/*
	@file	CollisionMesh.cpp
	@brief	Obj�`���̃��b�V�����R���W�����ɂ���N���X
*/
#include "pch.h"
#include "CollisionMesh.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

//-----------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------
mylib::CollisionMesh::CollisionMesh()
	:
	m_position{},
	m_rotation{},
	m_vertices{},
	m_indices{},
	m_triangles{},
	m_inputLayout{},
	m_basicEffect{},
	m_primitiveBatch{}
{
}

//-----------------------------------------------------
// ����������
//-----------------------------------------------------
void mylib::CollisionMesh::Initialize(
	const std::wstring& objName
)
{
	// Obj�t�@�C����ǂݍ���
	this->LoadObjFile(objName);

	// �|���S���z����쐬����
	for (size_t i = 0; i < m_indices.size() / 3; i++)
	{
		this->AddTriangle(
			m_vertices[m_indices[i * 3 + 0]].position,
			m_vertices[m_indices[i * 3 + 1]].position,
			m_vertices[m_indices[i * 3 + 2]].position
		);
	}

	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �`��I�u�W�F�N�g����������
	m_basicEffect = std::make_unique<BasicEffect>(device);

	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPosition>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPosition>>(context);
}

//-----------------------------------------------------
// �`�悷��
//-----------------------------------------------------
void mylib::CollisionMesh::Draw()
{
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	DirectX::SimpleMath::Matrix view = Graphics::GetInstance()->GetViewMatrix();
	DirectX::SimpleMath::Matrix projection = Graphics::GetInstance()->GetProjectionMatrix();

	// �f�o�C�X�R���e�L�X�g�̃p�����[�^��ݒ肷��
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states->DepthRead(), 0);	// �X�e���V���o�b�t�@�[�֏������܂Ȃ�
	context->RSSetState(states->Wireframe());
	context->IASetInputLayout(m_inputLayout.Get());

	// ���[���h�s����v�Z����
	Matrix rotation = Matrix::CreateFromQuaternion(m_rotation);
	Matrix translation = Matrix::CreateTranslation(m_position);
	Matrix world = rotation * translation;

	// �x�[�V�b�N�G�t�F�N�g�̃p�����[�^��ݒ肷��
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
	m_basicEffect->Apply(context);

	// ���b�V����`�悷��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		&m_indices[0], m_indices.size(),
		&m_vertices[0], m_vertices.size()
	);
	m_primitiveBatch->End();
}

//-----------------------------------------------------
// ���b�V����Ray�Ƃ̏Փ˔���
//-----------------------------------------------------
bool mylib::CollisionMesh::IntersectRay(
	const DirectX::SimpleMath::Ray& ray,		// ���C
	DirectX::SimpleMath::Vector3* hitPosition,	// �Փˍ��W
	DirectX::SimpleMath::Vector3* normal,		// �Փ˂����|���S���̖@��
	int* polygonNo								// �Փ˂����|���S���̔ԍ�
)
{
	assert(hitPosition);
	assert(normal);

	/*
		���C�ɃR���W�������b�V���̋t�s���������
	*/
	// �R���W�������b�V���̉�]����W��񂩂�Aworld�̋t�s������߂�
	Matrix rotation = Matrix::CreateFromQuaternion(m_rotation);
	Matrix transration = Matrix::CreateTranslation(m_position);
	Matrix world = rotation * transration;
	Matrix invertWorld = world.Invert();

	// ���C�ɃR���W�������b�V���̋t�s���������
	// �����C���R���W�������b�V���̃��[�J�����W�n�Ɏ����Ă���
	Ray unitRay{};
	unitRay.position = Vector3::Transform(ray.position, invertWorld);
	unitRay.direction = Vector3::Transform(ray.direction, invertWorld);

	// ���C�ƏՓ˓_�܂ł̋���
	float distance = 0.0f;

	// �Փ˔���
	for (int i = 0; i < m_triangles.size(); i++)
	{
		//** ToDo::���炩�ɏՓ˂��Ȃ��ꍇ�͑������^�[������悤�ɕύX����

		// ���C�ƃ|���S���̏Փ˔�����Ƃ�
		if (unitRay.Intersects(
			m_triangles[i].triangle[0],
			m_triangles[i].triangle[1],
			m_triangles[i].triangle[2],
			distance
		)
			)
		{
			// �Փ˓_�̍��W���v�Z����
			*hitPosition = Vector3{ unitRay.position + unitRay.direction * distance };

			// �Փ˓_�����[���h���W�ɕϊ�����
			*hitPosition = Vector3::Transform(*hitPosition, world);

			// �|���S���̖@���ɃR���W�������b�V���̉�]������������
			*normal = Vector3::Transform(m_triangles[i].normal, m_rotation);

			// �Փ˂����|���S���ԍ�
			*polygonNo = i;

			return true;
		}
	}

	// �Փ˂��Ȃ�����
	return false;
}

//-----------------------------------------------------
// Obj�`���̃t�@�C�������[�h����
//-----------------------------------------------------
void mylib::CollisionMesh::LoadObjFile(const std::wstring& objName)
{
	// Obj�`���̃t�@�C�����J��
	std::wstring fileName = L"Resources/Models/" + objName + L".obj";
	std::ifstream ifs(fileName);

	assert(ifs && ".obj�t�@�C�����ǂݍ��߂܂���ł���");

	// 1�s���Ƃɏ�������
	std::string line;
	while (getline(ifs, line))
	{
		// �ǂݎ�����P�s���̃f�[�^���X�g�����O�X�g���[���ň���
		std::stringstream iss(line);
		std::string type;

		// �擪�v�f���󂯎��
		iss >> type;

		// ���_�f�[�^���쐬����
		// ��Obj�f�[�^��vt,vn�����鎞������̂Œ��ӂ���
		if (type.compare("v") == 0)
		{
			Vector3 vec;
			iss >> vec.x >> vec.y >> vec.z;
			m_vertices.emplace_back(vec);
		}
		// �C���f�b�N�X�f�[�^���쐬����
		else if (type.compare("f") == 0)
		{
			int a, b, c;
			iss >> a >> b >> c;

			// �O�p�`�̒��_�C���f�b�N�X�ԍ������������܂ޏꍇ�͖�������F�R�_���قȂ�_���w���Ă���
			if (a != b && a != c && b != c)
			{
				/*
					�EObj�f�[�^�̃|���S���̒��_�͔����v���ɋL�^����Ă���
					�E������W�n�ł͒��_�͎��v���Ɏw�肷��
					�EDirectXTK�ł�������g�p����ꍇ�͖@����񂪔��]����̂ŁA���ӂ��K�v
				*/
				//m_indices.push_back(static_cast<uint16_t>(a - 1));
				//m_indices.push_back(static_cast<uint16_t>(c - 1));
				//m_indices.push_back(static_cast<uint16_t>(b - 1));

				/*
					�EObj�f�[�^�̃|���S���̒��_�͔����v���ɋL�^����Ă���
					�E�E����W�n�ł͂��̂ق����s�����悢�̂ŁA���̂܂ܗ��p����
					�E�@�������߂�ۂ����]���Ȃ��Ă悢
				*/
				m_indices.emplace_back(static_cast<uint16_t>(a - 1));
				m_indices.emplace_back(static_cast<uint16_t>(b - 1));
				m_indices.emplace_back(static_cast<uint16_t>(c - 1));
			}
		}
	}

	// �J�����t�@�C�������
	ifs.close();
}

//-----------------------------------------------------
// �O�p�`�|���S�������A�|���S���z��ɓo�^����
//-----------------------------------------------------
void mylib::CollisionMesh::AddTriangle(
	DirectX::SimpleMath::Vector3 a,
	DirectX::SimpleMath::Vector3 b,
	DirectX::SimpleMath::Vector3 c
)
{
	m_triangles.emplace_back(Triangle(a, b, c));
}

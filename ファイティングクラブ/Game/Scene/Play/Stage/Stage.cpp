//--------------------------------------------------------------------------------------
// File: Stage.cpp
//
// �v���C���[�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Stage.h"
#include "Game/Screen.h"

#include "Libraries/MyLib/CollisionMesh.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage()
	:
	m_model{},
	m_collisionMesh{},
	m_isVisible{},
	m_hitPosition{},
	m_normal{},
	m_hitPolygonNo{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
}

void Stage::Initialize()
{
	// �n�`�̕\�����f����ǂݍ���
	m_model = std::make_unique <Ede::ModelManager>();
	m_model->AddModelData("Terrain", L"Resources/Models/floor02.cmo");
	//�ŏ��͕\�����Ȃ�
	m_isVisible = false;

	//�R���W�������b�V���𐶐�
	m_collisionMesh = std::make_unique<mylib::CollisionMesh>();
	m_collisionMesh->Initialize(L"Stage");

	m_normal = { Vector3::Zero,Matrix::Identity };
}

/// <summary>
/// �`��֐�
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Stage::Render()
{
	// ���b�V����`�悷��
	m_collisionMesh->Draw();

	// ���f����`�悷��
	Matrix mat = Matrix::CreateTranslation(Vector3(0.0f, -1.2f, 0.0f));
	if (m_isVisible)
	{
		m_model->DrawModel("Terrain", mat);
	}
}

//�@���Ƃ̓����蔻��
Normal Stage::NormalHitDetection(DirectX::SimpleMath::Vector3 pos)
{
	//Ray���g�����R���W�������b�V���Ƃ̓����蔻��
	Vector3 rayOrigin = pos;
	//Ray�̎n�܂��������ɂ����Ă���
	rayOrigin.y += 2.0f;

	//Ray�ƏՓˎ��̃|���S���̖@�����`����
	Ray ray{ rayOrigin,Vector3::Down };
	Vector3 normal;

	//Ray�ƃR���W�������b�V���ŏՓ˔�������
	if (m_collisionMesh->IntersectRay(ray, &m_hitPosition, &normal, &m_hitPolygonNo))
	{
		Quaternion q2 = Quaternion::FromToRotation(Vector3::UnitY, normal);
		m_normal.rotate = Matrix::CreateFromQuaternion(q2);
		m_normal.pos = m_hitPosition;
	}
	return m_normal;
}

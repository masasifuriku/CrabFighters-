//--------------------------------------------------------------------------------------
// File: PlayerHand.cpp
//
// �v���C���[�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "PlayerHand.h"
#include "Game/Screen.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Input.h"

#include "Libraries/Microsoft/DebugDraw.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerHand::PlayerHand()
	:
	m_model{},
	m_BoundingSphere{},
	m_rotate{},
	m_angle{},
	m_attackCount{},
	m_time{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerHand::~PlayerHand()
{
}

void PlayerHand::Initialize()
{
	// �v���C���[���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("CrabRightHand", L"Resources/Models/CrabRightHand.cmo");

	//��]
	m_rotate = Quaternion::Identity;
	//�p�x�ݒ�
	m_angle = { 0.0f,10.0f,20.0f,30.0f,40.0f };
	//�U�����[�V�����J�E���g
	m_attackCount = 0;

	// �o�E���f�B���O�X�t�B�A�𐶐�����
	m_BoundingSphere = CreateBoundingSphere(0.5f);
}

/// <summary>
/// �`��֐�
/// </summary>
void PlayerHand::Render(Matrix world)
{
	Matrix rotation, translation;
	//�U�����ɘr����]
	rotation = Matrix::CreateFromQuaternion(m_rotate);
	//�r��̂̃��[���h���W�ƍ��킹��
	Matrix handWorld = rotation * world;

	//�o�E���f�B���O�X�t�B�A��r�ɍ��킹��
	translation = Matrix::CreateTranslation(-9.0f, 0.0f, 9.0f);
	//�r�ɍ��킹���̂Ƒ̂ɍ��킹���̂����킹��
	Matrix handSphere = translation * handWorld;
	// �o�E���f�B���O�X�t�B�A�̒��S���X�V
	Vector3 handPosition = Vector3::Transform(Vector3(1.0f, 0.0f, 1.0f), handSphere);
	m_BoundingSphere.Center = handPosition;

	// ���f����`�悷��
	m_model->DrawModel("CrabRightHand",handWorld);
	DrawBoundingSphere();
}

//�U�����ɘr�𓮂���
void PlayerHand::AttackMotion()
{
	// �z��C���f�b�N�X�Ǘ�
	static bool reverse = false;

	if (!reverse)
	{
		m_attackCount++;
		if (m_attackCount >= 4) // �Ō�̊p�x�ɒB������t������
		{
			m_attackCount = 4;
			reverse = true;
		}
	}
	else
	{
		m_attackCount--;
		if (m_attackCount <= 0) // �ŏ��̊p�x�ɖ߂�����i�s���������Z�b�g
		{
			m_attackCount = 0;
			reverse = false;
		}
	}
	// �N�H�[�^�j�I�����g���čU�����̘r�̉�]��ݒ�
	m_rotate = Quaternion::CreateFromAxisAngle(Vector3::UnitY, (XMConvertToRadians(m_angle[m_attackCount])));
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere PlayerHand::CreateBoundingSphere(const float& radius)
{
	// �o�E���f�B���O�X�t�B�A��錾����
	DirectX::BoundingSphere turretBoundingSphere;
	// �o�E���f�B���O�X�t�B�A�̔��a��ݒ肷��
	turretBoundingSphere.Radius = radius;
	// �o�E���f�B���O�X�t�B�A��Ԃ�
	return turretBoundingSphere;
}

// �o�E���f�B���O�X�t�B�A��`�悷��
void PlayerHand::DrawBoundingSphere()
{
	// ����F��ݒ肷��
	DirectX::XMVECTOR color = DirectX::Colors::Black;
	auto batch = Graphics::GetInstance();
	// �v���~�e�B�u�`����J�n����
	batch->DrawPrimitiveBegin(batch->GetViewMatrix(), batch->GetProjectionMatrix());
	// �C���̋��E����`�悷��
	DX::Draw(batch->GetPrimitiveBatch(), m_BoundingSphere, color);
	// �v���~�e�B�u�`����I������
	batch->DrawPrimitiveEnd();
}
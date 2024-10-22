//--------------------------------------------------------------------------------------
// File: PlayerHand.cpp
//
// �v���C���[�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "PlayerHand.h"
#include "Game/Screen.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerHand::PlayerHand()
	:
	m_model{},
	m_rotate{}
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
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void PlayerHand::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
	//�r�����ɖ߂�
	m_rotate = Quaternion::Identity;
}

/// <summary>
/// �`��֐�
/// </summary>
void PlayerHand::Render(Matrix world)
{
	//�̂̃��[���h�s��ɍ��킹��
	Matrix rotation = Matrix::CreateFromQuaternion(m_rotate);
	Matrix handworld = rotation * world;
	// ���f����`�悷��
	m_model->DrawModel("CrabRightHand",handworld);
}

//�U�����ɘr�𓮂���
void PlayerHand::AttackMotion()
{
	// �N�H�[�^�j�I�����g���čU�����̘r�̉�]��ݒ�
	m_rotate = Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(30.0f));
}

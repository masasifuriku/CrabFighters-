//--------------------------------------------------------------------------------------
// File: Player.cpp
//
// �v���C���[�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Player.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/UtilityMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	:
	m_model{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}

void Player::Initialize()
{
	// ���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void Player::Update()
{
}

/// <summary>
/// �`��֐�
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void Player::Render()
{
}

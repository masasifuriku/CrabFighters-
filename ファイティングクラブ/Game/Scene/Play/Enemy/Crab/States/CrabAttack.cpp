//--------------------------------------------------------------------------------------
// File: CrabAttack.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "CrabAttack.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"
#include "Game/Scene/Play/Player/PlayerBody.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CrabAttack::CrabAttack(EnemyCrab* crab,PlayerBody* player)
	:
	m_crab(crab),
	m_player(player),
	m_attackCoolTime{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CrabAttack::~CrabAttack()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void CrabAttack::Update(float time)
{
	//�U���N�[���^�C������
	m_attackCoolTime -= time;
	//�X�y�[�X����������
	if (m_attackCoolTime <= 0.0f)
	{
		//�U������
		m_player->TakeDamage(20.0f);
		//�N�[���^�C����ݒ�
		m_attackCoolTime = 1.0f;
	}
}
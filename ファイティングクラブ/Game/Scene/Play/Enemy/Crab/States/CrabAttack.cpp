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
#include "Game/Scene/Play/Enemy/Crab/EnemyCrabHand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CrabAttack::CrabAttack(EnemyCrab* crab, PlayerBody* player, EnemyCrabHand* hand)
	:
	m_crab(crab),
	m_player(player),
	m_hand(hand),
	m_attackCoolTime{ 1.0f } ,
	m_attackCount{}
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
	if (m_attackCoolTime <= 0.0f)
	{
		//�U�����[�V����
		m_hand->AttackMotion();
		//�J�E���g�𑝂₷
		m_attackCount++;
		//�J�E���g���I�������
		if (m_attackCount >= 8)
		{
			//�U������
			m_player->TakeDamage(1.0f);
			//�J�E���g��߂�
			m_attackCount = 0;
			//�N�[���^�C����ݒ�
			m_attackCoolTime = 1.0f;
		}
	}
}
#include "pch.h"
#include "Collision.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Player/PlayerHand.h"
#include "Game/Scene/Play/Enemy/EnemyManager.h"


std::unique_ptr<Collision> Collision::m_collision = nullptr;

// Collision�N���X�̃C���X�^���X���擾����
Collision* const Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		// Collision�N���X�̃C���X�^���X�𐶐�����
		m_collision.reset(new Collision());
	}
	// Collision�N���X�̃C���X�^���X��Ԃ�
	return m_collision.get();
}

// �R���X�g���N�^
Collision::Collision()
	:
	m_player{},
	m_playerHand{},
	m_enemy{}
{
}

//�v���C���[����G�ւ̂̍U��
bool Collision::CheckHitAttackPlayerToCrab()
{
	//�r�������Ă���
	m_playerHand = m_player->GetHand();

	//�������̃J�j�������Ă���
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//�������Ă���true
		if (m_playerHand->GetHandBoundingSphere().
			Intersects(
				crab->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}
bool Collision::CheckHitAttackPlayerToBird()
{
	//�r�������Ă���
	m_playerHand = m_player->GetHand();

	//�������̒��������Ă���
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//�������Ă���true
		if (m_playerHand->GetHandBoundingSphere().
			Intersects(
				bird->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}
bool Collision::CheckHitAttackPlayerToShark()
{
	//�r�������Ă���
	m_playerHand = m_player->GetHand();

	//�������̃T���������Ă���
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//�������Ă���true
		if (m_playerHand->GetHandBoundingSphere().
			Intersects(
				shark->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}
bool Collision::CheckHitAttackPlayerToBoss()
{
	//�r�������Ă���
	m_playerHand = m_player->GetHand();

	//�{�X�������Ă���
	auto& boss = m_enemy->GetBoss();
	//�������Ă���true
	if (m_playerHand->GetHandBoundingSphere().
		Intersects(
			boss->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}

//�G����v���C���[�ւ̍U��
bool Collision::CheckHitAttackCrabrToPlayer()
{
	//�������̃J�j�������Ă���
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//�������Ă���true
		if (crab->GetBodyBoundingSphere().
			Intersects(
				m_player->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}
bool Collision::CheckHitAttackBirdrToPlayer()
{
	//�������̒��������Ă���
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//�������Ă���true
		if (bird->GetBodyBoundingSphere().
			Intersects(
				m_player->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}
bool Collision::CheckHitAttackSharkToPlayer()
{
	//�������̃T���������Ă���
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//�������Ă���true
		if (shark->GetBodyBoundingSphere().
			Intersects(
				m_player->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}
bool Collision::CheckHitAttackBossToPlayer()
{
	//�{�X�������Ă���
	auto& boss = m_enemy->GetBoss();
	//�������Ă���true
	if (boss->GetBodyBoundingSphere().
		Intersects(
			m_player->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}

//�����߂�����
bool Collision::CheckHitPlayerAndCrab()
{
	//�������̃J�j�������Ă���
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//�������Ă���true
		if (m_player->GetBodyBoundingSphere().
			Intersects(
				crab->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitPlayerAndBird()
{
	//�������̒��������Ă���
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//�������Ă���true
		if (m_player->GetBodyBoundingSphere().
			Intersects(
				bird->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitPlayerAndShark()
{
	//�������̃T���������Ă���
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//�������Ă���true
		if (m_player->GetBodyBoundingSphere().
			Intersects(
				shark->GetBodyBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitPlayerAndBoss()
{
	//�{�X�������Ă���
	auto& boss = m_enemy->GetBoss();
	//�������Ă���true
	if (m_player->GetBodyBoundingSphere().
		Intersects(
			boss->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}

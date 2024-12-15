#include "pch.h"
#include "Collision.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
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
	m_enemy{}
{
}

bool Collision::CheckHitPlayerToCrab()
{
	//�������̃J�j�������Ă���
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//�������Ă���true
		if (m_player->GetBoundingSphere().
			Intersects(
				crab->GetBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitPlayerToBird()
{
	//�������̒��������Ă���
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//�������Ă���true
		if (m_player->GetBoundingSphere().
			Intersects(
				bird->GetBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitPlayerToShark()
{
	//�������̃T���������Ă���
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//�������Ă���true
		if (m_player->GetBoundingSphere().
			Intersects(
				shark->GetBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitPlayerToBoss()
{
	//�{�X�������Ă���
	auto& boss = m_enemy->GetBoss();
	//�������Ă���true
	if (m_player->GetBoundingSphere().
		Intersects(
			boss->GetBoundingSphere()))
	{
		return true;
	}
	return false;
}

bool Collision::CheckHitCrabrToPlayer()
{
	//�������̃J�j�������Ă���
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//�������Ă���true
		if (crab->GetBoundingSphere().
			Intersects(
				m_player->GetBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitBirdrToPlayer()
{
	//�������̒��������Ă���
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//�������Ă���true
		if (bird->GetBoundingSphere().
			Intersects(
				m_player->GetBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitSharkToPlayer()
{
	//�������̃T���������Ă���
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//�������Ă���true
		if (shark->GetBoundingSphere().
			Intersects(
				m_player->GetBoundingSphere()))
		{
			return true;
		}
	}
	return false;
}

bool Collision::CheckHitBossToPlayer()
{
	//�{�X�������Ă���
	auto& boss = m_enemy->GetBoss();
	//�������Ă���true
	if (boss->GetBoundingSphere().
		Intersects(
			m_player->GetBoundingSphere()))
	{
		return true;
	}
	return false;
}
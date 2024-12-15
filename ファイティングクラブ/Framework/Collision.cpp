#include "pch.h"
#include "Collision.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/EnemyManager.h"


std::unique_ptr<Collision> Collision::m_collision = nullptr;

// Collisionクラスのインスタンスを取得する
Collision* const Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		// Collisionクラスのインスタンスを生成する
		m_collision.reset(new Collision());
	}
	// Collisionクラスのインスタンスを返す
	return m_collision.get();
}

// コンストラクタ
Collision::Collision()
	:
	m_player{},
	m_enemy{}
{
}

bool Collision::CheckHitPlayerToCrab()
{
	//生存中のカニを持ってくる
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//当たってたらtrue
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
	//生存中の鳥を持ってくる
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//当たってたらtrue
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
	//生存中のサメを持ってくる
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//当たってたらtrue
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
	//ボスを持ってくる
	auto& boss = m_enemy->GetBoss();
	//当たってたらtrue
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
	//生存中のカニを持ってくる
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//当たってたらtrue
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
	//生存中の鳥を持ってくる
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//当たってたらtrue
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
	//生存中のサメを持ってくる
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//当たってたらtrue
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
	//ボスを持ってくる
	auto& boss = m_enemy->GetBoss();
	//当たってたらtrue
	if (boss->GetBoundingSphere().
		Intersects(
			m_player->GetBoundingSphere()))
	{
		return true;
	}
	return false;
}
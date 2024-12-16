#include "pch.h"
#include "Collision.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Player/PlayerHand.h"
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
	m_playerHand{},
	m_enemy{}
{
}

//プレイヤーから敵へのの攻撃
bool Collision::CheckHitAttackPlayerToCrab()
{
	//腕を持ってくる
	m_playerHand = m_player->GetHand();

	//生存中のカニを持ってくる
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//当たってたらtrue
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
	//腕を持ってくる
	m_playerHand = m_player->GetHand();

	//生存中の鳥を持ってくる
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//当たってたらtrue
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
	//腕を持ってくる
	m_playerHand = m_player->GetHand();

	//生存中のサメを持ってくる
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//当たってたらtrue
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
	//腕を持ってくる
	m_playerHand = m_player->GetHand();

	//ボスを持ってくる
	auto& boss = m_enemy->GetBoss();
	//当たってたらtrue
	if (m_playerHand->GetHandBoundingSphere().
		Intersects(
			boss->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}

//敵からプレイヤーへの攻撃
bool Collision::CheckHitAttackCrabrToPlayer()
{
	//生存中のカニを持ってくる
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//当たってたらtrue
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
	//生存中の鳥を持ってくる
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//当たってたらtrue
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
	//生存中のサメを持ってくる
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//当たってたらtrue
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
	//ボスを持ってくる
	auto& boss = m_enemy->GetBoss();
	//当たってたらtrue
	if (boss->GetBodyBoundingSphere().
		Intersects(
			m_player->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}

//押し戻し判定
bool Collision::CheckHitPlayerAndCrab()
{
	//生存中のカニを持ってくる
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//当たってたらtrue
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
	//生存中の鳥を持ってくる
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//当たってたらtrue
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
	//生存中のサメを持ってくる
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//当たってたらtrue
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
	//ボスを持ってくる
	auto& boss = m_enemy->GetBoss();
	//当たってたらtrue
	if (m_player->GetBodyBoundingSphere().
		Intersects(
			boss->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}

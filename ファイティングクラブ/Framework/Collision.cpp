#include "pch.h"
#include "Collision.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Player/PlayerHand.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"


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
	m_crab{},
	m_boss{}
{
}

//プレイヤーから敵へのの攻撃
bool Collision::CheckHitAttackPlayerToCrab()
{
	//腕を持ってくる
	m_playerHand = m_player->GetHand();
	//当たってたらtrue
	if (m_playerHand->GetHandBoundingSphere().
		Intersects(
			m_crab->GetBodyBoundingSphere()))
	{
		return true;
	}
	
	return false;
}
//bool Collision::CheckHitAttackPlayerToBoss()
//{
//	//腕を持ってくる
//	m_playerHand = m_player->GetHand();
//	//当たってたらtrue
//	if (m_playerHand->GetHandBoundingSphere().
//		Intersects(
//			m_boss->GetBodyBoundingSphere()))
//	{
//		return true;
//	}
//	return false;
//}

//敵からプレイヤーへの攻撃
bool Collision::CheckHitAttackCrabsToPlayer()
{
	//当たってたらtrue
	if (m_crab->GetBodyBoundingSphere().
		Intersects(
			m_player->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}
//bool Collision::CheckHitAttackBossToPlayer()
//{
//	//当たってたらtrue
//	if (m_boss->GetBodyBoundingSphere().
//		Intersects(
//			m_player->GetBodyBoundingSphere()))
//	{
//		return true;
//	}
//	return false;
//}
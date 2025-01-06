#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED

class PlayerBody;
class PlayerHand;
class EnemyCrab;
class EnemyBoss;

// Collisionクラスを定義する
class Collision
{
public:
	// Collisionクラスのインスタンスを取得する
	static Collision* const GetInstance();

	//プレイヤーをもらう
	void SetPlayer(PlayerBody* player) { m_player = player; }
	//敵をもらう
	void SetCrab(EnemyCrab* crab) { m_crab = crab; }
	void SetBoss(EnemyBoss* boss) { m_boss = boss; }

public:
	//攻撃系の当たり判定
	//プレイヤーからカニへの攻撃当たり判定
	bool CheckHitAttackPlayerToCrab();
	////プレイヤーからボスへの攻撃当たり判定
	//bool CheckHitAttackPlayerToBoss();

	//カニからプレイヤーへの攻撃当たり判定
	bool CheckHitAttackCrabsToPlayer();
	////ボスからプレイヤーへの攻撃当たり判定
	//bool CheckHitAttackBossToPlayer();

public:
	Collision(Collision&&) = default;
	Collision& operator= (Collision&&) = default;
	Collision& operator= (Collision const&) = delete;
	// デストラクタ
	~Collision() = default;

private:
	// コンストラクタ
	Collision();

private:
	// Collisionクラスのインスタンスへのポインタ
	static std::unique_ptr<Collision> m_collision;

	//プレイヤーのポインタ
	PlayerBody* m_player;
	//プレイヤーの腕のポインタ
	PlayerHand* m_playerHand;
	//カニのポインタ
	EnemyCrab* m_crab;
	//ボスのポインタ
	EnemyBoss* m_boss;
};

#endif		// Collision_DEFINED

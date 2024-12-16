#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED

class PlayerBody;
class PlayerHand;
class EnemyManager;

// Collisionクラスを定義する
class Collision
{
public:
	// Collisionクラスのインスタンスを取得する
	static Collision* const GetInstance();

	//プレイヤーをもらう
	void SetPlayer(PlayerBody* player) { m_player = player; }
	//敵をもらう
	void SetEnemy(EnemyManager* enemy) { m_enemy = enemy; }

public:
	//攻撃系の当たり判定
	//プレイヤーからカニへの攻撃当たり判定
	bool CheckHitAttackPlayerToCrab();
	//プレイヤーから鳥への攻撃当たり判定
	bool CheckHitAttackPlayerToBird();
	//プレイヤーからサメへの攻撃当たり判定
	bool CheckHitAttackPlayerToShark();
	//プレイヤーからボスへの攻撃当たり判定
	bool CheckHitAttackPlayerToBoss();
	//カニからプレイヤーへの攻撃当たり判定
	bool CheckHitAttackCrabrToPlayer();
	//鳥からプレイヤーへの攻撃当たり判定
	bool CheckHitAttackBirdrToPlayer();
	//サメからプレイヤーへの攻撃当たり判定
	bool CheckHitAttackSharkToPlayer();
	//ボスからプレイヤーへの攻撃当たり判定
	bool CheckHitAttackBossToPlayer();

	//押し戻し用当たり判定
	bool CheckHitPlayerAndCrab();
	bool CheckHitPlayerAndBird();
	bool CheckHitPlayerAndShark();
	bool CheckHitPlayerAndBoss();

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
	//敵のポインタ
	EnemyManager* m_enemy;
};

#endif		// Collision_DEFINED

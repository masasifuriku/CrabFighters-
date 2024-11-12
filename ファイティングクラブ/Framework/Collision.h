#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED

class PlayerBody;
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
	//プレイヤーからカニへの当たり判定
	bool CheckHitPlayerToCrab();
	//プレイヤーから鳥への当たり判定
	bool CheckHitPlayerToBird();
	//プレイヤーからサメへの当たり判定
	bool CheckHitPlayerToShark();
	//プレイヤーからボスへの当たり判定
	bool CheckHitPlayerToBoss();

	//カニからプレイヤーへの当たり判定
	bool CheckHitCrabrToPlayer();
	//鳥からプレイヤーへの当たり判定
	bool CheckHitBirdrToPlayer();
	//サメからプレイヤーへの当たり判定
	bool CheckHitSharkToPlayer();
	//ボスからプレイヤーへの当たり判定
	bool CheckHitBossToPlayer();

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
	//敵のポインタ
	EnemyManager* m_enemy;
};

#endif		// Collision_DEFINED

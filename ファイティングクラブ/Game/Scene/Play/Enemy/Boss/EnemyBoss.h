//--------------------------------------------------------------------------------------
// File: EnemyBoss.h
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Interface/IEnemy.h"
#include "Libraries/EdeLib/ModelManager.h"

class PlayerBody;

class BossPatrol;
class BossChase;
class BossAttack;
class BossEscape;

class EnemyBoss :public IEnemy
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
	//状態
	EnemyState m_state;

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 速さ
	DirectX::SimpleMath::Vector3 m_velocity;
	//回転
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	//行列
	DirectX::SimpleMath::Matrix m_world;
	//HP
	float m_health;
	//角度
	float m_angle;

	//プレイヤー
	PlayerBody* m_player;

	//ステート
	std::unique_ptr<BossPatrol> m_patrol;
	std::unique_ptr<BossChase> m_chase;
	std::unique_ptr<BossAttack> m_attack;
	std::unique_ptr<BossEscape> m_escape;

public:
	EnemyBoss(PlayerBody* player);
	~EnemyBoss();

	void Initialize(
		IEnemy::EnemyState state, 
		DirectX::SimpleMath::Vector3 position);
	void Update(float timer);
	void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal);
public:
	//現在の位置の取得
	DirectX::SimpleMath::Vector3 GetPos() const override{ return m_position; }
	//位置を受け取る
	void SetPos(DirectX::SimpleMath::Vector3 pos)override { m_position = pos; }
	//現在の角度を渡す
	float GetAngle()const override { return m_angle; }
	//角度を受け取る
	void SetAngle(float angle)override { m_angle = angle; }
	//状態の設定
	void SetEnemyState(EnemyState state) override { m_state = state; }
	//敵が生存中か
	bool IsActive() override;
	//ダメージを受ける
	void TakeDamage(float damage)override;
	//バウンディングスフィア生成
	DirectX::BoundingSphere GetBoundingSphere(
		DirectX::SimpleMath::Vector3 center) override;
	//体力を取得
	float GetHP() const override{ return m_health; }

private:
	//ステート管理
	void UpdateState();
};

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

public:
	EnemyBoss();
	~EnemyBoss();

	void Initialize(
		IEnemy::EnemyState state, 
		DirectX::SimpleMath::Vector3 position);
	void Update(float timer, DirectX::SimpleMath::Vector3 Ppos);
	void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal);
public:
	//現在の位置の取得
	DirectX::SimpleMath::Vector3 GetPos() const override{ return m_position; }
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
	void UpdateState(float time,DirectX::SimpleMath::Vector3 player);
	//探索
	void BossPatrol(float timer);
	//追跡
	void BossChase(DirectX::SimpleMath::Vector3 pos);
	//戦闘
	void BossBattle();
	//逃走
	void BossEscape(DirectX::SimpleMath::Vector3 pos);
};

//--------------------------------------------------------------------------------------
// File: EnemyCrab.h
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Interface/IEnemy.h"
#include "Libraries/EdeLib/ModelManager.h"

class CrabPatrol;
class CrabChase;
class CrabAttack;
class CrabEscape;

class EnemyCrab :public IEnemy
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
	//状態
	EnemyState m_state;

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	//回転
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	//行列
	DirectX::SimpleMath::Matrix m_world;
	//角度
	float m_angle;
	//速度
	static constexpr float SPEED = 0.1f;
	//HP
	float m_health;

	//ステート
	std::unique_ptr<CrabPatrol> m_patrol;
	std::unique_ptr<CrabChase> m_chase;
	std::unique_ptr<CrabAttack> m_attack;
	std::unique_ptr<CrabEscape> m_escape;

	//std::vector<std::vector<DirectX::SimpleMath::Vector3>> m_goals2;


public:
	EnemyCrab();
	~EnemyCrab()override;

	void Initialize(
		IEnemy::EnemyState state, 
		DirectX::SimpleMath::Vector3 position);
	void Update(float timer, DirectX::SimpleMath::Vector3 Ppos);
	void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal);
public:
	//現在の位置の渡す
	DirectX::SimpleMath::Vector3 GetPos() const override{ return m_position; }
	//位置を受け取る
	void SetPos(DirectX::SimpleMath::Vector3 pos)override { m_position += pos; }
	//現在の角度を渡す
	float GetAngle()const override { return m_angle; }
	//角度を受け取る
	void SetAngle(float angle)override { m_angle += angle; }
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
};

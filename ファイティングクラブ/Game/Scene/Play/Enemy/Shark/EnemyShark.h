//--------------------------------------------------------------------------------------
// File: EnemyShark.h
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Interface/IEnemy.h"
#include "Libraries/EdeLib/ModelManager.h"

class PlayerBody;

class SharkPatrol;
class SharkChase;
class SharkAttack;
class SharkEscape;

class EnemyShark:public IEnemy
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
	//状態
	EnemyState m_state;

	// バウンディングスフィア
	DirectX::BoundingSphere m_BoundingSphere;

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 速さ
	DirectX::SimpleMath::Vector3 m_velocity;
	//回転
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	//行列
	DirectX::SimpleMath::Matrix m_world;
	//角度
	float m_angle;
	//HP
	float m_health;

	//プレイヤー
	PlayerBody* m_player;

	//ステート
	std::unique_ptr<SharkPatrol> m_patrol;
	std::unique_ptr<SharkChase> m_chase;
	std::unique_ptr<SharkAttack> m_attack;
	std::unique_ptr<SharkEscape> m_escape;

public:
	EnemyShark(PlayerBody* player);
	~EnemyShark();

	void Initialize(
		IEnemy::EnemyState state,
		DirectX::SimpleMath::Vector3 position);
	void Update(float timer);
	void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal
	);
public:
	//ゲーター
	DirectX::SimpleMath::Vector3 GetPos()const override{ return m_position; }
	//位置を受け取る
	void SetPos(DirectX::SimpleMath::Vector3 pos)override { m_position = pos; }
	//現在の角度を渡す
	float GetAngle()const override { return m_angle; }
	//角度を受け取る
	void SetAngle(float angle)override { m_angle = angle; }
	//状態の設定
	void SetEnemyState(EnemyState state) override { m_state = state; }
	// 敵が生存中か
	bool IsActive() override;
	//ダメージを受ける
	void TakeDamage(float damage)override;
	//バウンディングスフィア生成
	DirectX::BoundingSphere CreateBoundingSphere(
		const float& radius) override;
	//バウンディングスフィアを取得する
	DirectX::BoundingSphere& GetBodyBoundingSphere() override
	{ return m_BoundingSphere; }
	// バウンディングスフィアを描画する
	void DrawBoundingSphere() override;
	//HPを取得する
	float GetHP() const override{ return m_health; }

private:
	//ステート管理
	void UpdateState();

};

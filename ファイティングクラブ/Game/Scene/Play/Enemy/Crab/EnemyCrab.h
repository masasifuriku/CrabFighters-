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

class PlayerBody;
class EnemyCrabHand;

class CrabPatrol;
class CrabChase;
class CrabAttack;
class CrabEscape;

class EnemyCrab :public IEnemy
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
	//敵カニの腕
	std::unique_ptr<EnemyCrabHand> m_hand;
	//状態
	EnemyState m_state;

	// バウンディングスフィア
	DirectX::BoundingSphere m_BoundingSphere;

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
	//プレイヤーのサイズ
	float m_size;
	//HP
	float m_health;

	//プレイヤー
	PlayerBody* m_player;

	//ステート
	std::unique_ptr<CrabPatrol> m_patrol;
	std::unique_ptr<CrabChase> m_chase;
	std::unique_ptr<CrabAttack> m_attack;
	std::unique_ptr<CrabEscape> m_escape;

public:
	EnemyCrab(PlayerBody* player);
	~EnemyCrab()override;

	void Initialize(DirectX::SimpleMath::Vector3 position);
	void Update(float timer);
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
	//状態の取得
	EnemyState GetState() { return m_state; }
	//状態の設定
	void SetEnemyState(EnemyState state) override { m_state = state; }
	//敵が生存中か
	bool IsActive() override;
	//ダメージを受ける
	void TakeDamage(float damage)override { m_health -= damage; }
	//バウンディングスフィア生成
	DirectX::BoundingSphere CreateBoundingSphere(
		const float& radius) override;
	//バウンディングスフィアを取得する
	DirectX::BoundingSphere& GetBodyBoundingSphere() override 
	{ return m_BoundingSphere; }
	// バウンディングスフィアを描画する
	void DrawBoundingSphere() override;
	//体力を取得
	float GetHP() const override{ return m_health; }

private:
	//ステート変更
	void ChangeState();
	//ステート管理
	void UpdateState(float time);
};

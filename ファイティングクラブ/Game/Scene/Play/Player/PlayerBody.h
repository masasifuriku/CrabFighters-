//--------------------------------------------------------------------------------------
// File: PlayerBody.h
//
// プレイヤー本体クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"

class Stage;
class PlayerHand;

class PlayerBody
{
public:
	//プレイヤーの状態
	enum PlayerState {
		NONE,   //何もしていない
		ATTACK, //攻撃
		DEAD    //死亡
	};

private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
	//プレイヤーの腕
	std::unique_ptr<PlayerHand> m_hand;
	//ステージのポインタ
	Stage* m_stage;

	//プレイヤー自身の変数
	//プレイヤーの状態 
	PlayerState m_state;
	// バウンディングスフィア
	DirectX::BoundingSphere m_BoundingSphere;
	// プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_position;
	//プレイヤーの速さ
	DirectX::SimpleMath::Vector3 m_velocity;
	//プレイヤーの回転
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	//傾き
	DirectX::SimpleMath::Matrix m_rotateNormal;
	//プレイヤーのサイズ
	float m_size;
	//プレイヤーの体力
	float m_health;
	//プレイヤーのスタミナ
	float m_stamina;
	//プレイヤーの攻撃クールタイム
	float m_attackCoolTime;
	//プレイヤーのワールド行列
	DirectX::SimpleMath::Matrix m_world;
	//衝突判定
	bool m_isHit;

	//マウス操作系
	std::unique_ptr<DirectX::GeometricPrimitive> m_torus;
	// 座標
	DirectX::SimpleMath::Vector3 m_torusPosition;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_torusWorld;

	//攻撃カウント
	int m_attackCount;


public:
	PlayerBody(Stage* stage);
	~PlayerBody();

	void Initialize();
	void Update(float timer);
	void Render();
public:
	//ゲーター
	DirectX::SimpleMath::Vector3 GetPos() const { return m_position; }
	//状態
	PlayerState GetState() { return m_state; }
	//バウンディングスフィア取得
	DirectX::BoundingSphere& GetBodyBoundingSphere() { return m_BoundingSphere; }
	//体力を取得
	float GetHP() const { return m_health; }
	//ダメージを受ける
	void TakeDamage(float damage);
	//スタミナを取得
	float GetStamina()const { return m_stamina; }
	//腕を渡す
	PlayerHand* GetHand() { return m_hand.get(); }
private:
	//キーボード処理
	void KeyBoardEvent();
	//マウス処理
	void MouseEvent();
	//バウンディングスフィア生成
	DirectX::BoundingSphere CreateBoundingSphere(
		const float& radius);
	// バウンディングスフィアを描画する
	void DrawBoundingSphere();
};

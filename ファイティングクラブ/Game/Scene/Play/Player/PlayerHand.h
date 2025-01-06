//--------------------------------------------------------------------------------------
// File: PlayerHand.h
//
// プレイヤー腕クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"
#include "PlayerBody.h"
#include <vector>

class PlayerHand
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;

	// バウンディングスフィア
	DirectX::BoundingSphere m_BoundingSphere;

	//プレイヤー自身の変数
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	std::vector<float> m_angle;
	int m_attackCount;
	float m_time;

public:
	PlayerHand();
	~PlayerHand();

	void Initialize();
	void Render(DirectX::SimpleMath::Matrix world);

public:
	//プレイヤーの攻撃モーション
	void AttackMotion();
	//バウンディングスフィア取得
	DirectX::BoundingSphere& GetHandBoundingSphere() { return m_BoundingSphere; }
	//バウンディングスフィアの中心点を設定を設定
	void SetSphereCenter(DirectX::SimpleMath::Vector3 center) { m_BoundingSphere.Center = center; }

private:
	//バウンディングスフィア生成
	DirectX::BoundingSphere CreateBoundingSphere(
		const float& radius);
	// バウンディングスフィアを描画する
	void DrawBoundingSphere();

};

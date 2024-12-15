//--------------------------------------------------------------------------------------
// File: EnemyCrabHand.h
//
// 敵カニ腕クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"
#include "EnemyCrab.h"


class EnemyCrabHand
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;

	//プレイヤー自身の変数
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	float m_angle[4];
	int m_attackCount;
	float m_time;

public:
	EnemyCrabHand();
	~EnemyCrabHand();

	void Initialize();
	void Render(DirectX::SimpleMath::Matrix world);

public:
	//プレイヤーの攻撃モーション
	void AttackMotion();

private:
	
};

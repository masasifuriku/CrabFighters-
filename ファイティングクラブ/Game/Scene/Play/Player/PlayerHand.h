//--------------------------------------------------------------------------------------
// File: PlayerHand.h
//
// プレイヤー腕クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"


class PlayerHand
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;

	//プレイヤー自身の変数
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;

public:
	PlayerHand();
	~PlayerHand();

	void Initialize();
	void Update(float timer);
	void Render(DirectX::SimpleMath::Matrix world);

public:
	//プレイヤーの攻撃モーション
	void AttackMotion();

private:
	
};

//--------------------------------------------------------------------------------------
// File: EnemyBossRightLeg.h
//
// ボス右足クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"


class EnemyBossRightLeg
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
	//バウンディングスフィア
	DirectX::BoundingSphere m_BoundingSphere;

public:
	EnemyBossRightLeg();
	~EnemyBossRightLeg();

	void Initialize();
	void Update(float timer);
	void Render();
public:
	//バウンディングスフィア生成
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);
	//バウンディングスフィアを取得する
	DirectX::BoundingSphere& GetBodyBoundingSphere(){ return m_BoundingSphere; }
	// バウンディングスフィアを描画する
	void DrawBoundingSphere();
};

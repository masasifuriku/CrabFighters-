//--------------------------------------------------------------------------------------
// File: BossChase.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBoss;

class BossChase
{
private:
	EnemyBoss* m_boss;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	BossChase(EnemyBoss* boss);
	~BossChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

//--------------------------------------------------------------------------------------
// File: BossEscape.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBoss;

class BossEscape
{
private:
	EnemyBoss* m_boss;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	BossEscape(EnemyBoss* boss);
	~BossEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

//--------------------------------------------------------------------------------------
// File: BossPatrol.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBoss;

class BossPatrol
{
private:
	EnemyBoss* m_boss;

	// 現在のゴール番号
	unsigned int m_currentGoalNo;
	// ゴール配列
	std::vector<DirectX::SimpleMath::Vector3> m_goals;
	// 発見フラグ
	bool m_isInside;
	//速度
	static constexpr float SPEED = 0.1f;

public:
	BossPatrol(EnemyBoss* boss);
	~BossPatrol();

	void Update();
};

//--------------------------------------------------------------------------------------
// File: CrabPatrol.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyCrab;

class CrabPatrol
{
private:
	EnemyCrab* m_crab;

	// 現在のゴール番号
	unsigned int m_currentGoalNo;
	// ゴール配列
	std::vector<DirectX::SimpleMath::Vector3> m_goals;
	// 発見フラグ
	bool m_isInside;
	//速度
	static constexpr float SPEED = 0.1f;

public:
	CrabPatrol(EnemyCrab* crab);
	~CrabPatrol();

	void Update();
};

//--------------------------------------------------------------------------------------
// File: SharkPatrol.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyShark;

class SharkPatrol
{
private:
	EnemyShark* m_shark;

	// 現在のゴール番号
	unsigned int m_currentGoalNo;
	// ゴール配列
	std::vector<DirectX::SimpleMath::Vector3> m_goals;
	// 発見フラグ
	bool m_isInside;
	//速度
	static constexpr float SPEED = 0.1f;

public:
	SharkPatrol(EnemyShark* shark);
	~SharkPatrol();

	void Update();
};

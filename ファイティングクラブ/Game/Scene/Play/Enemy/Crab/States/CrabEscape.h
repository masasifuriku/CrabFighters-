//--------------------------------------------------------------------------------------
// File: CrabEscape.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyCrab;

class CrabEscape
{
private:
	EnemyCrab* m_crab;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	CrabEscape(EnemyCrab* crab);
	~CrabEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

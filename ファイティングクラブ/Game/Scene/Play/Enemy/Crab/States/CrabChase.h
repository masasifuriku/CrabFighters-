//--------------------------------------------------------------------------------------
// File: CrabChase.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyCrab;

class CrabChase
{
private:
	EnemyCrab* m_crab;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	CrabChase(EnemyCrab* crab);
	~CrabChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

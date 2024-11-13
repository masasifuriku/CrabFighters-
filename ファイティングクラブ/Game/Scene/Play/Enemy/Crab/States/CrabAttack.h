//--------------------------------------------------------------------------------------
// File: CrabAttack.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyCrab;

class CrabAttack
{
private:
	EnemyCrab* m_crab;


public:
	CrabAttack(EnemyCrab* crab);
	~CrabAttack();

	void Update();
};

//--------------------------------------------------------------------------------------
// File: SharkAttack.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyShark;

class SharkAttack
{
private:
	EnemyShark* m_shark;


public:
	SharkAttack(EnemyShark* shark);
	~SharkAttack();

	void Update();
};

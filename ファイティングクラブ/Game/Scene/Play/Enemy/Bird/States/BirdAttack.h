//--------------------------------------------------------------------------------------
// File: BirdAttack.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBird;

class BirdAttack
{
private:
	EnemyBird* m_bird;


public:
	BirdAttack(EnemyBird* bird);
	~BirdAttack();

	void Update();
};

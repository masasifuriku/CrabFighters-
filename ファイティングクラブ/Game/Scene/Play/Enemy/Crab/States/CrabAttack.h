//--------------------------------------------------------------------------------------
// File: CrabAttack.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Framework/Collision.h"

class EnemyCrab;
class PlayerBody;

class CrabAttack
{
private:
	EnemyCrab* m_crab;
	PlayerBody* m_player;
	//クールタイム
	float m_attackCoolTime;


public:
	CrabAttack(EnemyCrab* crab, PlayerBody* player);
	~CrabAttack();

	void Update();
};

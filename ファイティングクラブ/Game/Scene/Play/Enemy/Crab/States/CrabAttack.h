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
class EnemyCrabHand;

class CrabAttack
{
private:
	EnemyCrab* m_crab;
	PlayerBody* m_player;
	EnemyCrabHand* m_hand;
	//クールタイム
	float m_attackCoolTime;
	//攻撃カウント
	int m_attackCount;


public:
	CrabAttack(EnemyCrab* crab, PlayerBody* player, EnemyCrabHand* hand);
	~CrabAttack();

	void Update(float time);
};

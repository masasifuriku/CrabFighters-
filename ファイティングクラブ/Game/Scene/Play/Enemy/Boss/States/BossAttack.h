//--------------------------------------------------------------------------------------
// File: BossAttack.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBoss;

class BossAttack
{
private:
	EnemyBoss* m_boss;


public:
	BossAttack(EnemyBoss* boss);
	~BossAttack();

	void Update();
};

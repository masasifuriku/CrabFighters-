//--------------------------------------------------------------------------------------
// File: CrabAttack.h
//
// �G�X�e�[�g�N���X
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

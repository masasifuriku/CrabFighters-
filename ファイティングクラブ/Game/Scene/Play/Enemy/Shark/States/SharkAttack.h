//--------------------------------------------------------------------------------------
// File: SharkAttack.h
//
// �G�X�e�[�g�N���X
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

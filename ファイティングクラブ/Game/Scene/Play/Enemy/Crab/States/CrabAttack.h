//--------------------------------------------------------------------------------------
// File: CrabAttack.h
//
// �G�X�e�[�g�N���X
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
	//�N�[���^�C��
	float m_attackCoolTime;


public:
	CrabAttack(EnemyCrab* crab, PlayerBody* player);
	~CrabAttack();

	void Update();
};

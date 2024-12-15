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
class EnemyCrabHand;

class CrabAttack
{
private:
	EnemyCrab* m_crab;
	PlayerBody* m_player;
	EnemyCrabHand* m_hand;
	//�N�[���^�C��
	float m_attackCoolTime;
	//�U���J�E���g
	int m_attackCount;


public:
	CrabAttack(EnemyCrab* crab, PlayerBody* player, EnemyCrabHand* hand);
	~CrabAttack();

	void Update(float time);
};

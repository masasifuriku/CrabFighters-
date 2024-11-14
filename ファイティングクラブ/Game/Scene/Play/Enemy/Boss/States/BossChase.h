//--------------------------------------------------------------------------------------
// File: BossChase.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBoss;

class BossChase
{
private:
	EnemyBoss* m_boss;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	BossChase(EnemyBoss* boss);
	~BossChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

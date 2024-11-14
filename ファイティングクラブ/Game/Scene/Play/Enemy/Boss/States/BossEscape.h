//--------------------------------------------------------------------------------------
// File: BossEscape.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBoss;

class BossEscape
{
private:
	EnemyBoss* m_boss;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	BossEscape(EnemyBoss* boss);
	~BossEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

//--------------------------------------------------------------------------------------
// File: BirdChase.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBird;

class BirdChase
{
private:
	EnemyBird* m_bird;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	BirdChase(EnemyBird* bird);
	~BirdChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

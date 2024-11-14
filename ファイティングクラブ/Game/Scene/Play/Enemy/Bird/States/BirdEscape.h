//--------------------------------------------------------------------------------------
// File: BirdEscape.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBird;

class BirdEscape
{
private:
	EnemyBird* m_bird;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	BirdEscape(EnemyBird* bird);
	~BirdEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

//--------------------------------------------------------------------------------------
// File: CrabChase.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyCrab;

class CrabChase
{
private:
	EnemyCrab* m_crab;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	CrabChase(EnemyCrab* crab);
	~CrabChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

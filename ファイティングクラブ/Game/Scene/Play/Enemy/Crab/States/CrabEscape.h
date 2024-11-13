//--------------------------------------------------------------------------------------
// File: CrabEscape.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyCrab;

class CrabEscape
{
private:
	EnemyCrab* m_crab;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	CrabEscape(EnemyCrab* crab);
	~CrabEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

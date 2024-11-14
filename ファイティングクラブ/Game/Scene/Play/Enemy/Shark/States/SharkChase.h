//--------------------------------------------------------------------------------------
// File: SharkChase.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyShark;

class SharkChase
{
private:
	EnemyShark* m_shark;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	SharkChase(EnemyShark* shark);
	~SharkChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

//--------------------------------------------------------------------------------------
// File: SharkEscape.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyShark;

class SharkEscape
{
private:
	EnemyShark* m_shark;

	//���x
	static constexpr float SPEED = 0.1f;

public:
	SharkEscape(EnemyShark* shark);
	~SharkEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

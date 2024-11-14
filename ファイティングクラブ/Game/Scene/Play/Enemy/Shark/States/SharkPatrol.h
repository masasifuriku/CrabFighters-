//--------------------------------------------------------------------------------------
// File: SharkPatrol.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyShark;

class SharkPatrol
{
private:
	EnemyShark* m_shark;

	// ���݂̃S�[���ԍ�
	unsigned int m_currentGoalNo;
	// �S�[���z��
	std::vector<DirectX::SimpleMath::Vector3> m_goals;
	// �����t���O
	bool m_isInside;
	//���x
	static constexpr float SPEED = 0.1f;

public:
	SharkPatrol(EnemyShark* shark);
	~SharkPatrol();

	void Update();
};

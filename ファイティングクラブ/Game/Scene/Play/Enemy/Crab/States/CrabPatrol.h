//--------------------------------------------------------------------------------------
// File: CrabPatrol.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyCrab;

class CrabPatrol
{
private:
	EnemyCrab* m_crab;

	// ���݂̃S�[���ԍ�
	unsigned int m_currentGoalNo;
	// �S�[���z��
	std::vector<DirectX::SimpleMath::Vector3> m_goals;
	// �����t���O
	bool m_isInside;
	//���x
	static constexpr float SPEED = 0.1f;

public:
	CrabPatrol(EnemyCrab* crab);
	~CrabPatrol();

	void Update();
};

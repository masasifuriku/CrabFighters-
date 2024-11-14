//--------------------------------------------------------------------------------------
// File: BossPatrol.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBoss;

class BossPatrol
{
private:
	EnemyBoss* m_boss;

	// ���݂̃S�[���ԍ�
	unsigned int m_currentGoalNo;
	// �S�[���z��
	std::vector<DirectX::SimpleMath::Vector3> m_goals;
	// �����t���O
	bool m_isInside;
	//���x
	static constexpr float SPEED = 0.1f;

public:
	BossPatrol(EnemyBoss* boss);
	~BossPatrol();

	void Update();
};

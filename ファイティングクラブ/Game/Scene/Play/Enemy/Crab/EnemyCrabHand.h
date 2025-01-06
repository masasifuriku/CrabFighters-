//--------------------------------------------------------------------------------------
// File: EnemyCrabHand.h
//
// �G�J�j�r�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"
#include "EnemyCrab.h"
#include <vector>

class EnemyCrabHand
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;

	//�v���C���[���g�̕ϐ�
	// �N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;
	std::vector<float> m_angle;
	int m_attackCount;
	float m_time;

public:
	EnemyCrabHand();
	~EnemyCrabHand();

	void Initialize();
	void Render(DirectX::SimpleMath::Matrix world);

public:
	//�v���C���[�̍U�����[�V����
	void AttackMotion();

private:
	
};

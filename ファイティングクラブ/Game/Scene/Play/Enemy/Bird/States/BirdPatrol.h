//--------------------------------------------------------------------------------------
// File: BirdPatrol.h
//
// �G�X�e�[�g�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"



class BirdPatrol
{
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ����
	DirectX::SimpleMath::Vector3 m_velocity;
	//��]
	// �N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;
	//�s��
	DirectX::SimpleMath::Matrix m_world;
	//�p�x
	float m_angle;

public:
	BirdPatrol();
	~BirdPatrol();

	void Update(float timer, DirectX::SimpleMath::Vector3 Ppos);
};

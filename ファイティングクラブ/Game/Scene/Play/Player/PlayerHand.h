//--------------------------------------------------------------------------------------
// File: PlayerHand.h
//
// �v���C���[�r�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"


class PlayerHand
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;

	//�v���C���[���g�̕ϐ�
	// �N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

public:
	PlayerHand();
	~PlayerHand();

	void Initialize();
	void Update(float timer);
	void Render(DirectX::SimpleMath::Matrix world);

public:
	//�v���C���[�̍U�����[�V����
	void AttackMotion();

private:
	
};

//--------------------------------------------------------------------------------------
// File: PlayerHand.h
//
// �v���C���[�r�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"
#include "PlayerBody.h"
#include <vector>

class PlayerHand
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;

	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_BoundingSphere;

	//�v���C���[���g�̕ϐ�
	// �N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;
	std::vector<float> m_angle;
	int m_attackCount;
	float m_time;

public:
	PlayerHand();
	~PlayerHand();

	void Initialize();
	void Render(DirectX::SimpleMath::Matrix world);

public:
	//�v���C���[�̍U�����[�V����
	void AttackMotion();
	//�o�E���f�B���O�X�t�B�A�擾
	DirectX::BoundingSphere& GetHandBoundingSphere() { return m_BoundingSphere; }
	//�o�E���f�B���O�X�t�B�A�̒��S�_��ݒ��ݒ�
	void SetSphereCenter(DirectX::SimpleMath::Vector3 center) { m_BoundingSphere.Center = center; }

private:
	//�o�E���f�B���O�X�t�B�A����
	DirectX::BoundingSphere CreateBoundingSphere(
		const float& radius);
	// �o�E���f�B���O�X�t�B�A��`�悷��
	void DrawBoundingSphere();

};

//--------------------------------------------------------------------------------------
// File: EnemyCrab.h
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Interface/IEnemy.h"
#include "Libraries/EdeLib/ModelManager.h"

class EnemyCrab :public IEnemy
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	//���
	EnemyState m_state;

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
	//���x
	static constexpr float SPEED = 0.1f;
	// ���݂̃S�[���ԍ�
	unsigned int m_currentGoalNo;
	// �S�[���z��
	std::vector<DirectX::SimpleMath::Vector3> m_goals;
	// �����t���O
	bool m_isInside;
	//HP
	float m_health;
	//�J�E���g
	float m_count;

	std::vector<std::vector<DirectX::SimpleMath::Vector3>> m_goals2;


public:
	EnemyCrab();
	~EnemyCrab();

	void Initialize(
		IEnemy::EnemyState state, 
		DirectX::SimpleMath::Vector3 position);
	void Update(float timer, DirectX::SimpleMath::Vector3 Ppos);
	void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal);
public:
	//���݂̈ʒu�̎擾
	DirectX::SimpleMath::Vector3 GetPos() const override{ return m_position; }
	//��Ԃ̐ݒ�
	void SetEnemyState(EnemyState state) override { m_state = state; }
	//�G����������
	bool IsActive() override;
	//�_���[�W���󂯂�
	void TakeDamage(float damage)override;
	//�o�E���f�B���O�X�t�B�A����
	DirectX::BoundingSphere GetBoundingSphere(
		DirectX::SimpleMath::Vector3 center) override;
	//�̗͂��擾
	float GetHP() const override{ return m_health; }

private:
	//�X�e�[�g�Ǘ�
	void UpdateState(float time,DirectX::SimpleMath::Vector3 player);
	//�T��
	void CrabPatrol(float timer);
	//�ǐ�
	void CrabChase(DirectX::SimpleMath::Vector3 pos);
	//�퓬
	void CrabBattle();
	//����
	void CrabEscape(DirectX::SimpleMath::Vector3 pos);
};

//--------------------------------------------------------------------------------------
// File: EnemyBoss.h
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Interface/IEnemy.h"
#include "Libraries/EdeLib/ModelManager.h"

class EnemyBoss :public IEnemy
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
	//HP
	float m_health;
	//�p�x
	float m_angle;

public:
	EnemyBoss();
	~EnemyBoss();

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
	void BossPatrol(float timer);
	//�ǐ�
	void BossChase(DirectX::SimpleMath::Vector3 pos);
	//�퓬
	void BossBattle();
	//����
	void BossEscape(DirectX::SimpleMath::Vector3 pos);
};

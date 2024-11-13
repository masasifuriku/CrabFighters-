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

class CrabPatrol;
class CrabChase;
class CrabAttack;
class CrabEscape;

class EnemyCrab :public IEnemy
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	//���
	EnemyState m_state;

	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	//��]
	// �N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;
	//�s��
	DirectX::SimpleMath::Matrix m_world;
	//�p�x
	float m_angle;
	//���x
	static constexpr float SPEED = 0.1f;
	//HP
	float m_health;

	//�X�e�[�g
	std::unique_ptr<CrabPatrol> m_patrol;
	std::unique_ptr<CrabChase> m_chase;
	std::unique_ptr<CrabAttack> m_attack;
	std::unique_ptr<CrabEscape> m_escape;

	//std::vector<std::vector<DirectX::SimpleMath::Vector3>> m_goals2;


public:
	EnemyCrab();
	~EnemyCrab()override;

	void Initialize(
		IEnemy::EnemyState state, 
		DirectX::SimpleMath::Vector3 position);
	void Update(float timer, DirectX::SimpleMath::Vector3 Ppos);
	void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal);
public:
	//���݂̈ʒu�̓n��
	DirectX::SimpleMath::Vector3 GetPos() const override{ return m_position; }
	//�ʒu���󂯎��
	void SetPos(DirectX::SimpleMath::Vector3 pos)override { m_position += pos; }
	//���݂̊p�x��n��
	float GetAngle()const override { return m_angle; }
	//�p�x���󂯎��
	void SetAngle(float angle)override { m_angle += angle; }
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
};

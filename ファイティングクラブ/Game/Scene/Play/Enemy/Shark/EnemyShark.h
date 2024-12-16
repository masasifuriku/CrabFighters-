//--------------------------------------------------------------------------------------
// File: EnemyShark.h
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Interface/IEnemy.h"
#include "Libraries/EdeLib/ModelManager.h"

class PlayerBody;

class SharkPatrol;
class SharkChase;
class SharkAttack;
class SharkEscape;

class EnemyShark:public IEnemy
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	//���
	EnemyState m_state;

	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_BoundingSphere;

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
	//HP
	float m_health;

	//�v���C���[
	PlayerBody* m_player;

	//�X�e�[�g
	std::unique_ptr<SharkPatrol> m_patrol;
	std::unique_ptr<SharkChase> m_chase;
	std::unique_ptr<SharkAttack> m_attack;
	std::unique_ptr<SharkEscape> m_escape;

public:
	EnemyShark(PlayerBody* player);
	~EnemyShark();

	void Initialize(
		IEnemy::EnemyState state,
		DirectX::SimpleMath::Vector3 position);
	void Update(float timer);
	void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal
	);
public:
	//�Q�[�^�[
	DirectX::SimpleMath::Vector3 GetPos()const override{ return m_position; }
	//�ʒu���󂯎��
	void SetPos(DirectX::SimpleMath::Vector3 pos)override { m_position = pos; }
	//���݂̊p�x��n��
	float GetAngle()const override { return m_angle; }
	//�p�x���󂯎��
	void SetAngle(float angle)override { m_angle = angle; }
	//��Ԃ̐ݒ�
	void SetEnemyState(EnemyState state) override { m_state = state; }
	// �G����������
	bool IsActive() override;
	//�_���[�W���󂯂�
	void TakeDamage(float damage)override;
	//�o�E���f�B���O�X�t�B�A����
	DirectX::BoundingSphere CreateBoundingSphere(
		const float& radius) override;
	//�o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere& GetBodyBoundingSphere() override
	{ return m_BoundingSphere; }
	// �o�E���f�B���O�X�t�B�A��`�悷��
	void DrawBoundingSphere() override;
	//HP���擾����
	float GetHP() const override{ return m_health; }

private:
	//�X�e�[�g�Ǘ�
	void UpdateState();

};

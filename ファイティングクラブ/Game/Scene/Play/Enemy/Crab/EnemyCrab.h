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

class PlayerBody;
class EnemyCrabHand;

class CrabPatrol;
class CrabChase;
class CrabAttack;
class CrabEscape;

class EnemyCrab :public IEnemy
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	//�G�J�j�̘r
	std::unique_ptr<EnemyCrabHand> m_hand;
	//���
	EnemyState m_state;

	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_BoundingSphere;

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
	//�v���C���[�̃T�C�Y
	float m_size;
	//HP
	float m_health;

	//�v���C���[
	PlayerBody* m_player;

	//�X�e�[�g
	std::unique_ptr<CrabPatrol> m_patrol;
	std::unique_ptr<CrabChase> m_chase;
	std::unique_ptr<CrabAttack> m_attack;
	std::unique_ptr<CrabEscape> m_escape;

public:
	EnemyCrab(PlayerBody* player);
	~EnemyCrab()override;

	void Initialize(DirectX::SimpleMath::Vector3 position);
	void Update(float timer);
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
	//��Ԃ̎擾
	EnemyState GetState() { return m_state; }
	//��Ԃ̐ݒ�
	void SetEnemyState(EnemyState state) override { m_state = state; }
	//�G����������
	bool IsActive() override;
	//�_���[�W���󂯂�
	void TakeDamage(float damage)override { m_health -= damage; }
	//�o�E���f�B���O�X�t�B�A����
	DirectX::BoundingSphere CreateBoundingSphere(
		const float& radius) override;
	//�o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere& GetBodyBoundingSphere() override 
	{ return m_BoundingSphere; }
	// �o�E���f�B���O�X�t�B�A��`�悷��
	void DrawBoundingSphere() override;
	//�̗͂��擾
	float GetHP() const override{ return m_health; }

private:
	//�X�e�[�g�ύX
	void ChangeState();
	//�X�e�[�g�Ǘ�
	void UpdateState(float time);
};

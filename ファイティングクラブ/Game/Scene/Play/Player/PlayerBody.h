//--------------------------------------------------------------------------------------
// File: PlayerBody.h
//
// �v���C���[�{�̃N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"

class Stage;
class PlayerHand;

class PlayerBody
{
public:
	//�v���C���[�̏��
	enum PlayerState {
		NONE,   //�������Ă��Ȃ�
		ATTACK, //�U��
		DEAD    //���S
	};

private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	//�v���C���[�̘r
	std::unique_ptr<PlayerHand> m_hand;
	//�X�e�[�W�̃|�C���^
	Stage* m_stage;

	//�v���C���[���g�̕ϐ�
	//�v���C���[�̏�� 
	PlayerState m_state;
	// �v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_position;
	//�v���C���[�̑���
	DirectX::SimpleMath::Vector3 m_velocity;
	//�v���C���[�̉�]
	// �N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;
	//�X��
	DirectX::SimpleMath::Matrix m_rotateNormal;
	//�v���C���[�̃T�C�Y
	float m_size;
	//�v���C���[�̗̑�
	float m_health;
	//�v���C���[�̃X�^�~�i
	float m_stamina;
	//�v���C���[�̍U���N�[���^�C��
	float m_attackCoolTime;
	//�v���C���[�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//�}�E�X����n
	std::unique_ptr<DirectX::GeometricPrimitive> m_torus;
	// ���W
	DirectX::SimpleMath::Vector3 m_torusPosition;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_torusWorld;


public:
	PlayerBody(Stage* stage);
	~PlayerBody();

	void Initialize();
	void Update(float timer);
	void Render();
public:
	//�Q�[�^�[
	DirectX::SimpleMath::Vector3 GetPos() const { return m_position; }
	//���
	PlayerState GetState() { return m_state; }
	//�o�E���f�B���O�X�t�B�A����
	DirectX::BoundingSphere GetBoundingSphere(DirectX::SimpleMath::Vector3 center);
	//�̗͂��擾
	float GetHP() const { return m_health; }
	//�_���[�W���󂯂�
	void TakeDamage(float damage);
	//�X�^�~�i���擾
	float GetStamina()const { return m_stamina; }
private:
	//�L�[�{�[�h����
	void KeyBoardEvent();
	//�}�E�X����
	void MouseEvent();
};

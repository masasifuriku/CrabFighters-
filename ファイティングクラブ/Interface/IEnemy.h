/*
	@file	IEnemy.h
	@brief	�G�̃C���^�[�t�F�C�X�N���X
*/
#pragma once
#include "pch.h"

class IEnemy
{
public:
	//�G�̏��
	enum EnemyState 
	{
		NONE,
		Patrol,  //�v���C���[��T���ăp�g���[��
		Chase,	 //�����Ēǐ�
		Battle,	 //��풆
		Escape,	 //����
		DEAD     //���S
	};

public:
	//���݂̈ʒu�̓n��
	virtual DirectX::SimpleMath::Vector3 GetPos()const = 0;
	//�ʒu���󂯎��
	virtual void SetPos(DirectX::SimpleMath::Vector3 pos) = 0;
	//���݂̊p�x��n��
	virtual float GetAngle()const = 0;
	//�p�x���󂯎��
	virtual void SetAngle(float angle) = 0;
	//�G�̏�Ԃ�ݒ肷��
	virtual void SetEnemyState(EnemyState state) = 0;
	// �G����������
	virtual bool IsActive() = 0;
	//�_���[�W���󂯂�
	virtual void TakeDamage(float damage) = 0;
	//�����蔻�萶��
	// �o�E���f�B���O�X�t�B�A���쐬����
	virtual DirectX::BoundingSphere CreateBoundingSphere(const float& radius) = 0;
	//�o�E���f�B���O�X�t�B�A
	virtual DirectX::BoundingSphere& GetBodyBoundingSphere() = 0;
	// �o�E���f�B���O�X�t�B�A��`�悷��
	virtual void DrawBoundingSphere() = 0;
	//�̗͂��擾����
	virtual float GetHP()const = 0;
public:
	//���z�f�X�g���N�^
	virtual ~IEnemy() = default;
	//������
	virtual void Initialize(EnemyState state,DirectX::SimpleMath::Vector3 position) = 0;
	//�X�V
	virtual void Update(float elapsedTime) = 0;
	//�`��
	virtual void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal
	) = 0;
};

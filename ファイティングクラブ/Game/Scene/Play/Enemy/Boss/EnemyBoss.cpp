//--------------------------------------------------------------------------------------
// File: EnemyBoss.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBoss::EnemyBoss()
	:
	m_model{},
	m_state{ DEAD }, 
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_health{},
	m_angle{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// ���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Boss", L"Resources/Models/dice.cmo");
	//��Ԃ̐ݒ�
	m_state = state;
	//���W������������
	m_position = position;
	//���x
	m_velocity = Vector3::Zero;
	//��]
	m_rotate = Quaternion::FromToRotation(Vector3::UnitZ, -Vector3::UnitZ);
	//�s��
	m_world = Matrix::Identity;
	//�̗�
	m_health = 300.0f;
	//�p�x
	m_angle = 0.0f;
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void EnemyBoss::Update(float timer,Vector3 Ppos)
{
	UpdateState(timer,Ppos);
}

/// <summary>
/// �`��֐�
/// </summary>
void EnemyBoss::Render(
	Vector3 pos,
	Matrix normal
)
{
	m_position = pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(3.0f);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

	// ���f����`�悷��
	if (m_state != DEAD)
	{
		m_model->DrawModel("Boss", m_world);
	}
}

//������Ԃ����f����
bool EnemyBoss::IsActive()
{
	//��Ԃ����S�ȊO�Ȃ琶�����Ȃ̂�true��Ԃ�
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//�_���[�W���󂯂�
void EnemyBoss::TakeDamage(float damage)
{
	m_health -= damage;
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere EnemyBoss::GetBoundingSphere(Vector3 center)
{
	BoundingSphere sphere;
	sphere.Center = center;
	sphere.Radius = 1.8f;
	return sphere;
}

//�X�e�[�g�̍X�V
void EnemyBoss::UpdateState(float time, Vector3 player)
{
	switch (m_state)
	{
		case Patrol:
			BossPatrol(time);
			break;
		case Chase:
			BossChase(player);
			break;
		case Battle:
			BossBattle();
			break;
		case Escape:
			BossEscape(player);
			break;
		case DEAD:
			break;
		default:
			break;
	}
}

//�T���s��
void EnemyBoss::BossPatrol(float timer)
{
}
//�ǐՍs��
void EnemyBoss::BossChase(Vector3 pos)
{
}
//�퓬�s��
void EnemyBoss::BossBattle()
{
}
//�����s��
void EnemyBoss::BossEscape(Vector3 pos)
{
}

//--------------------------------------------------------------------------------------
// File: BossPatrol.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BossPatrol.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BossPatrol::BossPatrol(EnemyBoss* boss)
	:
	m_boss(boss),
	m_currentGoalNo{ 0 },
	m_isInside{ false }
{
	// �S�[���z����쐬����
	m_goals.emplace_back(Vector3{ -40.0f, -0.000008f, -40.0f });
	m_goals.emplace_back(Vector3{ 40.0f ,1.752317f ,40.0f });
	m_goals.emplace_back(Vector3{ -30.056952f, -0.902425f, -1.161875f });
	m_goals.emplace_back(Vector3{ -20.0f ,1.710116f, 30.0f });
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossPatrol::~BossPatrol()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void BossPatrol::Update()
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.35, Matrix::CreateRotationY(m_boss->GetAngle()));

	// �S�[���֌������x�N�g��
	Vector3 toGoal = m_goals[m_currentGoalNo] - m_boss->GetPos();

	// �^�[�Q�b�g�Ƃ̋������߂����Ȃ����
	if (toGoal.LengthSquared() > SPEED * SPEED)
	{
		// �ړ�����
		m_boss->SetPos(heading * SPEED);

		//�^�[�Q�b�g�̕����֏��X�ɉ�]����
		// �u�i�s�����x�N�g���v�Ɓu�^�[�Q�b�g�̕����v����cos�Ƃ��v�Z����
		float cosTheta = heading.Dot(toGoal) / (toGoal.Length() * heading.Length());

		// acos�̈����Ŏw��ł���͈͂́u-1�`1�v�Ȃ̂ŁA�l��␳����
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		// cos�Ƃ���Ƃ��v�Z����
		//** acos�̌��ʂ́u0�`�΁v
		float theta = std::acos(cosTheta);

		// �P�t���[���ł̉�]�p�𐧌��l�ȓ��ɕ␳����
		theta = std::min(0.1f, theta);

		if (heading.Cross(toGoal).y < 0.0f)
		{
			theta *= (-1.0f);
		}
		// �p�x���X�V����
		m_boss->SetAngle(theta);
		// �S�[���ɒB������A�S�[�������X�V����
		if (m_isInside == false && toGoal.Length() < 0.5f)
		{
			m_currentGoalNo++;
			m_currentGoalNo %= 4;
		}
	}
}
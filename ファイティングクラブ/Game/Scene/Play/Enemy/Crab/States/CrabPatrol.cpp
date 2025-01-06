//--------------------------------------------------------------------------------------
// File: CrabPatrol.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "CrabPatrol.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
CrabPatrol::CrabPatrol(EnemyCrab* crab)
	:
	m_crab(crab),
	m_currentGoalNo{ 0 },
	m_isInside{ false }
{
	// �S�[���z����쐬����
	m_goals.emplace_back(Vector3{ 20.677824f,   5.715546f,   21.750154f });
	m_goals.emplace_back(Vector3{ -21.150574f, -2.996116f,   21.016121f });
	m_goals.emplace_back(Vector3{ 20.612558f,   1.405255f,  -20.664967f });
	m_goals.emplace_back(Vector3{ -20.646391f, -3.127819f,  -22.142441f });
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CrabPatrol::~CrabPatrol()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void CrabPatrol::Update()
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3(0.1f, 0.0f, 0.0f), Matrix::CreateRotationY(m_crab->GetAngle()));

	// �S�[���֌������x�N�g��
	Vector3 toGoal = m_goals[m_currentGoalNo] - m_crab->GetPos();

	// �^�[�Q�b�g�Ƃ̋������߂����Ȃ����
	if (toGoal.LengthSquared() > SPEED * SPEED)
	{
		// �ړ�����
		m_crab->SetPos(heading * SPEED);

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
		m_crab->SetAngle(theta);
		// �S�[���ɒB������A�S�[�������X�V����
		if (m_isInside == false && toGoal.Length() < 0.5f)
		{
			m_currentGoalNo++;
			m_currentGoalNo %= 4;
		}
	}
}
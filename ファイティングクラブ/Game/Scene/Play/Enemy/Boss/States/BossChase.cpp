//--------------------------------------------------------------------------------------
// File: BossChase.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BossChase.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BossChase::BossChase(EnemyBoss* boss)
	:
	m_boss(boss)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossChase::~BossChase()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void BossChase::Update(Vector3 Ppos)
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_boss->GetAngle()));
	// �v���C���[�֌������x�N�g��
	Vector3 toTarget = Ppos - m_boss->GetPos();

	// �v���C���[�Ƃ̋������߂����Ȃ����
	if (toTarget.LengthSquared() > SPEED * SPEED)
	{
		// �ړ�����
		m_boss->SetPos(heading * SPEED);

		// �u�i�s�����x�N�g���v�Ɓu�^�[�Q�b�g�̕����v����cos�Ƃ��v�Z����
		float cosTheta = heading.Dot(toTarget) / (toTarget.Length() * heading.Length());

		// acos�̈����Ŏw��ł���͈͂́u-1�`1�v�Ȃ̂ŁA�l��␳����
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		// cos�Ƃ���Ƃ��v�Z����
		//** acos�̌��ʂ́u0�`�΁v
		float theta = std::acos(cosTheta);

		// �P�t���[���ł̉�]�p�𐧌��l�ȓ��ɕ␳����
		theta = std::min(0.1f, theta);

		// �E���ɍs�������ꍇ�͊p�x�̕�����t���ւ���
		if (heading.Cross(toTarget).y < 0.0f)
		{
			theta *= (-1.0f);
		}

		//�p�x���X�V����
		m_boss->SetAngle(theta);
	}
}
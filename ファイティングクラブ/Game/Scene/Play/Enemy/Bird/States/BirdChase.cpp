//--------------------------------------------------------------------------------------
// File: BirdChase.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BirdChase.h"
#include "Game/Scene/Play/Enemy/Bird/EnemyBird.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdChase::BirdChase(EnemyBird* bird)
	:
	m_bird(bird)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdChase::~BirdChase()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void BirdChase::Update(Vector3 Ppos)
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_bird->GetAngle()));
	// �v���C���[�֌������x�N�g��
	Vector3 toTarget = Ppos - m_bird->GetPos();

	// �v���C���[�Ƃ̋������߂����Ȃ����
	if (toTarget.LengthSquared() > SPEED * SPEED)
	{
		// �ړ�����
		m_bird->SetPos(heading * SPEED);

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
		m_bird->SetAngle(theta);
	}
}
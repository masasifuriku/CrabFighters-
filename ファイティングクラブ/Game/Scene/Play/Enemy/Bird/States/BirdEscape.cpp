//--------------------------------------------------------------------------------------
// File: BirdEscape.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BirdEscape.h"
#include "Game/Scene/Play/Enemy/Bird/EnemyBird.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdEscape::BirdEscape(EnemyBird* bird)
	:
	m_bird(bird)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEscape::~BirdEscape()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void BirdEscape::Update(DirectX::SimpleMath::Vector3 Ppos)
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_bird->GetAngle()));
	//�v���C���[���瓦����x�N�g��
	Vector3 awayFromPlayer = m_bird->GetPos() - Ppos;

	// �^�[�Q�b�g���牓������x�N�g�����v�Z
	float cosTheta = heading.Dot(awayFromPlayer) / (awayFromPlayer.Length() * heading.Length());

	// acos�̈����Ŏw��ł���͈͂́u-1�`1�v�Ȃ̂ŁA�l��␳����
	cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

	// cos�Ƃ���Ƃ��v�Z����
	float theta = std::acos(cosTheta);

	// �P�t���[���ł̉�]�p�𐧌��l�ȓ��ɕ␳����
	theta = std::min(0.1f, theta);

	// ���E�ǂ���ɉ�]���邩�����߂�
	if (heading.Cross(awayFromPlayer).y < 0.0f)
	{
		theta *= (-1.0f);
	}

	// �p�x���X�V����
	m_bird->SetAngle(theta);

	// ��������
	m_bird->SetPos(heading * SPEED);
}
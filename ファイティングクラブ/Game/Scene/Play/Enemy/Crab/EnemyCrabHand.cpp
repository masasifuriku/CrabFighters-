//--------------------------------------------------------------------------------------
// File: EnemyCrabHand.cpp
//
// �G�J�j�r�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrabHand.h"
#include "Game/Screen.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyCrabHand::EnemyCrabHand()
	:
	m_model{},
	m_rotate{},
	m_angle{},
	m_attackCount{},
	m_time{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyCrabHand::~EnemyCrabHand()
{
}

void EnemyCrabHand::Initialize()
{
	// �v���C���[���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("CrabRightHand", L"Resources/Models/CrabRightHand.cmo");

	//��]
	m_rotate = Quaternion::Identity;
	m_angle[0] = 0.0f;
	m_angle[1] = 10.0f;
	m_angle[2] = 20.0f;
	m_angle[3] = 30.0f;
	//�U�����[�V�����J�E���g
	m_attackCount = 0;
}

/// <summary>
/// �`��֐�
/// </summary>
void EnemyCrabHand::Render(Matrix world)
{
	//�̂̃��[���h�s��ɍ��킹��
	Matrix rotation = Matrix::CreateFromQuaternion(m_rotate);
	Matrix handworld = rotation * world;
	// ���f����`�悷��
	m_model->DrawModel("CrabRightHand",handworld);
}

//�U�����ɘr�𓮂���
void EnemyCrabHand::AttackMotion()
{
	// �z��C���f�b�N�X�Ǘ�
	static bool reverse = false;

	if (!reverse)
	{
		m_attackCount++;
		if (m_attackCount >= 3) // �Ō�̊p�x�ɒB������t������
		{
			m_attackCount = 3;
			reverse = true;
		}
	}
	else
	{
		m_attackCount--;
		if (m_attackCount <= 0) // �ŏ��̊p�x�ɖ߂�����i�s���������Z�b�g
		{
			m_attackCount = 0;
			reverse = false;
		}
	}
	// �N�H�[�^�j�I�����g���čU�����̘r�̉�]��ݒ�
	m_rotate = Quaternion::CreateFromAxisAngle(Vector3::UnitY, (XMConvertToRadians(m_angle[m_attackCount])));
}

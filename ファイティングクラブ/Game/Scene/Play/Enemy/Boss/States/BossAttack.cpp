//--------------------------------------------------------------------------------------
// File: BossAttack.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BossAttack.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BossAttack::BossAttack(EnemyBoss* boss)
	:
	m_boss(boss)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossAttack::~BossAttack()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void BossAttack::Update()
{
}
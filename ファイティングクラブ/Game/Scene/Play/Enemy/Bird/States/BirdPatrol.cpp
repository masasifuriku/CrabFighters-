//--------------------------------------------------------------------------------------
// File: BirdPatrol.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BirdPatrol.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BirdPatrol::BirdPatrol()
	:
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_angle{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdPatrol::~BirdPatrol()
{
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void BirdPatrol::Update(float timer,Vector3 Ppos)
{

}
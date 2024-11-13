//--------------------------------------------------------------------------------------
// File: BirdPatrol.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BirdPatrol.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
BirdPatrol::~BirdPatrol()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void BirdPatrol::Update(float timer,Vector3 Ppos)
{

}
//--------------------------------------------------------------------------------------
// File: BirdAttack.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BirdAttack.h"
#include "Game/Scene/Play/Enemy/Bird/EnemyBird.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BirdAttack::BirdAttack(EnemyBird* bird)
	:
	m_bird(bird)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdAttack::~BirdAttack()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void BirdAttack::Update()
{
}
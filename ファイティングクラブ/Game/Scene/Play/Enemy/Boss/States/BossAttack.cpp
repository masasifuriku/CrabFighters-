//--------------------------------------------------------------------------------------
// File: BossAttack.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BossAttack.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BossAttack::BossAttack(EnemyBoss* boss)
	:
	m_boss(boss)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossAttack::~BossAttack()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void BossAttack::Update()
{
}
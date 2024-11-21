//--------------------------------------------------------------------------------------
// File: CrabAttack.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "CrabAttack.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
CrabAttack::CrabAttack(EnemyCrab* crab,PlayerBody* player)
	:
	m_crab(crab),
	m_player(player),
	m_attackCoolTime{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
CrabAttack::~CrabAttack()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void CrabAttack::Update()
{
	
}
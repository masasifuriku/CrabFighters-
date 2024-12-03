//--------------------------------------------------------------------------------------
// File: CrabAttack.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "CrabAttack.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"
#include "Game/Scene/Play/Player/PlayerBody.h"

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
void CrabAttack::Update(float time)
{
	//攻撃クールタイム減少
	m_attackCoolTime -= time;
	//スペースを押したら
	if (m_attackCoolTime <= 0.0f)
	{
		//攻撃する
		m_player->TakeDamage(20.0f);
		//クールタイムを設定
		m_attackCoolTime = 1.0f;
	}
}
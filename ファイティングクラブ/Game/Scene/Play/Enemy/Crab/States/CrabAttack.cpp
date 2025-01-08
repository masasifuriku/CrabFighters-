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
#include "Game/Scene/Play/Enemy/Crab/EnemyCrabHand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
CrabAttack::CrabAttack(EnemyCrab* crab, PlayerBody* player, EnemyCrabHand* hand)
	:
	m_crab(crab),
	m_player(player),
	m_hand(hand),
	m_attackCoolTime{ 1.0f } ,
	m_attackCount{}
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
	if (m_attackCoolTime <= 0.0f)
	{
		//攻撃モーション
		m_hand->AttackMotion();
		//カウントを増やす
		m_attackCount++;
		//カウントが終わったら
		if (m_attackCount >= 8)
		{
			//攻撃する
			m_player->TakeDamage(1.0f);
			//カウントを戻す
			m_attackCount = 0;
			//クールタイムを設定
			m_attackCoolTime = 1.0f;
		}
	}
}
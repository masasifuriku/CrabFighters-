//--------------------------------------------------------------------------------------
// File: SharkAttack.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "SharkAttack.h"
#include "Game/Scene/Play/Enemy/Shark/EnemyShark.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
SharkAttack::SharkAttack(EnemyShark* shark)
	:
	m_shark(shark)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SharkAttack::~SharkAttack()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void SharkAttack::Update()
{
}
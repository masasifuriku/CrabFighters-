//--------------------------------------------------------------------------------------
// File: Player.cpp
//
// プレイヤークラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Player.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/UtilityMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	:
	m_model{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}

void Player::Initialize()
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void Player::Update()
{
}

/// <summary>
/// 描画関数
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Player::Render()
{
}

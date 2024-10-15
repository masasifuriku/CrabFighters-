//--------------------------------------------------------------------------------------
// File: Enemy.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
	:
	m_model{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void Enemy::Update()
{
	//m_position = m_velocity;
}

/// <summary>
/// 描画関数
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Enemy::Render()
{
}
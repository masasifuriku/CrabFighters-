//--------------------------------------------------------------------------------------
// File: EnemyBossBody.cpp
//
// ボス体クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBossBody.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"

#include "Libraries/Microsoft/DebugDraw.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBossBody::EnemyBossBody()
	:
	m_model{},
	m_BoundingSphere{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBossBody::~EnemyBossBody()
{
}

void EnemyBossBody::Initialize()
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Boss", L"Resources/Models/BossBody.cmo");
	// バウンディングスフィアを生成する
	m_BoundingSphere = CreateBoundingSphere(11.0f);
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyBossBody::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// 描画関数
/// </summary>
void EnemyBossBody::Render()
{
	Matrix world;
	m_model->DrawModel("Boss", world);
}

//バウンディングスフィア生成
DirectX::BoundingSphere EnemyBossBody::CreateBoundingSphere(const float& radius)
{
	// バウンディングスフィアを宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// バウンディングスフィアの半径を設定する
	turretBoundingSphere.Radius = radius;
	// バウンディングスフィアを返す
	return turretBoundingSphere;
}

// バウンディングスフィアを描画する
void EnemyBossBody::DrawBoundingSphere()
{
	// 既定色を設定する
	DirectX::XMVECTOR color = DirectX::Colors::Yellow;
	auto batch = Graphics::GetInstance();
	// プリミティブ描画を開始する
	batch->DrawPrimitiveBegin(batch->GetViewMatrix(), batch->GetProjectionMatrix());
	// 砲塔の境界球を描画する
	DX::Draw(batch->GetPrimitiveBatch(), m_BoundingSphere, color);
	// プリミティブ描画を終了する
	batch->DrawPrimitiveEnd();
}
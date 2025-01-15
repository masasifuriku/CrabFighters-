//--------------------------------------------------------------------------------------
// File: EnemyBossRightLeg.cpp
//
// ボス右足クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBossRightLeg.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"

#include "Libraries/Microsoft/DebugDraw.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBossRightLeg::EnemyBossRightLeg()
	:
	m_model{},
	m_BoundingSphere{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBossRightLeg::~EnemyBossRightLeg()
{
}

void EnemyBossRightLeg::Initialize()
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Boss", L"Resources/Models/BossRightLeg.cmo");
	// バウンディングスフィアを生成する
	m_BoundingSphere = CreateBoundingSphere(11.0f);
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyBossRightLeg::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// 描画関数
/// </summary>
void EnemyBossRightLeg::Render()
{
	Matrix world;
	m_model->DrawModel("Boss", world);
}

//バウンディングスフィア生成
DirectX::BoundingSphere EnemyBossRightLeg::CreateBoundingSphere(const float& radius)
{
	// バウンディングスフィアを宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// バウンディングスフィアの半径を設定する
	turretBoundingSphere.Radius = radius;
	// バウンディングスフィアを返す
	return turretBoundingSphere;
}

// バウンディングスフィアを描画する
void EnemyBossRightLeg::DrawBoundingSphere()
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
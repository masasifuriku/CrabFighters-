//--------------------------------------------------------------------------------------
// File: PlayerHand.cpp
//
// プレイヤークラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "PlayerHand.h"
#include "Game/Screen.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Input.h"

#include "Libraries/Microsoft/DebugDraw.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerHand::PlayerHand()
	:
	m_model{},
	m_BoundingSphere{},
	m_rotate{},
	m_angle{},
	m_attackCount{},
	m_time{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHand::~PlayerHand()
{
}

void PlayerHand::Initialize()
{
	// プレイヤーモデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("CrabRightHand", L"Resources/Models/CrabRightHand.cmo");

	//回転
	m_rotate = Quaternion::Identity;
	//角度設定
	m_angle = { 0.0f,10.0f,20.0f,30.0f,40.0f };
	//攻撃モーションカウント
	m_attackCount = 0;

	// バウンディングスフィアを生成する
	m_BoundingSphere = CreateBoundingSphere(0.5f);
}

/// <summary>
/// 描画関数
/// </summary>
void PlayerHand::Render(Matrix world)
{
	Matrix rotation, translation;
	//攻撃時に腕を回転
	rotation = Matrix::CreateFromQuaternion(m_rotate);
	//腕を体のワールド座標と合わせる
	Matrix handWorld = rotation * world;

	//バウンディングスフィアを腕に合わせる
	translation = Matrix::CreateTranslation(-9.0f, 0.0f, 9.0f);
	//腕に合わせたのと体に合わせたのを合わせる
	Matrix handSphere = translation * handWorld;
	// バウンディングスフィアの中心を更新
	Vector3 handPosition = Vector3::Transform(Vector3(1.0f, 0.0f, 1.0f), handSphere);
	m_BoundingSphere.Center = handPosition;

	// モデルを描画する
	m_model->DrawModel("CrabRightHand",handWorld);
	DrawBoundingSphere();
}

//攻撃時に腕を動かす
void PlayerHand::AttackMotion()
{
	// 配列インデックス管理
	static bool reverse = false;

	if (!reverse)
	{
		m_attackCount++;
		if (m_attackCount >= 4) // 最後の角度に達したら逆方向へ
		{
			m_attackCount = 4;
			reverse = true;
		}
	}
	else
	{
		m_attackCount--;
		if (m_attackCount <= 0) // 最初の角度に戻ったら進行方向をリセット
		{
			m_attackCount = 0;
			reverse = false;
		}
	}
	// クォータニオンを使って攻撃時の腕の回転を設定
	m_rotate = Quaternion::CreateFromAxisAngle(Vector3::UnitY, (XMConvertToRadians(m_angle[m_attackCount])));
}

//バウンディングスフィア生成
DirectX::BoundingSphere PlayerHand::CreateBoundingSphere(const float& radius)
{
	// バウンディングスフィアを宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// バウンディングスフィアの半径を設定する
	turretBoundingSphere.Radius = radius;
	// バウンディングスフィアを返す
	return turretBoundingSphere;
}

// バウンディングスフィアを描画する
void PlayerHand::DrawBoundingSphere()
{
	// 既定色を設定する
	DirectX::XMVECTOR color = DirectX::Colors::Black;
	auto batch = Graphics::GetInstance();
	// プリミティブ描画を開始する
	batch->DrawPrimitiveBegin(batch->GetViewMatrix(), batch->GetProjectionMatrix());
	// 砲塔の境界球を描画する
	DX::Draw(batch->GetPrimitiveBatch(), m_BoundingSphere, color);
	// プリミティブ描画を終了する
	batch->DrawPrimitiveEnd();
}
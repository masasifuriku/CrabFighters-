//--------------------------------------------------------------------------------------
// File: PlayerHand.cpp
//
// プレイヤークラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "PlayerHand.h"
#include "Game/Screen.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerHand::PlayerHand()
	:
	m_model{},
	m_rotate{}
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
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void PlayerHand::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
	//腕を元に戻す
	m_rotate = Quaternion::Identity;
}

/// <summary>
/// 描画関数
/// </summary>
void PlayerHand::Render(Matrix world)
{
	//体のワールド行列に合わせる
	Matrix rotation = Matrix::CreateFromQuaternion(m_rotate);
	Matrix handworld = rotation * world;
	// モデルを描画する
	m_model->DrawModel("CrabRightHand",handworld);
}

//攻撃時に腕を動かす
void PlayerHand::AttackMotion()
{
	// クォータニオンを使って攻撃時の腕の回転を設定
	m_rotate = Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(30.0f));
}

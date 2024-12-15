//--------------------------------------------------------------------------------------
// File: EnemyCrabHand.cpp
//
// 敵カニ腕クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrabHand.h"
#include "Game/Screen.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyCrabHand::EnemyCrabHand()
	:
	m_model{},
	m_rotate{},
	m_angle{},
	m_attackCount{},
	m_time{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyCrabHand::~EnemyCrabHand()
{
}

void EnemyCrabHand::Initialize()
{
	// プレイヤーモデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("CrabRightHand", L"Resources/Models/CrabRightHand.cmo");

	//回転
	m_rotate = Quaternion::Identity;
	m_angle[0] = 0.0f;
	m_angle[1] = 10.0f;
	m_angle[2] = 20.0f;
	m_angle[3] = 30.0f;
	//攻撃モーションカウント
	m_attackCount = 0;
}

/// <summary>
/// 描画関数
/// </summary>
void EnemyCrabHand::Render(Matrix world)
{
	//体のワールド行列に合わせる
	Matrix rotation = Matrix::CreateFromQuaternion(m_rotate);
	Matrix handworld = rotation * world;
	// モデルを描画する
	m_model->DrawModel("CrabRightHand",handworld);
}

//攻撃時に腕を動かす
void EnemyCrabHand::AttackMotion()
{
	// 配列インデックス管理
	static bool reverse = false;

	if (!reverse)
	{
		m_attackCount++;
		if (m_attackCount >= 3) // 最後の角度に達したら逆方向へ
		{
			m_attackCount = 3;
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

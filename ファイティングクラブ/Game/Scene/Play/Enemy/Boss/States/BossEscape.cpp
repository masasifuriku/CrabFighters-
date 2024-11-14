//--------------------------------------------------------------------------------------
// File: BossEscape.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BossEscape.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BossEscape::BossEscape(EnemyBoss* boss)
	:
	m_boss(boss)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossEscape::~BossEscape()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void BossEscape::Update(DirectX::SimpleMath::Vector3 Ppos)
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_boss->GetAngle()));
	//プレイヤーから逃げるベクトル
	Vector3 awayFromPlayer = m_boss->GetPos() - Ppos;

	// ターゲットから遠ざかるベクトルを計算
	float cosTheta = heading.Dot(awayFromPlayer) / (awayFromPlayer.Length() * heading.Length());

	// acosの引数で指定できる範囲は「-1～1」なので、値を補正する
	cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

	// cosθからθを計算する
	float theta = std::acos(cosTheta);

	// １フレームでの回転角を制限値以内に補正する
	theta = std::min(0.1f, theta);

	// 左右どちらに回転するかを決める
	if (heading.Cross(awayFromPlayer).y < 0.0f)
	{
		theta *= (-1.0f);
	}

	// 角度を更新する
	m_boss->SetAngle(theta);

	// 逃走する
	m_boss->SetPos(heading * SPEED);
}
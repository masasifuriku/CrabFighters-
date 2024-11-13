//--------------------------------------------------------------------------------------
// File: CrabEscape.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "CrabEscape.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
CrabEscape::CrabEscape(EnemyCrab* crab)
	:
	m_crab(crab)
{
}

/// <summary>
/// デストラクタ
/// </summary>
CrabEscape::~CrabEscape()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void CrabEscape::Update(DirectX::SimpleMath::Vector3 Ppos)
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_crab->GetAngle()));
	//プレイヤーから逃げるベクトル
	Vector3 awayFromPlayer = m_crab->GetPos() - Ppos;

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
	m_crab->SetAngle(theta);

	// 逃走する
	m_crab->SetPos(heading * SPEED);
}
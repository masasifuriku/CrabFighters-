//--------------------------------------------------------------------------------------
// File: BossChase.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "BossChase.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BossChase::BossChase(EnemyBoss* boss)
	:
	m_boss(boss)
{
}

/// <summary>
/// デストラクタ
/// </summary>
BossChase::~BossChase()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void BossChase::Update(Vector3 Ppos)
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_boss->GetAngle()));
	// プレイヤーへ向かうベクトル
	Vector3 toTarget = Ppos - m_boss->GetPos();

	// プレイヤーとの距離が近すぎなければ
	if (toTarget.LengthSquared() > SPEED * SPEED)
	{
		// 移動する
		m_boss->SetPos(heading * SPEED);

		// 「進行方向ベクトル」と「ターゲットの方向」からcosθを計算する
		float cosTheta = heading.Dot(toTarget) / (toTarget.Length() * heading.Length());

		// acosの引数で指定できる範囲は「-1～1」なので、値を補正する
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		// cosθからθを計算する
		//** acosの結果は「0～π」
		float theta = std::acos(cosTheta);

		// １フレームでの回転角を制限値以内に補正する
		theta = std::min(0.1f, theta);

		// 右側に行きたい場合は角度の符号を付け替える
		if (heading.Cross(toTarget).y < 0.0f)
		{
			theta *= (-1.0f);
		}

		//角度を更新する
		m_boss->SetAngle(theta);
	}
}
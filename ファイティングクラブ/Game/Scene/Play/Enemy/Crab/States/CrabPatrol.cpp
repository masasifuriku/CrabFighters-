//--------------------------------------------------------------------------------------
// File: CrabPatrol.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "CrabPatrol.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
CrabPatrol::CrabPatrol(EnemyCrab* crab)
	:
	m_crab(crab),
	m_currentGoalNo{ 0 },
	m_isInside{ false }
{
	// ゴール配列を作成する
	m_goals.emplace_back(Vector3{ 20.677824f,   5.715546f,   21.750154f });
	m_goals.emplace_back(Vector3{ -21.150574f, -2.996116f,   21.016121f });
	m_goals.emplace_back(Vector3{ 20.612558f,   1.405255f,  -20.664967f });
	m_goals.emplace_back(Vector3{ -20.646391f, -3.127819f,  -22.142441f });
}

/// <summary>
/// デストラクタ
/// </summary>
CrabPatrol::~CrabPatrol()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void CrabPatrol::Update()
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3(0.1f, 0.0f, 0.0f), Matrix::CreateRotationY(m_crab->GetAngle()));

	// ゴールへ向かうベクトル
	Vector3 toGoal = m_goals[m_currentGoalNo] - m_crab->GetPos();

	// ターゲットとの距離が近すぎなければ
	if (toGoal.LengthSquared() > SPEED * SPEED)
	{
		// 移動する
		m_crab->SetPos(heading * SPEED);

		//ターゲットの方向へ徐々に回転する
		// 「進行方向ベクトル」と「ターゲットの方向」からcosθを計算する
		float cosTheta = heading.Dot(toGoal) / (toGoal.Length() * heading.Length());

		// acosの引数で指定できる範囲は「-1～1」なので、値を補正する
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		// cosθからθを計算する
		//** acosの結果は「0～π」
		float theta = std::acos(cosTheta);

		// １フレームでの回転角を制限値以内に補正する
		theta = std::min(0.1f, theta);

		if (heading.Cross(toGoal).y < 0.0f)
		{
			theta *= (-1.0f);
		}
		// 角度を更新する
		m_crab->SetAngle(theta);
		// ゴールに達したら、ゴール情報を更新する
		if (m_isInside == false && toGoal.Length() < 0.5f)
		{
			m_currentGoalNo++;
			m_currentGoalNo %= 4;
		}
	}
}
//--------------------------------------------------------------------------------------
// File: SharkPatrol.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "SharkPatrol.h"
#include "Game/Scene/Play/Enemy/Shark/EnemyShark.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
SharkPatrol::SharkPatrol(EnemyShark* shark)
	:
	m_shark(shark),
	m_currentGoalNo{ 0 },
	m_isInside{ false }
{
	// ゴール配列を作成する
	m_goals.emplace_back(Vector3{ -40.0f, -0.000008f, -40.0f });
	m_goals.emplace_back(Vector3{ 40.0f ,1.752317f ,40.0f });
	m_goals.emplace_back(Vector3{ -30.056952f, -0.902425f, -1.161875f });
	m_goals.emplace_back(Vector3{ -20.0f ,1.710116f, 30.0f });
}

/// <summary>
/// デストラクタ
/// </summary>
SharkPatrol::~SharkPatrol()
{
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void SharkPatrol::Update()
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.35, Matrix::CreateRotationY(m_shark->GetAngle()));

	// ゴールへ向かうベクトル
	Vector3 toGoal = m_goals[m_currentGoalNo] - m_shark->GetPos();

	// ターゲットとの距離が近すぎなければ
	if (toGoal.LengthSquared() > SPEED * SPEED)
	{
		// 移動する
		m_shark->SetPos(heading * SPEED);

		//ターゲットの方向へ徐々に回転する
		// 「進行方向ベクトル」と「ターゲットの方向」からcosθを計算する
		float cosTheta = heading.Dot(toGoal) / (toGoal.Length() * heading.Length());

		// acosの引数で指定できる範囲は「-1〜1」なので、値を補正する
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		// cosθからθを計算する
		//** acosの結果は「0〜π」
		float theta = std::acos(cosTheta);

		// １フレームでの回転角を制限値以内に補正する
		theta = std::min(0.1f, theta);

		if (heading.Cross(toGoal).y < 0.0f)
		{
			theta *= (-1.0f);
		}
		// 角度を更新する
		m_shark->SetAngle(theta);
		// ゴールに達したら、ゴール情報を更新する
		if (m_isInside == false && toGoal.Length() < 0.5f)
		{
			m_currentGoalNo++;
			m_currentGoalNo %= 4;
		}
	}
}
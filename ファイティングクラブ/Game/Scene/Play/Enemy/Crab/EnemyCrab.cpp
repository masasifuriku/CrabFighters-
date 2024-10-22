//--------------------------------------------------------------------------------------
// File: EnemyCrab.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrab.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyCrab::EnemyCrab()
	:
	m_model{},
	m_state{ DEAD }, 
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_angle{},
	m_currentGoalNo{},
	m_goals{},
	m_isInside{},
	m_health{},
	m_count{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyCrab::~EnemyCrab()
{
}

void EnemyCrab::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("dice", L"Resources/Models/dice.cmo");
	//状態の設定
	m_state = state;
	//座標を初期化する
	m_position = position;
	//速度
	m_velocity = Vector3::Zero;
	//回転
	m_rotate = Quaternion::FromToRotation(Vector3::UnitZ, -Vector3::UnitZ);
	//行列
	m_world = Matrix::Identity;
	//角度
	m_angle = 0.0f;

	// ゴール番号
	m_currentGoalNo = 0;
	// ゴール配列を作成する
	m_goals.emplace_back(Vector3{ -40.0f, -0.000008f, -40.0f });
	m_goals.emplace_back(Vector3{ 40.0f ,1.752317f ,40.0f });
	m_goals.emplace_back(Vector3{ -30.056952f, -0.902425f, -1.161875f });
	m_goals.emplace_back(Vector3{ -20.0f ,1.710116f, 30.0f });
	// 発見フラグを初期化する
	m_isInside = false;
	//HP
	m_health = 100.0f;
	m_count = 0.0f;

	/*std::vector<Vector3> vec;

	vec.emplace_back(Vector3::Zero);
	vec.emplace_back(Vector3::Zero);
	vec.emplace_back(Vector3::Zero);
	vec.emplace_back(Vector3::Zero);

	m_goals2.push_back(vec);
	m_goals2.push_back(vec);*/
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyCrab::Update(float timer,Vector3 Ppos)
{
	UpdateState(timer,Ppos);
}

/// <summary>
/// 描画関数
/// </summary>
void EnemyCrab::Render(
	Vector3 pos,
	Matrix normal
)
{
	m_position = pos;
	Matrix rotation, translation;
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = rotation * normal * translation;

	// モデルを描画する
	if (m_state != DEAD)
	{
		m_model->DrawModel("dice",m_world);
	}
}

//生存状態か判断する
bool EnemyCrab::IsActive()
{
	//状態が死亡以外なら生存中なのでtrueを返す
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//ダメージを受ける
void EnemyCrab::TakeDamage(float damage)
{
	m_health -= damage;
}

//バウンディングスフィア生成
DirectX::BoundingSphere EnemyCrab::GetBoundingSphere(Vector3 center)
{
	BoundingSphere sphere;
	sphere.Center = center;
	sphere.Radius = 0.6f;
	return sphere;
}

//ステートの更新
void EnemyCrab::UpdateState(float time, Vector3 player)
{
	switch (m_state)
	{
		case Patrol:
			CrabPatrol(time);
			break;
		case Chase:
			CrabChase(player);
			break;
		case Battle:
			CrabBattle();
			break;
		case Escape:
			CrabEscape(player);
			break;
		case DEAD:
			break;
		default:
			break;
	}
}

//探索行動
void EnemyCrab::CrabPatrol(float timer)
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.35, Matrix::CreateRotationY(m_angle));

	// ゴールへ向かうベクトル
	Vector3 toGoal = m_goals[m_currentGoalNo] - m_position;

	// ターゲットとの距離が近すぎなければ
	if (toGoal.LengthSquared() > SPEED * SPEED)
	{
		// 移動する
		m_position += (heading * SPEED);

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
		m_angle += theta;
		// ゴールに達したら、ゴール情報を更新する
		if (m_isInside == false && toGoal.Length() < 0.5f)
		{
			m_currentGoalNo++;
			m_currentGoalNo %= 4;
		}
	}
	//ガチランダム
	//m_count += timer;
	//if (m_count >= 2.0f)
	//{
	//	// ランダムな方向に移動
	//	float randomX = (rand() % 200 - 100);
	//	float randomZ = (rand() % 200 - 100);
	//	m_count = 0.0f;
	//	// ランダムな方向に速度ベクトルを設定
	//	m_velocity = Vector3(randomX, 0.0f, randomZ);
	//}
	//// 速度ベクトルを正規化し、速度を乗じる
	//m_velocity.Normalize();
	//// ポジションを更新
	//m_position += m_velocity * timer;
	//// 進行方向に向けて回転
	////m_rotate = Quaternion::CreateFromRotationMatrix(Matrix::CreateLookAt(Vector3::Zero, m_velocity, Vector3::Up));
}
//追跡行動
void EnemyCrab::CrabChase(Vector3 pos)
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_angle));
	// プレイヤーへ向かうベクトル
	Vector3 toTarget = pos - m_position;

	// プレイヤーとの距離が近すぎなければ
	if (toTarget.LengthSquared() > SPEED * SPEED)
	{
		// 移動する
		m_position += (heading * SPEED);

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
		m_angle += theta;
	}
}
//戦闘行動
void EnemyCrab::CrabBattle()
{

}
//逃走行動
void EnemyCrab::CrabEscape(Vector3 pos)
{
	// 進行方向ベクトル
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_angle));
	//プレイヤーから逃げるベクトル
	Vector3 awayFromPlayer = m_position - pos;

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
	m_angle += theta;

	// 逃走する
	m_position += heading * SPEED;
}

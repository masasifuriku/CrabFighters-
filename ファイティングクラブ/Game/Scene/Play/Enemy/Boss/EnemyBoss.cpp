//--------------------------------------------------------------------------------------
// File: EnemyBoss.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBoss.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBoss::EnemyBoss()
	:
	m_model{},
	m_state{ DEAD }, 
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_health{},
	m_angle{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Boss", L"Resources/Models/dice.cmo");
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
	//体力
	m_health = 300.0f;
	//角度
	m_angle = 0.0f;
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyBoss::Update(float timer,Vector3 Ppos)
{
	UpdateState(timer,Ppos);
}

/// <summary>
/// 描画関数
/// </summary>
void EnemyBoss::Render(
	Vector3 pos,
	Matrix normal
)
{
	m_position = pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(3.0f);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

	// モデルを描画する
	if (m_state != DEAD)
	{
		m_model->DrawModel("Boss", m_world);
	}
}

//生存状態か判断する
bool EnemyBoss::IsActive()
{
	//状態が死亡以外なら生存中なのでtrueを返す
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//ダメージを受ける
void EnemyBoss::TakeDamage(float damage)
{
	m_health -= damage;
}

//バウンディングスフィア生成
DirectX::BoundingSphere EnemyBoss::GetBoundingSphere(Vector3 center)
{
	BoundingSphere sphere;
	sphere.Center = center;
	sphere.Radius = 1.8f;
	return sphere;
}

//ステートの更新
void EnemyBoss::UpdateState(float time, Vector3 player)
{
	switch (m_state)
	{
		case Patrol:
			BossPatrol(time);
			break;
		case Chase:
			BossChase(player);
			break;
		case Battle:
			BossBattle();
			break;
		case Escape:
			BossEscape(player);
			break;
		case DEAD:
			break;
		default:
			break;
	}
}

//探索行動
void EnemyBoss::BossPatrol(float timer)
{
}
//追跡行動
void EnemyBoss::BossChase(Vector3 pos)
{
}
//戦闘行動
void EnemyBoss::BossBattle()
{
}
//逃走行動
void EnemyBoss::BossEscape(Vector3 pos)
{
}

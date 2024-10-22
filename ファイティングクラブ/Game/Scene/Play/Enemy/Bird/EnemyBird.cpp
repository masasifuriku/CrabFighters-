//--------------------------------------------------------------------------------------
// File: EnemyBird.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBird.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBird::EnemyBird()
	:
	m_model{},
	m_state{ DEAD }, 
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_angle{},
	m_health{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBird::~EnemyBird()
{
}

void EnemyBird::Initialize(
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
	//HP
	m_health = 100.0f;
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyBird::Update(float timer,Vector3 Ppos)
{
	//m_position = m_velocity;
	if (m_health <= 0.0f)
	{
		m_state = DEAD;
	}
}

/// <summary>
/// 描画関数
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void EnemyBird::Render(
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
		m_model->DrawModel("dice", m_world);
	}
}

//生存状態か判断する
bool EnemyBird::IsActive()
{
	//状態が死亡以外なら生存中なのでtrueを返す
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//ダメージを受ける
void EnemyBird::TakeDamage(float damage)
{
	m_health -= damage;
}

//バウンディングスフィア生成
DirectX::BoundingSphere EnemyBird::GetBoundingSphere(Vector3 center)
{
	BoundingSphere sphere;
	sphere.Center = center;
	sphere.Radius = 0.6f;
	return sphere;
}
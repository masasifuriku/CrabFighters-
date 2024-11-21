//--------------------------------------------------------------------------------------
// File: EnemyShark.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyShark.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/Shark/States/SharkPatrol.h"
#include "Game/Scene/Play/Enemy/Shark/States/SharkChase.h"
#include "Game/Scene/Play/Enemy/Shark/States/SharkAttack.h"
#include "Game/Scene/Play/Enemy/Shark/States/SharkEscape.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyShark::EnemyShark(PlayerBody* player)
	:
	m_model{},
	m_state{ DEAD },
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_angle{},
	m_health{},
	m_player{ player },
	m_patrol{},
	m_chase{},
	m_attack{},
	m_escape{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyShark::~EnemyShark()
{
}

void EnemyShark::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("dice", L"Resources/Models/shark.cmo");
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

	//ステート
	m_patrol = std::make_unique<SharkPatrol>(this);
	m_chase  = std::make_unique<SharkChase>(this);
	m_attack = std::make_unique<SharkAttack>(this);
	m_escape = std::make_unique<SharkEscape>(this);
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyShark::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
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
void EnemyShark::Render(
	Vector3 pos,
	Matrix normal
)
{
	m_position = pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(0.01f);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

	// モデルを描画する
	if (m_state != DEAD)
	{
		m_model->DrawModel("dice", m_world);
	}
}

//生存状態か判断する
bool EnemyShark::IsActive()
{
	//状態が死亡以外なら生存中なのでtrueを返す
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//ダメージを受ける
void EnemyShark::TakeDamage(float damage)
{
	m_health -= damage;
}

//バウンディングスフィア生成
DirectX::BoundingSphere EnemyShark::GetBoundingSphere(Vector3 center)
{
	BoundingSphere sphere;
	sphere.Center = center;
	sphere.Radius = 0.6f;
	return sphere;
}

//ステートの更新
void EnemyShark::UpdateState()
{
	switch (m_state)
	{
		case Patrol:
			m_patrol->Update();
			break;
		case Chase:
			m_chase->Update(m_player->GetPos());
			break;
		case Battle:
			m_attack->Update();
			break;
		case Escape:
			m_escape->Update(m_player->GetPos());
			break;
		case DEAD:
			break;
		default:
			break;
	}
}
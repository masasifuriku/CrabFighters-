//--------------------------------------------------------------------------------------
// File: EnemyBoss.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBoss.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossPatrol.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossChase.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossAttack.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossEscape.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Framework/Collision.h"

#include "Libraries/Microsoft/DebugDraw.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBoss::EnemyBoss(PlayerBody* player)
	:
	m_model{},
	m_state{ DEAD }, 
	m_BoundingSphere{},
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_health{},
	m_angle{},
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
EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::Initialize(DirectX::SimpleMath::Vector3 position)
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Boss", L"Resources/Models/dice.cmo");
	//状態の設定
	m_state = NONE;
	// バウンディングスフィアを生成する
	m_BoundingSphere = CreateBoundingSphere(11.0f);
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

	//ステート
	m_patrol = std::make_unique<BossPatrol>(this);
	m_chase  = std::make_unique<BossChase>(this);
	m_attack = std::make_unique<BossAttack>(this);
	m_escape = std::make_unique<BossEscape>(this);

	Collision::GetInstance()->SetBoss(this);
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyBoss::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
	UpdateState();
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
DirectX::BoundingSphere EnemyBoss::CreateBoundingSphere(const float& radius)
{
	// バウンディングスフィアを宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// バウンディングスフィアの半径を設定する
	turretBoundingSphere.Radius = radius;
	// バウンディングスフィアを返す
	return turretBoundingSphere;
}

// バウンディングスフィアを描画する
void EnemyBoss::DrawBoundingSphere()
{
	// 既定色を設定する
	DirectX::XMVECTOR color = DirectX::Colors::Yellow;
	auto batch = Graphics::GetInstance();
	// プリミティブ描画を開始する
	batch->DrawPrimitiveBegin(batch->GetViewMatrix(), batch->GetProjectionMatrix());
	// 砲塔の境界球を描画する
	DX::Draw(batch->GetPrimitiveBatch(), m_BoundingSphere, color);
	// プリミティブ描画を終了する
	batch->DrawPrimitiveEnd();
}

void EnemyBoss::ChangeState()
{
	//プレイヤーとボスの位置
	Vector3 Ppos = m_player->GetPos();
	Vector3 Bpos = m_position;
	//プレイヤーとボスの距離
	float dx = Ppos.x - Bpos.x;
	float dy = Ppos.y - Bpos.y;
	float dz = Ppos.z - Bpos.z;
	float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
	//ボスの追跡範囲
	float SearchRande = 5.0f;
	//ステートをパトロールにする
	if (distance >= SearchRande)
	{
		m_state = Patrol;
	}
	//ステートを追跡にする
	else if (distance <= SearchRande)
	{
		m_state = Chase;
	}
	//ステートを逃走にする
	if (m_health <= 20.0f)
	{
		m_state = Escape;
	}
	//ステートを死亡にする
	if (m_health <= 0.0f)
	{
		m_state = DEAD;
	}
	//プレイヤーからボスへの攻撃
	if (Collision::GetInstance()->CheckHitAttackPlayerToBoss())
	{
		//プレイヤーの状態が攻撃なら敵にダメージが入る
		if (m_player->GetState() == PlayerBody::ATTACK)
		{
			TakeDamage(5.0f);
		}
	}
}

//ステートの更新
void EnemyBoss::UpdateState()
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
//--------------------------------------------------------------------------------------
// File: EnemyCrab.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrab.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrabHand.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabPatrol.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabChase.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabAttack.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabEscape.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Libraries/Microsoft/DebugDraw.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyCrab::EnemyCrab(PlayerBody* player)
	:
	m_model{},
	m_hand{},
	m_state{ DEAD }, 
	m_BoundingSphere{},
	m_position{},
	m_rotate{},
	m_world{},
	m_angle{},
	m_size{},
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
EnemyCrab::~EnemyCrab()
{
}

void EnemyCrab::Initialize(DirectX::SimpleMath::Vector3 position)
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("crab", L"Resources/Models/ogani-.cmo");
	//プレイヤーの腕
	m_hand = std::make_unique<EnemyCrabHand>();
	m_hand->Initialize();
	//状態の設定
	m_state = NONE;
	// バウンディングスフィアを生成する
	m_BoundingSphere = CreateBoundingSphere(0.9f);
	//座標を初期化する
	m_position = position;
	//回転
	m_rotate = Quaternion::Identity;
	//行列
	m_world = Matrix::Identity;
	//角度
	m_angle = 0.0f;
	//サイズ
	m_size = 0.08f;
	//HP
	m_health = 100.0f;

	//ステート
	m_patrol = std::make_unique<CrabPatrol>(this);
	m_chase  = std::make_unique<CrabChase>(this);
	m_attack = std::make_unique<CrabAttack>(this, m_player,m_hand.get());
	m_escape = std::make_unique<CrabEscape>(this);

	Collision::GetInstance()->SetCrab(this);
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void EnemyCrab::Update(float timer)
{
	ChangeState();
	UpdateState(timer);
}

/// <summary>
/// 描画関数
/// </summary>
void EnemyCrab::Render(
	Vector3 pos,
	Matrix normal
)
{
	//ステージとの判定
	m_position = pos;
	//バウンディングスフィアの中心点を設定
	m_BoundingSphere.Center = m_position;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(m_size);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

	// モデルを描画する
	if (m_state != DEAD)
	{
		m_model->DrawModel("crab",m_world);
		m_hand->Render(m_world);
		//DrawBoundingSphere();
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

//バウンディングスフィア生成
DirectX::BoundingSphere EnemyCrab::CreateBoundingSphere(const float& radius)
{
	// バウンディングスフィアを宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// バウンディングスフィアの半径を設定する
	turretBoundingSphere.Radius = radius;
	// バウンディングスフィアを返す
	return turretBoundingSphere;
}

// バウンディングスフィアを描画する
void EnemyCrab::DrawBoundingSphere()
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

void EnemyCrab::ChangeState()
{
	//敵のステート管理
	//プレイヤーと敵の位置
	Vector3 Ppos = m_player->GetPos();
	Vector3 Cpos = m_position;
	//プレイヤーと敵の距離
	float dx = Ppos.x - Cpos.x;
	float dy = Ppos.y - Cpos.y;
	float dz = Ppos.z - Cpos.z;
	float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
	//敵の追跡範囲
	float SearchRange = 5.0f;
	//ステートをパトロールにする
	if (distance >= SearchRange)
	{
		m_state = Patrol;
	}
	//ステートを追跡にする
	else if (distance <= SearchRange)
	{
		m_state = Chase;
	}
	//ステートを攻撃する
	if (Collision::GetInstance()->CheckHitAttackCrabsToPlayer())
	{
		m_state = Battle;
	}
	//ステートを逃走にする
	if (m_health <= 20.0f)
	{
		m_state = Escape;
		if (distance >= 15.0f)
		{
			m_state = Patrol;
		}
	}
	//ステートを死亡にする
	if (m_health <= 0.0f)
	{
		m_state = DEAD;
	}
	//プレイヤーからカニへの攻撃
	if (Collision::GetInstance()->CheckHitAttackPlayerToCrab())
	{
		//プレイヤーの状態が攻撃なら敵にダメージが入る
		if (m_player->GetState() == PlayerBody::ATTACK)
		{
			TakeDamage(5.0f);
		}
	}
}

//ステートの更新
void EnemyCrab::UpdateState(float time)
{
	switch (m_state)
	{
		case NONE:
			break;
		case Patrol:
			m_patrol->Update();
			break;
		case Chase:
			m_chase->Update(m_player->GetPos());
			break;
		case Battle:
			m_attack->Update(time);
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
//--------------------------------------------------------------------------------------
// File: EnemyCrab.cpp
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrab.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabPatrol.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabChase.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabAttack.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabEscape.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
EnemyCrab::EnemyCrab(PlayerBody* player)
	:
	m_model{},
	m_state{ DEAD }, 
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

void EnemyCrab::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// モデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("dice", L"Resources/Models/ogani-.cmo");
	//状態の設定
	m_state = state;
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
	m_attack = std::make_unique<CrabAttack>(this, m_player);
	m_escape = std::make_unique<CrabEscape>(this);

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
void EnemyCrab::Update(float timer)
{
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
	m_position = pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(m_size);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

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
void EnemyCrab::UpdateState(float time)
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
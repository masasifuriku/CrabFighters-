//--------------------------------------------------------------------------------------
// File: PlayerBody.cpp
//
// プレイヤークラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "PlayerBody.h"
#include "Game/Screen.h"
#include "PlayerHand.h"
#include "Game/Scene/Play/Stage/Stage.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Input.h"
#include "Framework/Collision.h"

#include "Libraries/MyLib/UtilityMath.h"
#include "Libraries/Microsoft/DebugDraw.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerBody::PlayerBody(Stage* stage)
	:
	m_model{},
	m_hand{},
	m_stage{ stage },
	m_state{ NONE }, 
	m_BoundingSphere{},
	m_position{},
	m_velocity{},
	m_rotate{},
	m_size{},
	m_health{},
	m_stamina{},
	m_attackCoolTime{},
	m_world{},
	m_isHit{},
	m_torus{},
	m_torusPosition{},
	m_torusWorld{},
	m_attackCount{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayerBody::~PlayerBody()
{
}

void PlayerBody::Initialize()
{
	// プレイヤーモデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("CrabBody", L"Resources/Models/CrabBody.cmo");

	//プレイヤーの腕
	m_hand = std::make_unique<PlayerHand>();
	m_hand->Initialize();

	// バウンディングスフィアを生成する
	m_BoundingSphere = CreateBoundingSphere(0.8f);

	//座標を初期化する
	m_position = Vector3::Zero;
	//行列
	m_world = Matrix::Identity;
	//速度
	m_velocity = Vector3::Zero;
	//回転
	m_rotate = Quaternion::Identity;
	//サイズ
	m_size = 0.08f;
	//体力
	m_health = 100.0f;
	//スタミナ
	m_stamina = 100.0f;
	//攻撃クールタイム
	m_attackCoolTime = 0.0f;
	//衝突判定
	m_isHit = false;

	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//マウス操作系
	m_torus = GeometricPrimitive::CreateTorus(context);
	//座標
	m_torusPosition = Vector3::Zero;
	//ワールド行列
	m_torusWorld = Matrix::Identity;

	//攻撃カウント
	m_attackCount = 0;
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="timer">StepTimerを受け取る</param>
void PlayerBody::Update(float timer)
{
	//キーボード処理
	KeyBoardEvent();
	//マウス移動処理
	MouseEvent();
	//衝突判定
	m_isHit = Collision::GetInstance()->CheckHitPlayerAndCrab();
	//ステートが攻撃の時
	if (m_state == ATTACK)
	{
		m_hand->AttackMotion();
		m_attackCount++;
		if (m_attackCount >= 6)
		{
			m_state = NONE;
			m_attackCount = 0;
		}
	}
	//攻撃クールタイム減少
	m_attackCoolTime -= timer;
	//死亡判定
	if (m_health <= 0.0f)
	{
		m_state = DEAD;
	}

	m_position = m_velocity;
	//ステージとの判定
	m_position = m_stage->NormalHitDetection(m_position).pos;
	m_rotateNormal = m_stage->NormalHitDetection(m_position).rotate;

	//バウンディングスフィアの中心点を設定
	m_BoundingSphere.Center = m_position;
}

/// <summary>
/// 描画関数
/// </summary>
void PlayerBody::Render()
{
	Matrix view = Graphics::GetInstance()->GetViewMatrix();
	Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	Matrix size, rotation, translation;
	size = Matrix::CreateScale(m_size);
	rotation = Matrix::CreateFromQuaternion(m_rotate);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * m_rotateNormal * translation;

	if (m_state != DEAD)
	{
		// モデルを描画する
		m_model->DrawModel("CrabBody", m_world);
		m_hand->Render(m_world);
		DrawBoundingSphere();

		m_torus->Draw(m_torusWorld, view, proj, Colors::DarkGreen);
	}
}

//ダメージを受ける
void PlayerBody::TakeDamage(float damage)
{
	m_health -= damage;
}

//キーボード処理
void PlayerBody::KeyBoardEvent()
{
	//キーステート
	const auto& kbState = Input::GetInstance()->GetKeyState();

	//移動中にレフトシフトを押したらダッシュ
	if (kbState.IsKeyDown(Keyboard::LeftShift))
	{
		//スタミナを消費する
		m_stamina--;
		//スタミナがあるとき
		if (m_stamina >= 0.0f)
		{
			m_velocity += Vector3::Transform(Vector3(0.1f, 0.0f, 0.0f), m_rotate);
		}
		//スタミナが0以下にならないようにする
		else if (m_stamina <= 0.0f)
		{
			m_stamina = 0.0f;
		}
	}
	else
	{
		//押していないときスタミナ回復
		m_stamina++;
		//スタミナが100以上にならないように
		if (m_stamina >= 100.0f)
		{
			m_stamina = 100.0f;
		}
	}

	//スペースを押したら
	if (kbState.IsKeyDown(Keyboard::Space) && m_attackCoolTime <= 0.0f)
	{
		//攻撃する
		m_state = ATTACK;
		//クールタイムを設定
		m_attackCoolTime = 0.5f;
	}
}

//マウス処理
void PlayerBody::MouseEvent()
{
	//マウスステート
	const auto& moState = Input::GetInstance()->GetMouseState();
	
	Matrix view = Graphics::GetInstance()->GetViewMatrix();
	Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	//クオータニオン保存用
	Quaternion q;

	//トーラスの座標を指定する
	if (moState.leftButton)
	{
		//マウスレイを取得する
		Ray mouseRay = mylib::GetMouseRay(moState.x, moState.y, Screen::WIDTH, Screen::HEIGHT, view, proj);

		//ZXの無限平面を生成する
		Plane planeZX(0, 1, 0, 0);

		//RayとPlaneの衝突判定
		float distance = 0.0f;
		bool isHit = mouseRay.Intersects(planeZX, distance);

		//RayとPlaneの衝突座標をトーラスの座標にする
		if (isHit)
		{
			m_torusPosition = Vector3{ mouseRay.position + mouseRay.direction * distance };
		}
	}

	//プレイヤーの移動ベクトル
	Vector3 velocity = Vector3::Transform(Vector3(0.07f, 0.0f, 0.0f), m_rotate);

	// プレイヤーの正面ベクトル
	Vector3 forward = Vector3::Transform(Vector3(1.0f, 0.0f, 0.0f), m_rotate);
	forward.Normalize();

	//プレイヤーからトーラスへ向かうベクトル
	Vector3 toTorus = m_torusPosition - m_position;
	Vector3 v = toTorus;
	v.Normalize();

	//プレイヤーの視野角
	constexpr float viewAngle = XMConvertToRadians(90.0f);

	//プレイヤーとトーラスの距離が近すぎなければ
	//ある程度妥協
	if (toTorus.LengthSquared() > 0.3f)
	{
		// forwardとvの間の角度をcos値で計算
		float dot = forward.Dot(v);
		float angle = std::acos(dot);

		//プレイヤーがトーラスの方向に回転する
		//「プレイヤーの移動ベクトル」と「トーラスの方向」からcosθ
		float cosTheta = velocity.Dot(toTorus) / (toTorus.Length() * velocity.Length());

		//acosの引数で指定できる範囲は「-1～1」なので、値を補正する
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		//cosθからθを計算する
		float theta = std::acos(cosTheta);

		//１フレームでの回転角を制限値以内に補正する
		theta = std::min(1.0f, theta);

		//右側に行きたい場合は角度の符号を付け替える
		if (velocity.Cross(toTorus).y < 0.0f)
		{
			theta *= (-1.0f);
		}

		// プレイヤーの角度を更新する
		q *= Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(theta));

		//クオータニオンを回転に掛ける
		m_rotate = q * m_rotate;

		
		//角度を合わせながら微移動
		m_velocity += Vector3::Transform(Vector3(0.03f, 0.0f, 0.0f), m_rotate);

		//目的地に角度があったら移動
		if (angle < std::cos(viewAngle / 1.5f))
		{
			//プレイヤーを移動する
			m_velocity += velocity;
		}
		
	}

	//トーラスのワールド行列を計算する
	m_torusPosition = m_stage->NormalHitDetection(m_torusPosition).pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(0.5f, 0.01f, 0.5f);
	rotation = m_stage->NormalHitDetection(m_torusPosition).rotate;
	translation = Matrix::CreateTranslation(m_torusPosition);
	m_torusWorld = size * rotation * translation;
}

//バウンディングスフィア生成
DirectX::BoundingSphere PlayerBody::CreateBoundingSphere(const float& radius)
{
	// バウンディングスフィアを宣言する
	DirectX::BoundingSphere turretBoundingSphere;
	// バウンディングスフィアの半径を設定する
	turretBoundingSphere.Radius = radius;
	// バウンディングスフィアを返す
	return turretBoundingSphere;
}

// バウンディングスフィアを描画する
void PlayerBody::DrawBoundingSphere()
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

//--------------------------------------------------------------------------------------
// File: Stage.cpp
//
// プレイヤークラス
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Stage.h"
#include "Game/Screen.h"

#include "Libraries/MyLib/CollisionMesh.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage()
	:
	m_model{},
	m_collisionMesh{},
	m_isVisible{},
	m_hitPosition{},
	m_normal{},
	m_hitPolygonNo{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
}

void Stage::Initialize()
{
	// 地形の表示モデルを読み込む
	m_model = std::make_unique <Ede::ModelManager>();
	m_model->AddModelData("Terrain", L"Resources/Models/floor02.cmo");
	//最初は表示しない
	m_isVisible = false;

	//コリジョンメッシュを生成
	m_collisionMesh = std::make_unique<mylib::CollisionMesh>();
	m_collisionMesh->Initialize(L"Stage");

	m_normal = { Vector3::Zero,Matrix::Identity };
}

/// <summary>
/// 描画関数
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="proj">射影行列</param>
void Stage::Render()
{
	// メッシュを描画する
	m_collisionMesh->Draw();

	// モデルを描画する
	Matrix mat = Matrix::CreateTranslation(Vector3(0.0f, -1.2f, 0.0f));
	if (m_isVisible)
	{
		m_model->DrawModel("Terrain", mat);
	}
}

//法線との当たり判定
Normal Stage::NormalHitDetection(DirectX::SimpleMath::Vector3 pos)
{
	//Rayを使ったコリジョンメッシュとの当たり判定
	Vector3 rayOrigin = pos;
	//Rayの始まりを少し上にあげておく
	rayOrigin.y += 2.0f;

	//Rayと衝突時のポリゴンの法線を定義する
	Ray ray{ rayOrigin,Vector3::Down };
	Vector3 normal;

	//Rayとコリジョンメッシュで衝突判定を取る
	if (m_collisionMesh->IntersectRay(ray, &m_hitPosition, &normal, &m_hitPolygonNo))
	{
		Quaternion q2 = Quaternion::FromToRotation(Vector3::UnitY, normal);
		m_normal.rotate = Matrix::CreateFromQuaternion(q2);
		m_normal.pos = m_hitPosition;
	}
	return m_normal;
}

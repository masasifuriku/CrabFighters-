//--------------------------------------------------------------------------------------
// File: Stage.h
//
// ステージクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "Libraries/EdeLib/ModelManager.h"

namespace mylib
{
	class CollisionMesh;
}

struct Normal 
{
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Matrix rotate;
};


class Stage
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
	//コリジョンメッシュ
	std::unique_ptr<mylib::CollisionMesh> m_collisionMesh;

	// モデル表示フラグ
	bool m_isVisible;

	//地形の判定用
	//ポリゴンとRayの衝突座標
	DirectX::SimpleMath::Vector3 m_hitPosition;
	//座標保存用
	Normal m_normal;
	//衝突したポリゴンの番号
	int m_hitPolygonNo;
	

public:
	Stage();
	~Stage();

	void Initialize();
	void Render();

public:
	//法線との当たり判定
	Normal NormalHitDetection(DirectX::SimpleMath::Vector3 pos);
};

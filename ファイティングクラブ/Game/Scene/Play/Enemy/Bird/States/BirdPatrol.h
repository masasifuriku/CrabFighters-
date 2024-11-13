//--------------------------------------------------------------------------------------
// File: BirdPatrol.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"



class BirdPatrol
{
private:
	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 速さ
	DirectX::SimpleMath::Vector3 m_velocity;
	//回転
	// クォータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	//行列
	DirectX::SimpleMath::Matrix m_world;
	//角度
	float m_angle;

public:
	BirdPatrol();
	~BirdPatrol();

	void Update(float timer, DirectX::SimpleMath::Vector3 Ppos);
};

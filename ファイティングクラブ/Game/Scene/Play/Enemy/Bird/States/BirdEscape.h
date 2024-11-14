//--------------------------------------------------------------------------------------
// File: BirdEscape.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBird;

class BirdEscape
{
private:
	EnemyBird* m_bird;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	BirdEscape(EnemyBird* bird);
	~BirdEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

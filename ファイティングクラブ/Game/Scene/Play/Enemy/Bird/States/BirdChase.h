//--------------------------------------------------------------------------------------
// File: BirdChase.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyBird;

class BirdChase
{
private:
	EnemyBird* m_bird;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	BirdChase(EnemyBird* bird);
	~BirdChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

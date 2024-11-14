//--------------------------------------------------------------------------------------
// File: SharkChase.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyShark;

class SharkChase
{
private:
	EnemyShark* m_shark;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	SharkChase(EnemyShark* shark);
	~SharkChase();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

//--------------------------------------------------------------------------------------
// File: SharkEscape.h
//
// 敵ステートクラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"

class EnemyShark;

class SharkEscape
{
private:
	EnemyShark* m_shark;

	//速度
	static constexpr float SPEED = 0.1f;

public:
	SharkEscape(EnemyShark* shark);
	~SharkEscape();

	void Update(DirectX::SimpleMath::Vector3 Ppos);
};

#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED
#include "Graphics.h"

// Collisionクラスを定義する
class Collision
{
public:
	//
public:
	Collision(Collision&&) = default;
	Collision& operator= (Collision&&) = default;
	Collision& operator= (Collision const&) = delete;
	// デストラクタ
	~Collision() = default;
	// Resoucesクラスのインスタンスを取得する
	static Collision* const GetInstance();
private:
	// コンストラクタ
	Collision() noexcept
	{
	}

private:
	// Collisionクラスのインスタンスへのポインタ
	static std::unique_ptr<Collision> m_collision;
};

#endif		// Collision_DEFINED

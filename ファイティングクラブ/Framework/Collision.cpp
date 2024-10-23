#include "pch.h"
#include "Collision.h"

std::unique_ptr<Collision> Collision::m_collision = nullptr;

// Collisionクラスのインスタンスを取得する
Collision* const Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		// Collisionクラスのインスタンスを生成する
		m_collision.reset(new Collision());
	}
	// Collisionクラスのインスタンスを返す
	return m_collision.get();
}
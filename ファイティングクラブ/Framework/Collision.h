#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED
#include "Graphics.h"

// Collision�N���X���`����
class Collision
{
public:
	//
public:
	Collision(Collision&&) = default;
	Collision& operator= (Collision&&) = default;
	Collision& operator= (Collision const&) = delete;
	// �f�X�g���N�^
	~Collision() = default;
	// Resouces�N���X�̃C���X�^���X���擾����
	static Collision* const GetInstance();
private:
	// �R���X�g���N�^
	Collision() noexcept
	{
	}

private:
	// Collision�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Collision> m_collision;
};

#endif		// Collision_DEFINED

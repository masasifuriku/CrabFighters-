#include "pch.h"
#include "Collision.h"

std::unique_ptr<Collision> Collision::m_collision = nullptr;

// Collision�N���X�̃C���X�^���X���擾����
Collision* const Collision::GetInstance()
{
	if (m_collision == nullptr)
	{
		// Collision�N���X�̃C���X�^���X�𐶐�����
		m_collision.reset(new Collision());
	}
	// Collision�N���X�̃C���X�^���X��Ԃ�
	return m_collision.get();
}
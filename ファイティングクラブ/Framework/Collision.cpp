#include "pch.h"
#include "Collision.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Player/PlayerHand.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrab.h"
#include "Game/Scene/Play/Enemy/Boss/EnemyBoss.h"


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

// �R���X�g���N�^
Collision::Collision()
	:
	m_player{},
	m_playerHand{},
	m_crab{},
	m_boss{}
{
}

//�v���C���[����G�ւ̂̍U��
bool Collision::CheckHitAttackPlayerToCrab()
{
	//�r�������Ă���
	m_playerHand = m_player->GetHand();
	//�������Ă���true
	if (m_playerHand->GetHandBoundingSphere().
		Intersects(
			m_crab->GetBodyBoundingSphere()))
	{
		return true;
	}
	
	return false;
}
//bool Collision::CheckHitAttackPlayerToBoss()
//{
//	//�r�������Ă���
//	m_playerHand = m_player->GetHand();
//	//�������Ă���true
//	if (m_playerHand->GetHandBoundingSphere().
//		Intersects(
//			m_boss->GetBodyBoundingSphere()))
//	{
//		return true;
//	}
//	return false;
//}

//�G����v���C���[�ւ̍U��
bool Collision::CheckHitAttackCrabsToPlayer()
{
	//�������Ă���true
	if (m_crab->GetBodyBoundingSphere().
		Intersects(
			m_player->GetBodyBoundingSphere()))
	{
		return true;
	}
	return false;
}
//bool Collision::CheckHitAttackBossToPlayer()
//{
//	//�������Ă���true
//	if (m_boss->GetBodyBoundingSphere().
//		Intersects(
//			m_player->GetBodyBoundingSphere()))
//	{
//		return true;
//	}
//	return false;
//}
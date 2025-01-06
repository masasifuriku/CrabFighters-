#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED

class PlayerBody;
class PlayerHand;
class EnemyCrab;
class EnemyBoss;

// Collision�N���X���`����
class Collision
{
public:
	// Collision�N���X�̃C���X�^���X���擾����
	static Collision* const GetInstance();

	//�v���C���[�����炤
	void SetPlayer(PlayerBody* player) { m_player = player; }
	//�G�����炤
	void SetCrab(EnemyCrab* crab) { m_crab = crab; }
	void SetBoss(EnemyBoss* boss) { m_boss = boss; }

public:
	//�U���n�̓����蔻��
	//�v���C���[����J�j�ւ̍U�������蔻��
	bool CheckHitAttackPlayerToCrab();
	////�v���C���[����{�X�ւ̍U�������蔻��
	//bool CheckHitAttackPlayerToBoss();

	//�J�j����v���C���[�ւ̍U�������蔻��
	bool CheckHitAttackCrabsToPlayer();
	////�{�X����v���C���[�ւ̍U�������蔻��
	//bool CheckHitAttackBossToPlayer();

public:
	Collision(Collision&&) = default;
	Collision& operator= (Collision&&) = default;
	Collision& operator= (Collision const&) = delete;
	// �f�X�g���N�^
	~Collision() = default;

private:
	// �R���X�g���N�^
	Collision();

private:
	// Collision�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Collision> m_collision;

	//�v���C���[�̃|�C���^
	PlayerBody* m_player;
	//�v���C���[�̘r�̃|�C���^
	PlayerHand* m_playerHand;
	//�J�j�̃|�C���^
	EnemyCrab* m_crab;
	//�{�X�̃|�C���^
	EnemyBoss* m_boss;
};

#endif		// Collision_DEFINED

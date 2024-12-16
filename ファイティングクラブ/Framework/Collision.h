#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED

class PlayerBody;
class PlayerHand;
class EnemyManager;

// Collision�N���X���`����
class Collision
{
public:
	// Collision�N���X�̃C���X�^���X���擾����
	static Collision* const GetInstance();

	//�v���C���[�����炤
	void SetPlayer(PlayerBody* player) { m_player = player; }
	//�G�����炤
	void SetEnemy(EnemyManager* enemy) { m_enemy = enemy; }

public:
	//�U���n�̓����蔻��
	//�v���C���[����J�j�ւ̍U�������蔻��
	bool CheckHitAttackPlayerToCrab();
	//�v���C���[���璹�ւ̍U�������蔻��
	bool CheckHitAttackPlayerToBird();
	//�v���C���[����T���ւ̍U�������蔻��
	bool CheckHitAttackPlayerToShark();
	//�v���C���[����{�X�ւ̍U�������蔻��
	bool CheckHitAttackPlayerToBoss();
	//�J�j����v���C���[�ւ̍U�������蔻��
	bool CheckHitAttackCrabrToPlayer();
	//������v���C���[�ւ̍U�������蔻��
	bool CheckHitAttackBirdrToPlayer();
	//�T������v���C���[�ւ̍U�������蔻��
	bool CheckHitAttackSharkToPlayer();
	//�{�X����v���C���[�ւ̍U�������蔻��
	bool CheckHitAttackBossToPlayer();

	//�����߂��p�����蔻��
	bool CheckHitPlayerAndCrab();
	bool CheckHitPlayerAndBird();
	bool CheckHitPlayerAndShark();
	bool CheckHitPlayerAndBoss();

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
	//�G�̃|�C���^
	EnemyManager* m_enemy;
};

#endif		// Collision_DEFINED

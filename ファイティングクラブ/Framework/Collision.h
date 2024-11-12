#pragma once
#ifndef COLLISION_DEFINED
#define COLLISION_DEFINED

class PlayerBody;
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
	//�v���C���[����J�j�ւ̓����蔻��
	bool CheckHitPlayerToCrab();
	//�v���C���[���璹�ւ̓����蔻��
	bool CheckHitPlayerToBird();
	//�v���C���[����T���ւ̓����蔻��
	bool CheckHitPlayerToShark();
	//�v���C���[����{�X�ւ̓����蔻��
	bool CheckHitPlayerToBoss();

	//�J�j����v���C���[�ւ̓����蔻��
	bool CheckHitCrabrToPlayer();
	//������v���C���[�ւ̓����蔻��
	bool CheckHitBirdrToPlayer();
	//�T������v���C���[�ւ̓����蔻��
	bool CheckHitSharkToPlayer();
	//�{�X����v���C���[�ւ̓����蔻��
	bool CheckHitBossToPlayer();

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
	//�G�̃|�C���^
	EnemyManager* m_enemy;
};

#endif		// Collision_DEFINED

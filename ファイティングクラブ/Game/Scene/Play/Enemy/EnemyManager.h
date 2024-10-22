/**
 * @file   EnemyManager.h
 *
 * @brief  �G�Ɋւ���w�b�_�t�@�C��
 *
 * @author kaede
 *
 * @date   2023/11/08
 */

// ���d�C���N���[�h�̖h�~ =====================================================
#pragma once
#include "Interface/IEnemy.h"
#include "Crab/EnemyCrab.h"
#include "Shark/EnemyShark.h"
#include "Bird/EnemyBird.h"
#include "Boss/EnemyBoss.h"
#include <vector>

class Stage;


// �N���X�̒�` ===============================================================
/**
  * @brief �Q�[��
  */
class EnemyManager
{
// �f�[�^�����o�̐錾
private:
	struct EnemyData
	{
		float time = 0.0f;					// �o������
		int id = 0;                     //�G�̎��
		DirectX::SimpleMath::Vector3 position;	        // �o�����W
	};

	// �G�̑���
	static const int MAX_ENEMY_COUNT = 1;
	// �G�̔z��
	std::unique_ptr<IEnemy>  m_crabs[MAX_ENEMY_COUNT];
	std::unique_ptr<IEnemy> m_sharks[MAX_ENEMY_COUNT];
	std::unique_ptr<IEnemy>  m_birds[MAX_ENEMY_COUNT];
	//�{�X
	std::unique_ptr<IEnemy> m_boss;
	// �������̓G���J�E���^
	int m_activeEnemyCount;
	// �G�̏o�����X�g
	std::vector<EnemyData>m_enemyDataList;
	// �t���[���J�E���^
	int m_frameCounter;
	// �G�̏o�����X�g�A�ǂ��܂Ŏ��s������
	int m_nowListNumber;
	// �A�N�e�B�u�ȓG�z��
	std::vector<IEnemy*>  m_activeCrabs;
	std::vector<IEnemy*> m_activeSharks;
	std::vector<IEnemy*>  m_activeBirds;

	//�t�@�C�����I�������
	bool m_CSVFlag;

	//�X�e�[�W�̃|�C���^
	Stage* m_stage;

// �����o�֐��̐錾
public:
	// �R���X�g���N�^
	EnemyManager(Stage* stage);

	// �f�X�g���N�^
	~EnemyManager();

// ����
public:
	// ����������
	void Initialize();

	// �X�V����
	void Update(float timer, IEnemy::EnemyState state, DirectX::SimpleMath::Vector3 Ppos);

	// �`�揈��
	void Render();

public:
	// �G���o��������
	bool Spawn(IEnemy::EnemyState state);
	// �S�G����Ԃ�
	static int GetTotalEnemyCount() { return MAX_ENEMY_COUNT; }
	// �������̓G����Ԃ�
	int GetActiveEnemyCount() const { return m_activeEnemyCount; }
	// �������̓G�z����擾����
	std::vector<IEnemy*>& GetActiveCrabs() { return m_activeCrabs; }
	std::vector<IEnemy*>& GetActiveSharks() { return m_activeSharks; }
	std::vector<IEnemy*>& GetActiveBirds() { return m_activeBirds; }
	//�{�X���擾���� 
	std::unique_ptr<IEnemy>& GetBoss() { return m_boss; }
	//�t�@�C�����I��������
	bool GetCSV()const { return m_CSVFlag; }

private:
	//CSV�����[�h����
	void LoadCSV(const char* fileName);
};

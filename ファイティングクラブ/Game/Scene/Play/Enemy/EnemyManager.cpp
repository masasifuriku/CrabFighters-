/**
 * @file   EnemyManager.cpp
 *
 * @brief  �G�Ɋւ���\�[�X�t�@�C��
 *
 * @author kaede
 *
 * @date   2023/11/08
 */

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "EnemyManager.h"
#include<fstream>
#include<sstream>
#include "Game/Scene/Play/Stage/Stage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �����o�֐��̒�` ===========================================================
/**
 * @brief �f�t�H���g�R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
EnemyManager::EnemyManager(Stage* stage,PlayerBody* player)
	:
	m_crabs{},
	m_sharks{},
	m_birds{},
	m_boss{},
	m_activeEnemyCount{},
	m_enemyDataList{},
	m_frameCounter{},
	m_nowListNumber{},
	m_activeCrabs{},
	m_activeSharks{},
	m_activeBirds{},
	m_CSVFlag{},
	m_stage{ stage },
	m_player{ player }
{
}



/**
 * @brief �f�X�g���N�^
 */
EnemyManager::~EnemyManager()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void EnemyManager::Initialize()
{
	// �G�𐶐�����
	for (int i = 0; i < MAX_ENEMY_COUNT; i++)
	{
		m_crabs[i] = std::make_unique<EnemyCrab>(m_player);
		m_sharks[i] = std::make_unique<EnemyShark>(m_player);
		m_birds[i] = std::make_unique<EnemyBird>();
	}
	//�{�X�𐶐�����
	m_boss = std::make_unique<EnemyBoss>(m_player);
	//�������̓G�̐�������������
	m_activeEnemyCount = 0;

	//�G�̏o�����X�g�����[�h����
	LoadCSV("Resources\\CSV\\enemy.csv");
	m_CSVFlag = false;
}




/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void EnemyManager::Update(float timer, IEnemy::EnemyState state)
{
	// �t���[�����J�E���g����
	m_frameCounter++;

	// �G���X�|�[������
	Spawn(state);

	//�z����N���A����
	m_activeEnemyCount = 0;
	m_activeCrabs.clear();
	m_activeSharks.clear();
	m_activeBirds.clear();

	//�J�j�̍X�V
	for (auto& crab : m_crabs)
	{
		assert(crab);

		// �A�N�e�B�u�ȃJ�j�����X�V����
		if (!crab->IsActive())
		{
			continue;
		}

		crab->Update(timer);

		// �A�N�e�B�u�ȓG���J�E���g����
		m_activeEnemyCount++;

		// �A�N�e�B�u�ȃJ�j�����z��ɓ����
		m_activeCrabs.push_back(crab.get());
	}
	//�T���̍X�V
	for (auto& shark : m_sharks)
	{
		assert(shark);

		// �A�N�e�B�u�ȃT�������X�V����
		if (!shark->IsActive())
		{
			continue;
		}

		shark->Update(timer);

		// �A�N�e�B�u�ȓG���J�E���g����
		m_activeEnemyCount++;

		// �A�N�e�B�u�ȃT�������z��ɓ����
		m_activeSharks.push_back(shark.get());
	}
	//���̍X�V
	for (auto& bird : m_birds)
	{
		assert(bird);

		// �A�N�e�B�u�Ȓ������X�V����
		if (!bird->IsActive())
		{
			continue;
		}

		bird->Update(timer);

		// �A�N�e�B�u�ȓG���J�E���g����
		m_activeEnemyCount++;

		// �A�N�e�B�u�Ȓ������z��ɓ����
		m_activeBirds.push_back(bird.get());
	}
	//�{�X�̍X�V
	m_boss->Update(timer);
}




/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void EnemyManager::Render()
{
	//�J�j�̕`��
	for (auto& crab : m_crabs)
	{
		assert(crab);

		// �A�N�e�B�u�ȓG�����`�悷��
		if (!crab->IsActive())
		{
			continue;
		}
		//�������̃J�j�ƃX�e�[�W�̔���
		Vector3 pos = m_stage->NormalHitDetection(crab->GetPos()).pos;
		Matrix normal = m_stage->NormalHitDetection(crab->GetPos()).rotate;
	
		crab->Render(pos, normal);
	}
	//�T���̕`��
	for (auto& shark : m_sharks)
	{
		assert(shark);

		// �A�N�e�B�u�ȓG�����`�悷��
		if (!shark->IsActive())
		{
			continue;
		}
		//�������̃T���ƃX�e�[�W�̔���
		Vector3 pos = m_stage->NormalHitDetection(shark->GetPos()).pos;
		Matrix normal = m_stage->NormalHitDetection(shark->GetPos()).rotate;

		shark->Render(pos, normal);
	}
	//���̕`��
	for (auto& bird : m_birds)
	{
		assert(bird);

		// �A�N�e�B�u�ȓG�����`�悷��
		if (!bird->IsActive())
		{
			continue;
		}
		//�������̒��ƃX�e�[�W�̔���
		Vector3 pos = m_stage->NormalHitDetection(bird->GetPos()).pos;
		Matrix normal = m_stage->NormalHitDetection(bird->GetPos()).rotate;

		bird->Render(pos, normal);
	}
	//�{�X�̕`��
	//�{�X�ƃX�e�[�W�̔���
	Vector3 Bpos = m_stage->NormalHitDetection(m_boss->GetPos()).pos;
	Matrix Bnormal = m_stage->NormalHitDetection(m_boss->GetPos()).rotate;
	m_boss->Render(Bpos, Bnormal);
}


// �G���o��������
bool EnemyManager::Spawn(IEnemy::EnemyState state)
{
	// �o���f�[�^���X�g���I������
	if (m_nowListNumber >= m_enemyDataList.size())
	{
		//�t�@�C�����I��
		m_CSVFlag = true;
		return false;
	}

	// �t���[���J�E���^���G�̏o�����ԂɂȂ��Ă��Ȃ�
	if (m_enemyDataList[m_nowListNumber].time > m_frameCounter)
	{
		return false;
	}

	// �G�̃C���X�^���X�z�񂩂�A�N�e�B�u�łȂ����̂𗘗p����
	for (int i = 0; i < MAX_ENEMY_COUNT; i++)
	{
		//�ǂ������������Ȃ���Α����Ȃ�
		if (m_crabs[i]->IsActive()  ||
			m_sharks[i]->IsActive() ||
			m_birds[i]->IsActive())
		{
			continue;
		}
		//ID�����đΉ�����G��������
		switch (m_enemyDataList[m_nowListNumber].id)
		{
			case 0:
				if (!m_crabs[i]->IsActive())
				{
					m_crabs[i]->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			case 1:
				if (!m_sharks[i]->IsActive())
				{
					m_sharks[i]->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			case 2:
				if (!m_birds[i]->IsActive())
				{
					m_birds[i]->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			case 3:
				if (!m_boss->IsActive())
				{
					m_boss->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			default:
				break;
		}

		// �o���f�[�^���X�g�̓Y�������X�V����
		m_nowListNumber++;

		// �G���o��������
		return true;
	}

	// �G�����ׂĎg�p��������
	return false;
}

//---------------------------------------------------------
// CSV�����[�h����
//---------------------------------------------------------
void EnemyManager::LoadCSV(const char* fileName)
{
	std::ifstream ifs;     //�t�@�C���X�g���[��
	std::string line;      //1�s���̃f�[�^	
	std::istringstream iss;//������X�g���[��

	//�t�@�C���X�g���[�����J��
	ifs.open(fileName);

	assert(ifs && "EnemyManager::LoadCSV::�t�@�C�����J���܂���ł����I");

	//�w�b�_�s��ǂݔ�΂�
	std::getline(ifs, line);

	//ifs�����܂Ńf�[�^����������
	//ifs����P�s���̃f�[�^�����o��
	while (std::getline(ifs, line))
	{
		//�J���}��؂���󔒋�؂�ɕϊ�����
		std::replace(line.begin(), line.end(), ',', ' ');

		//���܂��Ȃ�
		iss.clear(std::istringstream::goodbit);

		//��s���̃f�[�^��iss�ɓǂݍ���
		iss.str(line);

		//�f�[�^�𕪊�
		float time;
		int id;
		float x;
		float y;
		float z;
		iss >> time >> id >> x >> y >> z;

		//�ǉ�����G�f�[�^���쐬����
		EnemyData data;
		data.time = time;
		data.id = id;
		data.position = { x,y,z };

		//�G�f�[�^��G���X�g�ɒǉ�
		m_enemyDataList.push_back(data);
	}
	//����
	ifs.close();
}
/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Libraries/MyLib/TPS_Camera.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/EnemyManager.h"
#include "Game/Scene/Play/Stage/Stage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_camera{},
	m_isChangeScene{},
	m_player{},
	m_enemy{},
	m_stage{},
	m_Batch{},
	m_Font{},
	m_collision{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayScene::~PlayScene()
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayScene::Initialize()
{
	// �J�������쐬����
	m_camera = std::make_unique<mylib::TPS_Camera>();

	//�X�e�[�W�̐���
	m_stage = std::make_unique<Stage>();
	m_stage->Initialize();
	//�v���C���[�̐���
	m_player = std::make_unique<PlayerBody>(m_stage.get());
	m_player->Initialize();
	//�G�̐���
	m_enemy = std::make_unique<EnemyManager>(m_stage.get(), m_player.get());
	m_enemy->Initialize();

	//�o�b�`�ƃt�H���g�������Ă���
	m_Batch = Graphics::GetInstance()->GetSpriteBatch();
	m_Font = Graphics::GetInstance()->GetFont();

	//�����蔻��C���X�^���X�������Ă���
	m_collision = Collision::GetInstance();
	//�����蔻��ɃI�u�W�F�N�g��n��
	m_collision->SetPlayer(m_player.get());
	m_collision->SetEnemy(m_enemy.get());

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//�J�����̍X�V
	m_camera->Update(m_player->GetPos(), Matrix::Identity);

	//�v���C���[�̍X�V
	m_player->Update(elapsedTime);

	//�G�̍X�V
	m_enemy->Update(elapsedTime, IEnemy::Patrol);

	//�G�̃X�e�[�g�X�V
	UpdateCrabs();
	UpdateSharks();
	UpdateBirds();
	UpdateBoss();

	//�r���[�Ǝˉe�s��̐���
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());

	// �G�̏o���t�@�C�����I����ēG��S���|�����烊�U���g�Ɉڍs
	if (m_enemy->GetCSV() == true && m_enemy->GetActiveEnemyCount() == 0 ||
		m_player->GetHP() <= 0.0f)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	//�v���C���[�̕`��
	m_player->Render();
	//�G�̕`��
	m_enemy->Render();
	//�X�e�[�W�̕`��
	m_stage->Render();
	//�f�o�b�O�\��
	DrawDebug();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::RESULT;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

void PlayScene::UpdateCrabs()
{
	//�v���C���[�ƓG(�J�j)�̔���Ȃ�
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//�G�̃X�e�[�g�Ǘ�
		//�v���C���[�ƓG�̈ʒu
		Vector3 Ppos = m_player->GetPos();
		Vector3 Cpos = crab->GetPos();
		//�v���C���[�ƓG�̋���
		float dx = Ppos.x - Cpos.x;
		float dy = Ppos.y - Cpos.y;
		float dz = Ppos.z - Cpos.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		//�G�̒ǐՔ͈�
		float SearchRange = 5.0f;
		//�X�e�[�g���p�g���[���ɂ���
		if (distance >= SearchRange)
		{
			crab->SetEnemyState(IEnemy::EnemyState::Patrol);
		}
		//�X�e�[�g��ǐՂɂ���
		else if (distance <= SearchRange)
		{
			crab->SetEnemyState(IEnemy::EnemyState::Chase);
		}
		//�X�e�[�g���U������
		if (Collision::GetInstance()->CheckHitCrabrToPlayer())
		{
			crab->SetEnemyState(IEnemy::EnemyState::Battle);
		}
		//�X�e�[�g�𓦑��ɂ���
		if (crab->GetHP() <= 20.0f)
		{
			crab->SetEnemyState(IEnemy::EnemyState::Escape);
			if (distance >= 15.0f)
			{
				crab->SetEnemyState(IEnemy::EnemyState::Patrol);
			}
		}
		//�X�e�[�g�����S�ɂ���
		if (crab->GetHP() <= 0.0f)
		{
			crab->SetEnemyState(IEnemy::EnemyState::DEAD);
		}
		//�v���C���[����J�j�ւ̍U��
		if (Collision::GetInstance()->CheckHitPlayerToCrab())
		{
			//�v���C���[�̏�Ԃ��U���Ȃ�G�Ƀ_���[�W������
			if (m_player->GetState() == PlayerBody::ATTACK)
			{
				crab->TakeDamage(30.0f);
			}
		}
	}
}

void PlayScene::UpdateSharks()
{
	//�v���C���[�ƓG(�T��)�̓����蔻��
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//�G�̃X�e�[�g�Ǘ�
		//�v���C���[�ƓG�̈ʒu
		Vector3 Ppos = m_player->GetPos();
		Vector3 Spos = shark->GetPos();
		//�v���C���[�ƓG�̋���
		float dx = Ppos.x - Spos.x;
		float dy = Ppos.y - Spos.y;
		float dz = Ppos.z - Spos.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		//�G�̒ǐՔ͈�
		float SearchRange = 5.0f;
		//�X�e�[�g���p�g���[���ɂ���
		if (distance >= SearchRange)
		{
			shark->SetEnemyState(IEnemy::EnemyState::Patrol);
		}
		//�X�e�[�g��ǐՂɂ���
		else if (distance <= SearchRange)
		{
			shark->SetEnemyState(IEnemy::EnemyState::Chase);
		}
		//�X�e�[�g�𓦑��ɂ���
		if (shark->GetHP() <= 20.0f)
		{
			shark->SetEnemyState(IEnemy::EnemyState::Escape);
		}
		//�X�e�[�g�����S�ɂ���
		if (shark->GetHP() <= 0.0f)
		{
			shark->SetEnemyState(IEnemy::EnemyState::DEAD);
		}
		//�v���C���[����T���ւ̍U��
		if (Collision::GetInstance()->CheckHitPlayerToShark())
		{
			//�v���C���[�̏�Ԃ��U���Ȃ�G�Ƀ_���[�W������
			if (m_player->GetState() == PlayerBody::ATTACK)
			{
				shark->TakeDamage(30.0f);
			}
		}
	}
}

void PlayScene::UpdateBirds()
{
	//�v���C���[�ƓG(��)�̓����蔻��
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//�G�̃X�e�[�g�Ǘ�
		//�v���C���[�ƓG�̈ʒu
		Vector3 Ppos = m_player->GetPos();
		Vector3 Bpos = bird->GetPos();
		//�v���C���[�ƓG�̋���
		float dx = Ppos.x - Bpos.x;
		float dy = Ppos.y - Bpos.y;
		float dz = Ppos.z - Bpos.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		//�G�̒ǐՔ͈�
		float SearchRange = 5.0f;
		//�X�e�[�g���p�g���[���ɂ���
		if (distance >= SearchRange)
		{
			bird->SetEnemyState(IEnemy::EnemyState::Patrol);
		}
		//�X�e�[�g��ǐՂɂ���
		else if (distance <= SearchRange)
		{
			bird->SetEnemyState(IEnemy::EnemyState::Chase);
		}
		//�X�e�[�g�𓦑��ɂ���
		if (bird->GetHP() <= 20.0f)
		{
			bird->SetEnemyState(IEnemy::EnemyState::Escape);
		}
		//�X�e�[�g�����S�ɂ���
		if (bird->GetHP() <= 0.0f)
		{
			bird->SetEnemyState(IEnemy::EnemyState::DEAD);
		}
		//�v���C���[���璹�ւ̍U��
		if (Collision::GetInstance()->CheckHitPlayerToBird())
		{
			//�v���C���[�̏�Ԃ��U���Ȃ�G�Ƀ_���[�W������
			if (m_player->GetState() == PlayerBody::ATTACK)
			{
				bird->TakeDamage(30.0f);
			}
		}
	}
}

void PlayScene::UpdateBoss()
{
	//�{�X�����Ă���
	auto& boss = m_enemy->GetBoss();

	//�{�X�̃X�e�[�g�Ǘ�
	//�v���C���[�ƃ{�X�̈ʒu
	Vector3 Ppos = m_player->GetPos();
	Vector3 Bpos = boss->GetPos();
	//�v���C���[�ƃ{�X�̋���
	float dx = Ppos.x - Bpos.x;
	float dy = Ppos.y - Bpos.y;
	float dz = Ppos.z - Bpos.z;
	float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
	//�{�X�̒ǐՔ͈�
	float SearchRande = 5.0f;
	//�X�e�[�g���p�g���[���ɂ���
	if (distance >= SearchRande)
	{
		boss->SetEnemyState(IEnemy::EnemyState::Patrol);
	}
	//�X�e�[�g��ǐՂɂ���
	else if (distance <= SearchRande)
	{
		boss->SetEnemyState(IEnemy::EnemyState::Chase);
	}
	//�X�e�[�g�𓦑��ɂ���
	if (boss->GetHP() <= 20.0f)
	{
		boss->SetEnemyState(IEnemy::EnemyState::Escape);
	}
	//�X�e�[�g�����S�ɂ���
	if (boss->GetHP() <= 0.0f)
	{
		boss->SetEnemyState(IEnemy::EnemyState::DEAD);
	}
	//�v���C���[���璹�ւ̍U��
	if (Collision::GetInstance()->CheckHitPlayerToBoss())
	{
		//�v���C���[�̏�Ԃ��U���Ȃ�G�Ƀ_���[�W������
		if (m_player->GetState() == PlayerBody::ATTACK)
		{
			boss->TakeDamage(30.0f);
		}
	}
}

//�f�o�b�N�����܂Ƃ߂Ă���
void PlayScene::DrawDebug()
{
	//�n�߂�
	m_Batch->Begin();
	//// �f�o�b�O�����uDebugString�v�ŕ\������
	m_Font->DrawString(m_Batch, L"Play Scene", Vector2(10, 10), Colors::Aqua);
	//�������̃J�j�̏��
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		std::wstring crabHP = L"Crab:" + std::to_wstring(crab->GetHP());
		m_Font->DrawString(m_Batch, crabHP.c_str(), Vector2(10, 30), Colors::Aqua);
	}
	//�������̃T���̏��
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		std::wstring sharkHP = L"Shark:" + std::to_wstring(shark->GetHP());
		m_Font->DrawString(m_Batch, sharkHP.c_str(), Vector2(10, 50), Colors::Aqua);
	}	
	//�������̒��̏��
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		std::wstring birdHP = L"Bird:" + std::to_wstring(bird->GetHP());
		m_Font->DrawString(m_Batch, birdHP.c_str(), Vector2(10, 70), Colors::Aqua);
	}
	//�{�X�̏��
	auto& boss = m_enemy->GetBoss();
	std::wstring bossHP = L"Boss:" + std::to_wstring(boss->GetHP());
	m_Font->DrawString(m_Batch, bossHP.c_str(), Vector2(10, 90), Colors::Aqua);
	//�������̓G�̑���
	std::wstring ActiveEnemy = L"ActiveEnemy:" + std::to_wstring(m_enemy->GetActiveEnemyCount());
	m_Font->DrawString(m_Batch, ActiveEnemy.c_str(), Vector2(10, 110), Colors::Aqua);
	//�v���C���[�̃X�^�~�i
	std::wstring PSta = L"Player/Stamina:" + std::to_wstring(m_player->GetStamina());
	m_Font->DrawString(m_Batch, PSta.c_str(), Vector2(10, 130), Colors::Aqua);
	//�I���
	m_Batch->End();
}

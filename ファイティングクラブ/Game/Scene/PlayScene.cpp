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
#include "Game/Scene/Play/SkyDome/SkyDome.h"

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
	m_dome{},
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
	//�V���̐���
	m_dome = std::make_unique<SkyDome>();
	m_dome->Initialize();

	//�o�b�`�ƃt�H���g�������Ă���
	m_Batch = Graphics::GetInstance()->GetSpriteBatch();
	m_Font = Graphics::GetInstance()->GetFont();

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
	//�V���̕`��
	m_dome->Render();
	//�f�o�b�O�\��
	DrawDebug();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void PlayScene::Finalize()
{
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
	////�v���C���[���璹�ւ̍U��
	//if (Collision::GetInstance()->CheckHitAttackPlayerToBoss())
	//{
	//	//�v���C���[�̏�Ԃ��U���Ȃ�G�Ƀ_���[�W������
	//	if (m_player->GetState() == PlayerBody::ATTACK)
	//	{
	//		boss->TakeDamage(5.0f);
	//	}
	//}
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
	//�v���C���[�̗̑�
	std::wstring Php = L"Player/HP:" + std::to_wstring(m_player->GetHP());
	m_Font->DrawString(m_Batch, Php.c_str(), Vector2(10, 150), Colors::Aqua);
	//�I���
	m_Batch->End();
}

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
	//�J�����̍X�V
	m_camera->Update(m_player->GetPos(), Matrix::Identity);

	//�v���C���[�̍X�V
	m_player->Update(elapsedTime);

	//�G�̍X�V
	m_enemy->Update(elapsedTime);

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

//�f�o�b�N�����܂Ƃ߂Ă���
void PlayScene::DrawDebug()
{
	//�n�߂�
	m_Batch->Begin();
	//// �f�o�b�O�����uDebugString�v�ŕ\������
	m_Font->DrawString(m_Batch, L"Play Scene", Vector2(10, 10), Colors::Black);
	//�������̃J�j�̏��
	float yPosition = 30.0f;
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		std::wstring crabHP = L"Crab:" + std::to_wstring(crab->GetHP());
		std::wstring crabState = L" State: " +std::to_wstring(crab->GetState());
		std::wstring CisAttacking = L" CAttack: " + BoolToString(Collision::GetInstance()->CheckHitAttackCrabsToPlayer());
		std::wstring PisAttacking = L" PAttack: " + BoolToString(Collision::GetInstance()->CheckHitAttackPlayerToCrab());
		m_Font->DrawString(m_Batch, crabHP.c_str(), Vector2(10, yPosition), Colors::Black);
		m_Font->DrawString(m_Batch, crabState.c_str(), Vector2(180, yPosition), Colors::Black);
		m_Font->DrawString(m_Batch, CisAttacking.c_str(), Vector2(260, yPosition), Colors::Black);
		m_Font->DrawString(m_Batch, PisAttacking.c_str(), Vector2(410, yPosition), Colors::Black);
		yPosition += 20.0f; 
	}
	////�{�X�̏��
	//auto& boss = m_enemy->GetBoss();
	//std::wstring bossHP = L"Boss:" + std::to_wstring(boss->GetHP());
	//m_Font->DrawString(m_Batch, bossHP.c_str(), Vector2(10, 90), Colors::Aqua);
	//�������̓G�̑���
	std::wstring ActiveEnemy = L"ActiveEnemy:" + std::to_wstring(m_enemy->GetActiveEnemyCount());
	m_Font->DrawString(m_Batch, ActiveEnemy.c_str(), Vector2(10, 110), Colors::Black);
	//�v���C���[�̃X�^�~�i
	std::wstring PSta = L"Player/Stamina:" + std::to_wstring(m_player->GetStamina());
	m_Font->DrawString(m_Batch, PSta.c_str(), Vector2(10, 130), Colors::Black);
	//�v���C���[�̗̑�
	std::wstring Php = L"Player/HP:" + std::to_wstring(m_player->GetHP());
	m_Font->DrawString(m_Batch, Php.c_str(), Vector2(10, 150), Colors::Black);
	//�I���
	m_Batch->End();
}
/*
	@file	PlayScene.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "PlayScene.h"
#include "Framework/Graphics.h"
#include "Framework/input.h"
#include "FrameWork/DeviceResources.h"
#include "Libraries/MyLib/TPS_Camera.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Scene/Play/Player/Player.h"
#include "Game/Scene/Play/Enemy/Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_camera{},
	m_gridFloor{},
	m_isChangeScene{},
	m_player{},
	m_enemy{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
PlayScene::~PlayScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void PlayScene::Initialize()
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	
	// �O���b�h�����쐬����
	m_gridFloor = std::make_unique<mylib::GridFloor>(device, context, states);

	// �J�������쐬����
	m_camera = std::make_unique<mylib::TPS_Camera>();

	//�v���C���[�̐���
	m_player = std::make_unique<Player>();

	//�G�̐���
	m_enemy = std::make_unique<Enemy>();

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = Input::GetInstance()->GetKeyTracker();
	const auto& kbState = Input::GetInstance()->GetKeyState();

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->pressed.Space)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void PlayScene::Render()
{
	// �R���e�L�X�g�A�X�e�[�g�A�r���[�s��A�ˉe�s����擾����
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	//�r���[�Ǝˉe�s��̐���
	Matrix projection = Graphics::GetInstance()->GetProjectionMatrix();
	Matrix view = Graphics::GetInstance()->GetViewMatrix();

	// �i�q����`�悷��
	m_gridFloor->Render(context, view, projection);

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

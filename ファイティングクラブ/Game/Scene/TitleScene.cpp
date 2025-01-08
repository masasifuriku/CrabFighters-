/*
	@file	TitleScene.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "TitleScene.h"
#include "Game/Screen.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Input.h"
#include "Framework/Resources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

extern void ExitGame() noexcept;

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_spriteBatch{},
	m_spriteFont{},
	m_title{},
	m_start01{},
	m_start02{},
	m_exit01{},
	m_exit02{},
	m_arrow{},
	m_back{},
	m_texCenter01{},
	m_texCenter02{},
	m_isChangeScene{},
	m_number{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
TitleScene::~TitleScene()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void TitleScene::Initialize()
{
	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();

	// �X�v���C�g�t�H���g���쐬����
	m_spriteFont = Graphics::GetInstance()->GetFont();

	// �e�N�X�`���̏����擾����================================
	m_title   = Resources::GetInstance()->GetTexture(L"title");
	m_start01 = Resources::GetInstance()->GetTexture(L"titleStart01");
	m_start02 = Resources::GetInstance()->GetTexture(L"titleStart02");
	m_exit01  = Resources::GetInstance()->GetTexture(L"titleExit01");
	m_exit02  = Resources::GetInstance()->GetTexture(L"titleExit02");
	m_arrow   = Resources::GetInstance()->GetTexture(L"titleArrow");
	m_back    = Resources::GetInstance()->GetTexture(L"titleBack");

	m_texCenter01 = Vector2(350, 100);
	m_texCenter02 = Vector2(640, 360);

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	m_number = 0;
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	// �錾���������A���ۂ͎g�p���Ă��Ȃ��ϐ�
	UNREFERENCED_PARAMETER(elapsedTime);

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = Input::GetInstance()->GetKeyTracker();

	if (kbTracker->pressed.Up)
	{
		if (m_number == 1)
		{
			m_number = 0;
		}
	}
	if (kbTracker->pressed.Down)
	{
		if (m_number == 0)
		{
			m_number = 1;
		}
	}

	// �X�y�[�X�L�[���������Start���I������Ă�����
	if (kbTracker->pressed.Space && m_number == 0)
	{
		m_isChangeScene = true;
	}
	// �X�y�[�X�L�[���������Exit���I������Ă�����
	if (kbTracker->pressed.Space && m_number == 1)
	{
		ExitGame();
	}
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void TitleScene::Render()
{
	auto states = Graphics::GetInstance()->GetCommonStates();

	// �X�v���C�g�o�b�`�̊J�n�F�I�v�V�����Ń\�[�g���[�h�A�u�����h�X�e�[�g���w�肷��
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// �摜�̒��S���v�Z����
	Vector2 pos01{ Screen::CENTER_X , Screen::CENTER_Y - 100 };
	Vector2 pos02{ Screen::CENTER_X , Screen::CENTER_Y + 80 };
	Vector2 pos03{ Screen::CENTER_X , Screen::CENTER_Y + 220 };
	Vector2 pos04{ Screen::CENTER_X - 170 , Screen::CENTER_Y + 80 };
	Vector2 pos05{ Screen::CENTER_X - 170 , Screen::CENTER_Y + 220 };
	Vector2 pos06{ Screen::CENTER_X , Screen::CENTER_Y };

	// ���S��`�悷��
	m_spriteBatch->Draw(m_back.Get(),  pos06,nullptr,Colors::White,0.0f,m_texCenter02,1.0f,SpriteEffects_None,0.0f);
	m_spriteBatch->Draw(m_title.Get(),  pos01,nullptr,Colors::White,0.0f,m_texCenter01,1.0f,SpriteEffects_None,0.0f);
	if (m_number == 0)
	{
		m_spriteBatch->Draw(m_arrow.Get(), pos04, nullptr, Colors::White, 0.0f, m_texCenter01, 1.0f, SpriteEffects_None, 0.0f);
		m_spriteBatch->Draw(m_start02.Get(), pos02, nullptr, Colors::White, 0.0f, m_texCenter01, 1.0f, SpriteEffects_None, 0.0f);
		m_spriteBatch->Draw(m_exit01.Get(), pos03, nullptr, Colors::White, 0.0f, m_texCenter01, 1.0f, SpriteEffects_None, 0.0f);
	}
	else
	{
		m_spriteBatch->Draw(m_arrow.Get(), pos05, nullptr, Colors::White, 0.0f, m_texCenter01, 1.0f, SpriteEffects_None, 0.0f);
		m_spriteBatch->Draw(m_start01.Get(), pos02, nullptr, Colors::White, 0.0f, m_texCenter01, 1.0f, SpriteEffects_None, 0.0f);
		m_spriteBatch->Draw(m_exit02.Get(), pos03, nullptr, Colors::White, 0.0f, m_texCenter01, 1.0f, SpriteEffects_None, 0.0f);
	}


	// �����ɃX�v���C�g�t�H���g�ŕ������`�悷����@
	m_spriteFont->DrawString(m_spriteBatch, L"Title Scene", Vector2(10, 40));

	// �X�v���C�g�o�b�`�̏I���
	m_spriteBatch->End();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// ���̃V�[��ID���擾����
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

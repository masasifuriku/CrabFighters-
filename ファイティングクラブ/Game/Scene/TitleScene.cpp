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

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_spriteBatch{},
	m_spriteFont{},
	m_texture{},
	m_texCenter{},
	m_isChangeScene{}
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
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();

	// �X�v���C�g�t�H���g���쐬����
	m_spriteFont = Graphics::GetInstance()->GetFont();

	// �e�N�X�`���̏����擾����================================
	// �e�N�X�`����ID3D11Resource�Ƃ��Č���
	m_texture = Resources::GetInstance()->GetTexture(L"title");

	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
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

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->pressed.Space)
	{
		m_isChangeScene = true;
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

	// TRIDENT���S�̕`��ʒu�����߂�
	RECT rect{ Graphics::GetInstance()->GetDeviceResources()->GetOutputSize()};
	// �摜�̒��S���v�Z����
	Vector2 pos{ rect.right / 2.0f, rect.bottom / 2.0f };

	// TRIDENT���S��`�悷��
	m_spriteBatch->Draw(
		m_texture.Get(),	// �e�N�X�`��(SRV)
		pos,				// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		nullptr,			// ��`(RECT)
		Colors::White,		// �w�i�F
		0.0f,				// ��]�p(���W�A��)
		m_texCenter,		// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		1.0f,				// �X�P�[��(scale)
		SpriteEffects_None,	// �G�t�F�N�g(effects)
		0.0f				// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
	);


	// �����ɃX�v���C�g�t�H���g�ŕ������`�悷����@
	m_spriteFont->DrawString(m_spriteBatch, L"Title Scene", Vector2(10, 40));

	wchar_t buf[32];
	swprintf_s(buf, 32, L"right : %d, bottom : %d", rect.right, rect.bottom);
	m_spriteFont->DrawString(m_spriteBatch, buf, Vector2(10,70));

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

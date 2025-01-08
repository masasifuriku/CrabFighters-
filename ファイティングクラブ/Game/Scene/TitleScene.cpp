/*
	@file	TitleScene.cpp
	@brief	タイトルシーンクラス
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
// コンストラクタ
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
// デストラクタ
//---------------------------------------------------------
TitleScene::~TitleScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TitleScene::Initialize()
{
	// スプライトバッチを作成する
	m_spriteBatch = Graphics::GetInstance()->GetSpriteBatch();

	// スプライトフォントを作成する
	m_spriteFont = Graphics::GetInstance()->GetFont();

	// テクスチャの情報を取得する================================
	m_title   = Resources::GetInstance()->GetTexture(L"title");
	m_start01 = Resources::GetInstance()->GetTexture(L"titleStart01");
	m_start02 = Resources::GetInstance()->GetTexture(L"titleStart02");
	m_exit01  = Resources::GetInstance()->GetTexture(L"titleExit01");
	m_exit02  = Resources::GetInstance()->GetTexture(L"titleExit02");
	m_arrow   = Resources::GetInstance()->GetTexture(L"titleArrow");
	m_back    = Resources::GetInstance()->GetTexture(L"titleBack");

	m_texCenter01 = Vector2(350, 100);
	m_texCenter02 = Vector2(640, 360);

	// シーン変更フラグを初期化する
	m_isChangeScene = false;
	m_number = 0;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);

	// キーボードステートトラッカーを取得する
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

	// スペースキーが押されてStartが選択されていたら
	if (kbTracker->pressed.Space && m_number == 0)
	{
		m_isChangeScene = true;
	}
	// スペースキーが押されてExitが選択されていたら
	if (kbTracker->pressed.Space && m_number == 1)
	{
		ExitGame();
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleScene::Render()
{
	auto states = Graphics::GetInstance()->GetCommonStates();

	// スプライトバッチの開始：オプションでソートモード、ブレンドステートを指定する
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// 画像の中心を計算する
	Vector2 pos01{ Screen::CENTER_X , Screen::CENTER_Y - 100 };
	Vector2 pos02{ Screen::CENTER_X , Screen::CENTER_Y + 80 };
	Vector2 pos03{ Screen::CENTER_X , Screen::CENTER_Y + 220 };
	Vector2 pos04{ Screen::CENTER_X - 170 , Screen::CENTER_Y + 80 };
	Vector2 pos05{ Screen::CENTER_X - 170 , Screen::CENTER_Y + 220 };
	Vector2 pos06{ Screen::CENTER_X , Screen::CENTER_Y };

	// ロゴを描画する
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


	// 純粋にスプライトフォントで文字列を描画する方法
	m_spriteFont->DrawString(m_spriteBatch, L"Title Scene", Vector2(10, 40));

	// スプライトバッチの終わり
	m_spriteBatch->End();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}

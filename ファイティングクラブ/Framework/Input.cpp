#include "pch.h"
#include "Input.h"

std::unique_ptr<Input> Input::m_input = nullptr;

// グラフィックスのインスタンスを取得する
Input* const Input::GetInstance()
{
	if (m_input == nullptr)
	{
		// グラフィックスのインスタンスを生成する
		m_input.reset(new Input());
	}
	// グラフィックスのインスタンスを返す
	return m_input.get();
}

// コンストラクタ
Input::Input()
	:
	m_keyboard{},     //キーボード
	m_keyTracker{},   //キーボードトラッカー
	m_keyState{},     //キーボードステート
	m_mouse{},        //マウス
	m_mouseTracker{}, //マウストラッカー
	m_mouseState{}    //マウスステート
{
}

// デストラクタ
Input::~Input()
{
}

// 初期化する
void Input::Initialize(const HWND& window)
{
	//キーボードの生成
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	m_keyState = std::make_unique<DirectX::Keyboard::State>();

	//マウスの生成
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	m_mouseState = std::make_unique<DirectX::Mouse::State>();
	//マウスにウィンドウを設定
	m_mouse->SetWindow(window);
}

void Input::UpdateInput()
{
	//キーボードの更新
	m_keyTracker->Update(m_keyboard->GetState());
	//マウスの更新
	m_mouseTracker->Update(m_mouse->GetState());
}


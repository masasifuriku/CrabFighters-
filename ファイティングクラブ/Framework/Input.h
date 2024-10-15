#pragma once
#ifndef Input_DEFINED
#define Input_DEFINED

//Inputクラス
class Input final
{
public:
	// Inputクラスのインスタンスを取得する
	static Input* const GetInstance();

	//キーボードトラッカーを取得する
	DirectX::Keyboard::KeyboardStateTracker* GetKeyTracker() { return m_keyTracker.get(); }
	//キーボードステートを取得する
	DirectX::Keyboard::State* GetKeyState() { return m_keyState.get(); }

	//マウストラッカーを取得する
	DirectX::Mouse::ButtonStateTracker* GetMouseTracker() { return m_mouseTracker.get(); }
	//マウスステートを取得する
	DirectX::Mouse::State* GetMouseState() { return m_mouseState.get();}

public:
	// デストラクタ
	~Input();
	// 初期化する
	void Initialize(const HWND& window);

	//キーボードの更新
	void UpdateInput();

private:
	// コンストラクタ
	Input();

	// 代入は許容しない
	void operator=(const Input& object) = delete;
	// コピーコンストラクタは許容しない
	Input(const Input& object) = delete;

private:
	// Inputクラスのインスタンスへのポインタ
	static std::unique_ptr<Input> m_input;

	//キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
	std::unique_ptr<DirectX::Keyboard::State> m_keyState;

	//マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;
	std::unique_ptr<DirectX::Mouse::State> m_mouseState;
};

#endif		// Input_DEFINED


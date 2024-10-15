#pragma once
#ifndef Input_DEFINED
#define Input_DEFINED

//Input�N���X
class Input final
{
public:
	// Input�N���X�̃C���X�^���X���擾����
	static Input* const GetInstance();

	//�L�[�{�[�h�g���b�J�[���擾����
	DirectX::Keyboard::KeyboardStateTracker* GetKeyTracker() { return m_keyTracker.get(); }
	//�L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State* GetKeyState() { return m_keyState.get(); }

	//�}�E�X�g���b�J�[���擾����
	DirectX::Mouse::ButtonStateTracker* GetMouseTracker() { return m_mouseTracker.get(); }
	//�}�E�X�X�e�[�g���擾����
	DirectX::Mouse::State* GetMouseState() { return m_mouseState.get();}

public:
	// �f�X�g���N�^
	~Input();
	// ����������
	void Initialize(const HWND& window);

	//�L�[�{�[�h�̍X�V
	void UpdateInput();

private:
	// �R���X�g���N�^
	Input();

	// ����͋��e���Ȃ�
	void operator=(const Input& object) = delete;
	// �R�s�[�R���X�g���N�^�͋��e���Ȃ�
	Input(const Input& object) = delete;

private:
	// Input�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Input> m_input;

	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
	std::unique_ptr<DirectX::Keyboard::State> m_keyState;

	//�}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseTracker;
	std::unique_ptr<DirectX::Mouse::State> m_mouseState;
};

#endif		// Input_DEFINED


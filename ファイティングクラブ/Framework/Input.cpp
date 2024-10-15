#include "pch.h"
#include "Input.h"

std::unique_ptr<Input> Input::m_input = nullptr;

// �O���t�B�b�N�X�̃C���X�^���X���擾����
Input* const Input::GetInstance()
{
	if (m_input == nullptr)
	{
		// �O���t�B�b�N�X�̃C���X�^���X�𐶐�����
		m_input.reset(new Input());
	}
	// �O���t�B�b�N�X�̃C���X�^���X��Ԃ�
	return m_input.get();
}

// �R���X�g���N�^
Input::Input()
	:
	m_keyboard{},     //�L�[�{�[�h
	m_keyTracker{},   //�L�[�{�[�h�g���b�J�[
	m_keyState{},     //�L�[�{�[�h�X�e�[�g
	m_mouse{},        //�}�E�X
	m_mouseTracker{}, //�}�E�X�g���b�J�[
	m_mouseState{}    //�}�E�X�X�e�[�g
{
}

// �f�X�g���N�^
Input::~Input()
{
}

// ����������
void Input::Initialize(const HWND& window)
{
	//�L�[�{�[�h�̐���
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	m_keyState = std::make_unique<DirectX::Keyboard::State>();

	//�}�E�X�̐���
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	m_mouseState = std::make_unique<DirectX::Mouse::State>();
	//�}�E�X�ɃE�B���h�E��ݒ�
	m_mouse->SetWindow(window);
}

void Input::UpdateInput()
{
	//�L�[�{�[�h�̍X�V
	m_keyTracker->Update(m_keyboard->GetState());
	//�}�E�X�̍X�V
	m_mouseTracker->Update(m_mouse->GetState());
}


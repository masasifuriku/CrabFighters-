//
// Game.h
//

#pragma once

#include "FrameWork/DeviceResources.h"
#include "StepTimer.h"

// ��include�̒ǋL��
#include "Interface/IScene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/MyLib/DebugString.h"
#include "Framework/Graphics.h"
#include "Framework/Input.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    DX::DeviceResources*    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    // �f�o�b�O�X�g�����O
    std::unique_ptr<mylib::DebugString>     m_debugString;

    // �V�[���}�l�[�W��
    std::unique_ptr<SceneManager>           m_sceneManager;

    //�O���t�B�b�N�X
    Graphics* m_graphics;
    //�C���v�b�g
    Input* m_input;


    // �t���X�N���[���֘A
private:
    // �t���X�N���[������
    BOOL m_fullScreen;

public:
    // ��ʃ��[�h��ύX����֐��iTRUE:�t���X�N���[���j
    void SetFullscreenState(BOOL value)
    {
        m_fullScreen = value;
        m_deviceResources->GetSwapChain()->SetFullscreenState(value, nullptr);
        if (value) m_deviceResources->CreateWindowSizeDependentResources();
    }
};

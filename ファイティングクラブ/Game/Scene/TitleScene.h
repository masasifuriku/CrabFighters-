/*
	@file	TitleScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "Interface/IScene.h"

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class TitleScene final :
    public IScene
{
private:
	// �X�v���C�g�o�b�`
	DirectX::SpriteBatch* m_spriteBatch;

	// �X�v���C�g�t�H���g
	DirectX::SpriteFont* m_spriteFont;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_start01;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_start02;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_exit01;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_exit02;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_arrow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_back;

	// �e�N�X�`���̔����̑傫��
	DirectX::SimpleMath::Vector2 m_texCenter01;
	DirectX::SimpleMath::Vector2 m_texCenter02;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	//�I����
	int m_number;


public:
    TitleScene();
    ~TitleScene() override;

    void Initialize() override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;
};

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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// �e�N�X�`���̔����̑傫��
	DirectX::SimpleMath::Vector2 m_texCenter;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;


public:
    TitleScene();
    ~TitleScene() override;

    void Initialize() override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;
};

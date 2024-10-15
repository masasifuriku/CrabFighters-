/*
	@file	TitleScene.h
	@brief	タイトルシーンクラス
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
	// スプライトバッチ
	DirectX::SpriteBatch* m_spriteBatch;

	// スプライトフォント
	DirectX::SpriteFont* m_spriteFont;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// テクスチャの半分の大きさ
	DirectX::SimpleMath::Vector2 m_texCenter;

	// シーンチェンジフラグ
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

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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_title;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_start01;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_start02;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_exit01;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_exit02;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_arrow;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_back;

	// テクスチャの半分の大きさ
	DirectX::SimpleMath::Vector2 m_texCenter01;
	DirectX::SimpleMath::Vector2 m_texCenter02;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	//選択肢
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

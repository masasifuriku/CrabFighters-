/*
	@file	TextureManager.cpp
	@brief	テクスチャの読み込み・描画クラス
*/
#include "pch.h"
#include "TextureManager.h"


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Ede::TextureManager::TextureManager()
	:
	m_texture{}
{
}

//テクスチャの読み込み
void Ede::TextureManager::AddTextureData(const char* key, const TCHAR* pass)
{
	// テクスチャを読み込む
	//std::unique_ptr<Microsoft::WRL::ComPtr <ID3D11ShaderResourceView>> temp = ;
	//テクスチャを登録する
	//m_texture.emplace(key, std::move(temp));
}

//テクスチャの描画
void Ede::TextureManager::DrawTexture(const char* key)
{
	//引数で指定されたキーのテクスチャを探して保存
	//std::map<const char*, std::unique_ptr<Microsoft::WRL::ComPtr <ID3D11ShaderResourceView>>>::const_iterator it = m_texture.find(key);
	//見つけたテクスチャの描画
}
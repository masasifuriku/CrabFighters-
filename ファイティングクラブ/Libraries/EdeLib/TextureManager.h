/*
	@file	TextureManager.h
	@brief	�e�N�X�`���̓ǂݍ��݁E�`��N���X
*/
#pragma once
#include<map>
#include<memory>

namespace Ede
{
	class TextureManager
	{
	private:
		std::map < const char*, std::unique_ptr<Microsoft::WRL::ComPtr <ID3D11ShaderResourceView>>>m_texture;
	public:
		TextureManager();

	public:
		void AddTextureData(const char* key, const TCHAR* pass);
		void DrawTexture(const char* key);
	};
}
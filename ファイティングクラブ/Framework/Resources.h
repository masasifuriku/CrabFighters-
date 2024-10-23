#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Graphics.h"
#include <string>
#include <unordered_map>

// Resourcesクラスを定義する
class Resources
{
public:
	//
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(const wchar_t* name);
public:
	Resources(Resources&&) = default;
	Resources& operator= (Resources&&) = default;
	Resources& operator= (Resources const&) = delete;
	// デストラクタ
	~Resources() = default;
	// Resoucesクラスのインスタンスを取得する
	static Resources* const GetInstance();
	// リソースをロードする
	void LoadResource();

private:
	// コンストラクタ
	Resources() noexcept
	{
	}

private:
	// リソース
	static std::unique_ptr<Resources> m_resources;

	//
	std::unordered_map<const wchar_t*, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
};

#endif		// RESOURCES_DEFINED

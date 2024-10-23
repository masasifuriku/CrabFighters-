#include "pch.h"
#include "Resources.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

// Resourcesクラスのインスタンスを取得する
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resourcesクラスのインスタンスを生成する
		m_resources.reset(new Resources());
	}
	// Resourcesクラスのインスタンスを返す
	return m_resources.get();
}

// リソースをロードする
void Resources::LoadResource()
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//変数
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Title;//タイトル

	//読み込む
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Title.png", nullptr, Title.GetAddressOf());

	//テクスチャに登録
	m_texture.emplace(L"title", Title);
}

//
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	//テクスチャを検索
	auto it = m_texture.find(name);
	return it->second;
}

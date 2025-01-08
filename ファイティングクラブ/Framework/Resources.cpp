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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Start01;//スタート1
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Start02;//スタート2
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Exit01;//エンド1
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Exit02;//エンド2
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Arrow;//矢印
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Back;//背景

	//読み込む
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Title.png",        nullptr, Title.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleStart01.png", nullptr, Start01.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleStart02.png", nullptr, Start02.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleExit01.png",  nullptr, Exit01.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleExit02.png",  nullptr, Exit02.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleArrow.png",   nullptr, Arrow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Back.png",         nullptr, Back.GetAddressOf());

	//テクスチャに登録
	m_texture.emplace(L"title",        Title);
	m_texture.emplace(L"titleStart01", Start01);
	m_texture.emplace(L"titleStart02", Start02);
	m_texture.emplace(L"titleExit01",  Exit01);
	m_texture.emplace(L"titleExit02",  Exit02);
	m_texture.emplace(L"titleArrow",   Arrow);
	m_texture.emplace(L"titleBack",    Back);
}

//指定されたテクスチャを探して渡す
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	//テクスチャを検索
	auto it = m_texture.find(name);
	return it->second;
}

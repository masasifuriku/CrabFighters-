#include "pch.h"
#include "Resources.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

// Resources�N���X�̃C���X�^���X���擾����
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resources�N���X�̃C���X�^���X�𐶐�����
		m_resources.reset(new Resources());
	}
	// Resources�N���X�̃C���X�^���X��Ԃ�
	return m_resources.get();
}

// ���\�[�X�����[�h����
void Resources::LoadResource()
{
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//�ϐ�
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Title;//�^�C�g��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Start01;//�X�^�[�g1
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Start02;//�X�^�[�g2
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Exit01;//�G���h1
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Exit02;//�G���h2
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Arrow;//���
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Back;//�w�i

	//�ǂݍ���
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Title.png",        nullptr, Title.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleStart01.png", nullptr, Start01.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleStart02.png", nullptr, Start02.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleExit01.png",  nullptr, Exit01.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleExit02.png",  nullptr, Exit02.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/TitleArrow.png",   nullptr, Arrow.GetAddressOf());
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Back.png",         nullptr, Back.GetAddressOf());

	//�e�N�X�`���ɓo�^
	m_texture.emplace(L"title",        Title);
	m_texture.emplace(L"titleStart01", Start01);
	m_texture.emplace(L"titleStart02", Start02);
	m_texture.emplace(L"titleExit01",  Exit01);
	m_texture.emplace(L"titleExit02",  Exit02);
	m_texture.emplace(L"titleArrow",   Arrow);
	m_texture.emplace(L"titleBack",    Back);
}

//�w�肳�ꂽ�e�N�X�`����T���ēn��
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	//�e�N�X�`��������
	auto it = m_texture.find(name);
	return it->second;
}

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

	//�ǂݍ���
	DirectX::CreateWICTextureFromFile(device, context, L"Resources/Textures/Title.png", nullptr, Title.GetAddressOf());

	//�e�N�X�`���ɓo�^
	m_texture.emplace(L"title", Title);
}

//
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Resources::GetTexture(const wchar_t* name)
{
	//�e�N�X�`��������
	auto it = m_texture.find(name);
	return it->second;
}

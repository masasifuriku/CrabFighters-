#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Graphics.h"
#include <string>
#include <unordered_map>

// Resources�N���X���`����
class Resources
{
public:
	//�w�肳�ꂽ�e�N�X�`����T���ēn��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(const wchar_t* name);
public:
	Resources(Resources&&) = default;
	Resources& operator= (Resources&&) = default;
	Resources& operator= (Resources const&) = delete;
	// �f�X�g���N�^
	~Resources() = default;
	// Resouces�N���X�̃C���X�^���X���擾����
	static Resources* const GetInstance();
	// ���\�[�X�����[�h����
	void LoadResource();

private:
	// �R���X�g���N�^
	Resources() noexcept
	{
	}

private:
	// ���\�[�X
	static std::unique_ptr<Resources> m_resources;
	//�e�N�X�`���i�[�ϐ�
	std::unordered_map<const wchar_t*, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
};

#endif		// RESOURCES_DEFINED

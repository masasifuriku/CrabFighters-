/*
	@file	TextureManager.cpp
	@brief	�e�N�X�`���̓ǂݍ��݁E�`��N���X
*/
#include "pch.h"
#include "TextureManager.h"


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Ede::TextureManager::TextureManager()
	:
	m_texture{}
{
}

//�e�N�X�`���̓ǂݍ���
void Ede::TextureManager::AddTextureData(const char* key, const TCHAR* pass)
{
	// �e�N�X�`����ǂݍ���
	//std::unique_ptr<Microsoft::WRL::ComPtr <ID3D11ShaderResourceView>> temp = ;
	//�e�N�X�`����o�^����
	//m_texture.emplace(key, std::move(temp));
}

//�e�N�X�`���̕`��
void Ede::TextureManager::DrawTexture(const char* key)
{
	//�����Ŏw�肳�ꂽ�L�[�̃e�N�X�`����T���ĕۑ�
	//std::map<const char*, std::unique_ptr<Microsoft::WRL::ComPtr <ID3D11ShaderResourceView>>>::const_iterator it = m_texture.find(key);
	//�������e�N�X�`���̕`��
}
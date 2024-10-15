/*
	@file	ModelManager.h
	@brief	3D���f���̓ǂݍ��݁E�`��N���X
*/
#pragma once
#include<map>
#include<memory>

// ��ʓI�ȃV�[���N���X
namespace Ede
{
	class ModelManager
	{
	private:
		std::map < const char*, std::unique_ptr<DirectX::Model>>m_model;
	public:
		ModelManager();

	public:
		void AddModelData(const char* key, const TCHAR* pass, ID3D11Device1* device);
		void DrawModel(const char* key,
			ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix world,
			DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	};
}

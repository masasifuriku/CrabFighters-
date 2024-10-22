/*
	@file	ModelManager.h
	@brief	3D���f���̓ǂݍ��݁E�`��N���X
*/
#pragma once
#include<map>
#include<memory>

namespace Ede
{
	class ModelManager
	{
	private:
		std::map < const char*, std::unique_ptr<DirectX::Model>>m_model;
	public:
		ModelManager();

	public:
		void AddModelData(const char* key, const TCHAR* pass);
		void DrawModel(const char* key,
			const DirectX::SimpleMath::Matrix& world
		);
	};
}

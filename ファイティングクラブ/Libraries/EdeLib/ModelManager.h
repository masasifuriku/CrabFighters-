/*
	@file	ModelManager.h
	@brief	3Dモデルの読み込み・描画クラス
*/
#pragma once
#include<map>
#include<memory>

// 一般的なシーンクラス
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

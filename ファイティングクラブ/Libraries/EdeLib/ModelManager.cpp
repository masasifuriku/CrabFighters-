/*
	@file	ModelManager.cpp
	@brief	3Dモデルの読み込み・描画クラス
*/
#include "pch.h"
#include "ModelManager.h"


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Ede::ModelManager::ModelManager()
	:
	m_model{}
{
}

//3Dモデルの読み込み
void Ede::ModelManager::AddModelData(const char* key, const TCHAR* pass,ID3D11Device1* device)
{
	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// モデルを読み込む
	std::unique_ptr<DirectX::Model> temp = DirectX::Model::CreateFromCMO(device, pass, *fx);
	//モデルに登録する
	m_model.emplace(key, std::move(temp));
}

//3Dモデルの描画
void Ede::ModelManager::DrawModel(const char* key,
	ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix world,
	DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//引数で指定されたキーのモデルを探して保存
	std::map<const char*, std::unique_ptr<DirectX::Model>>::const_iterator it = m_model.find(key);
	//見つけたモデルの描画
	it->second->Draw(context, *states, world, view, proj);
}
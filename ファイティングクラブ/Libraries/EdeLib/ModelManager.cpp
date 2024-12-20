/*
	@file	ModelManager.cpp
	@brief	3Dモデルの読み込み・描画クラス
*/
#include "pch.h"
#include "ModelManager.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"



//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Ede::ModelManager::ModelManager()
	:
	m_model{}
{
}

//3Dモデルの読み込み
void Ede::ModelManager::AddModelData(const char* key, const TCHAR* pass)
{
	// モデルを読み込む準備
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	fx->SetDirectory(L"Resources/Models");
	// モデルを読み込む
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	std::unique_ptr<DirectX::Model> temp = DirectX::Model::CreateFromCMO(device, pass, *fx);
	//モデルを登録する
	m_model.emplace(key, std::move(temp));
}

//3Dモデルの描画
void Ede::ModelManager::DrawModel(
	const char* key,
	const DirectX::SimpleMath::Matrix& world
	)
{
	//引数で指定されたキーのモデルを探して保存
	std::map<const char*, std::unique_ptr<DirectX::Model>>::const_iterator it = m_model.find(key);
	//見つけたモデルの描画
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	DirectX::SimpleMath::Matrix view = Graphics::GetInstance()->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	// ライトを切る設定
	it->second->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ライトをきる
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
				// 環境光を黒に
				lights->SetAmbientLightColor(DirectX::Colors::Red);
			}
			// 自己発光させる
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
			}
		});

	it->second->Draw(context, *states, world, view, proj);
}
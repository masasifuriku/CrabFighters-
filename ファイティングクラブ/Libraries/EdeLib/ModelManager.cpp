/*
	@file	ModelManager.cpp
	@brief	3D���f���̓ǂݍ��݁E�`��N���X
*/
#include "pch.h"
#include "ModelManager.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"



//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Ede::ModelManager::ModelManager()
	:
	m_model{}
{
}

//3D���f���̓ǂݍ���
void Ede::ModelManager::AddModelData(const char* key, const TCHAR* pass)
{
	// ���f����ǂݍ��ޏ���
	DirectX::EffectFactory* fx = Graphics::GetInstance()->GetFX();
	fx->SetDirectory(L"Resources/Models");
	// ���f����ǂݍ���
	auto device = Graphics::GetInstance()->GetDeviceResources()->GetD3DDevice();
	std::unique_ptr<DirectX::Model> temp = DirectX::Model::CreateFromCMO(device, pass, *fx);
	//���f����o�^����
	m_model.emplace(key, std::move(temp));
}

//3D���f���̕`��
void Ede::ModelManager::DrawModel(
	const char* key,
	const DirectX::SimpleMath::Matrix& world
	)
{
	//�����Ŏw�肳�ꂽ�L�[�̃��f����T���ĕۑ�
	std::map<const char*, std::unique_ptr<DirectX::Model>>::const_iterator it = m_model.find(key);
	//���������f���̕`��
	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = Graphics::GetInstance()->GetCommonStates();
	DirectX::SimpleMath::Matrix view = Graphics::GetInstance()->GetViewMatrix();
	DirectX::SimpleMath::Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	// ���C�g��؂�ݒ�
	it->second->UpdateEffects([](DirectX::IEffect* effect)
		{
			// ���C�g������
			auto lights = dynamic_cast<DirectX::IEffectLights*>(effect);
			if (lights)
			{
				lights->SetLightEnabled(0, false);
				lights->SetLightEnabled(1, false);
				lights->SetLightEnabled(2, false);
				// ����������
				lights->SetAmbientLightColor(DirectX::Colors::Red);
			}
			// ���Ȕ���������
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(DirectX::Colors::White);
			}
		});

	it->second->Draw(context, *states, world, view, proj);
}
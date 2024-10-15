/*
	@file	ModelManager.cpp
	@brief	3D���f���̓ǂݍ��݁E�`��N���X
*/
#include "pch.h"
#include "ModelManager.h"


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Ede::ModelManager::ModelManager()
	:
	m_model{}
{
}

//3D���f���̓ǂݍ���
void Ede::ModelManager::AddModelData(const char* key, const TCHAR* pass,ID3D11Device1* device)
{
	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");
	// ���f����ǂݍ���
	std::unique_ptr<DirectX::Model> temp = DirectX::Model::CreateFromCMO(device, pass, *fx);
	//���f���ɓo�^����
	m_model.emplace(key, std::move(temp));
}

//3D���f���̕`��
void Ede::ModelManager::DrawModel(const char* key,
	ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix world,
	DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//�����Ŏw�肳�ꂽ�L�[�̃��f����T���ĕۑ�
	std::map<const char*, std::unique_ptr<DirectX::Model>>::const_iterator it = m_model.find(key);
	//���������f���̕`��
	it->second->Draw(context, *states, world, view, proj);
}
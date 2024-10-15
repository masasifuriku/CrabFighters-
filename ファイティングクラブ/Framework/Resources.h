#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Model.h"
#include "Graphics.h"

// Resources�N���X���`����
class Resources
{
public:
	// �u�C���v���f�����擾����
	DirectX::Model* GetTurretModel() { return m_turretModel.get(); }
	// �u�C�������v���f�����擾����
	DirectX::Model* GetTurretBottomModel() { return m_turretBottomModel.get(); }
	// �u�C�������r�v���f�����擾����
	DirectX::Model* GetTurretBottomFootModel() { return m_turretFootModel.get(); }
	// �u�C�������v���[�g�v���f�����擾����
	DirectX::Model* GetTurretMiddlePlateModel() { return m_turretPlateModel.get(); }
	// �u�C�������v���f�����擾����
	DirectX::Model* GetTurretMiddleModel() { return m_turretMiddleModel.get(); }
	// �u�C���㕔�v���f�����擾����
	DirectX::Model* GetTurretTopModel() { return m_turretTopModel.get(); }
	// �u�C���C��v���f�����擾����
	DirectX::Model* GetTurretFortModel() { return m_turretFortModel.get(); }
	// �u�C���C�g�v���f�����擾����
	DirectX::Model* GetTurretGunModel() { return m_turretGunModel.get(); }
	// �u�C�e�v���f�����擾����
	DirectX::Model* GetBulletModel() { return m_bulletModel.get(); }

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
		:
		m_turretModel{},
		m_turretBottomModel{},					// �C���������f��
		m_turretFootModel{},							// �C���r���f��
		m_turretPlateModel{},						// �C���v���[�g���f��
		m_turretMiddleModel{},					// �C���������f��
		m_turretTopModel{},							// �C���㕔���f��
		m_turretFortModel{},							// �C�䃂�f��
		m_turretGunModel{},							// �C�g���f��
		m_bulletModel{}									// �C�e���f��
	{
	}

private:
	// ���\�[�X
	static std::unique_ptr<Resources> m_resources;
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �f�o�C�X
	ID3D11Device* m_device = m_graphics->GetDeviceResources()->GetD3DDevice();

	// �u�C���v���f��
	std::unique_ptr<DirectX::Model> m_turretModel;
	// �u�C�������v���f��
	std::unique_ptr<DirectX::Model> m_turretBottomModel;
	// �u�C���r�v���f��
	std::unique_ptr<DirectX::Model> m_turretFootModel;
	// �u�C���v���[�g�v
	std::unique_ptr<DirectX::Model> m_turretPlateModel;
	// �u�C�������v
	std::unique_ptr<DirectX::Model> m_turretMiddleModel;
	// �u�C���㕔�v���f��
	std::unique_ptr<DirectX::Model> m_turretTopModel;
	// �u�C��v���f��
	std::unique_ptr<DirectX::Model> m_turretFortModel;
	// �u�C�g�v���f��
	std::unique_ptr<DirectX::Model> m_turretGunModel;
	// �u�C�e�v���f��
	std::unique_ptr<DirectX::Model> m_bulletModel;
};

#endif		// RESOURCES_DEFINED

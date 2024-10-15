#include "pch.h"
#include "Resources.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

// Resources�N���X�̃C���X�^���X���擾����
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resources�N���X�̃C���X�^���X�𐶐�����
		m_resources.reset(new Resources());
	}
	// Resources�N���X�̃C���X�^���X��Ԃ�
	return m_resources.get();
}

// ���\�[�X�����[�h����
void Resources::LoadResource()
{
	// ���\�[�X�f�B���N�g����ݒ肷��
	m_graphics->GetFX()->SetDirectory(L"resources\\cmo");
	// �u�C�������v���f�������[�h����
	m_turretBottomModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\turret_bottom3.cmo", *m_graphics->GetFX());	
	// �u�C���r�v���f�������[�h����
	m_turretFootModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\turret_bottom_foot.cmo", *m_graphics->GetFX());
	// �u�C���v���[�g�v���f�������[�h����
	m_turretPlateModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\turret_plate.cmo", *m_graphics->GetFX());
	// �u�C�������v���f�������[�h����
	m_turretMiddleModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\turret_middle.cmo", *m_graphics->GetFX());
	// �u�C���㕔�v���f�������[�h����
	m_turretTopModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\turret_top.cmo", *m_graphics->GetFX());
	// �u�C��v���f�������[�h����
	m_turretFortModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\turret_fort.cmo", *m_graphics->GetFX());
	// �u��C�v���f�������[�h����
	m_turretGunModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\turret_gun.cmo", *m_graphics->GetFX());
	// �u�C�e�v���f�������[�h����
	m_bulletModel = DirectX::Model::CreateFromCMO(m_device, L"resources\\cmo\\bullet.cmo", *m_graphics->GetFX());
}

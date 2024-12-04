/*
	@file	SkyDome.cpp
	@brief	�V���N���X
*/
#include "pch.h"
#include "SkyDome.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SkyDome::SkyDome()
	:
	m_projection{},
	m_model{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
SkyDome::~SkyDome()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void SkyDome::Initialize()
{
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();
	// �ˉe�s����쐬����
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);

	// ���f����ǂݍ���
		// �v���C���[���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Dome", L"Resources/Models/seaDome.cmo");
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void SkyDome::Render()
{
	// ���[���h�s����X�V����
	Matrix  size, world;
	size = Matrix::CreateScale(1.1f);
	world = size;


	// ���f����`�悷��
	m_model->DrawModel("Dome", world);
}


//--------------------------------------------------------------------------------------
// File: EnemyBossHead.cpp
//
// �{�X���N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBossHead.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"

#include "Libraries/Microsoft/DebugDraw.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBossHead::EnemyBossHead()
	:
	m_model{},
	m_BoundingSphere{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBossHead::~EnemyBossHead()
{
}

void EnemyBossHead::Initialize()
{
	// ���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Boss", L"Resources/Models/BossHead.cmo");
	// �o�E���f�B���O�X�t�B�A�𐶐�����
	m_BoundingSphere = CreateBoundingSphere(11.0f);
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void EnemyBossHead::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
}

/// <summary>
/// �`��֐�
/// </summary>
void EnemyBossHead::Render()
{
	Matrix world;
	m_model->DrawModel("Boss", world);
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere EnemyBossHead::CreateBoundingSphere(const float& radius)
{
	// �o�E���f�B���O�X�t�B�A��錾����
	DirectX::BoundingSphere turretBoundingSphere;
	// �o�E���f�B���O�X�t�B�A�̔��a��ݒ肷��
	turretBoundingSphere.Radius = radius;
	// �o�E���f�B���O�X�t�B�A��Ԃ�
	return turretBoundingSphere;
}

// �o�E���f�B���O�X�t�B�A��`�悷��
void EnemyBossHead::DrawBoundingSphere()
{
	// ����F��ݒ肷��
	DirectX::XMVECTOR color = DirectX::Colors::Yellow;
	auto batch = Graphics::GetInstance();
	// �v���~�e�B�u�`����J�n����
	batch->DrawPrimitiveBegin(batch->GetViewMatrix(), batch->GetProjectionMatrix());
	// �C���̋��E����`�悷��
	DX::Draw(batch->GetPrimitiveBatch(), m_BoundingSphere, color);
	// �v���~�e�B�u�`����I������
	batch->DrawPrimitiveEnd();
}
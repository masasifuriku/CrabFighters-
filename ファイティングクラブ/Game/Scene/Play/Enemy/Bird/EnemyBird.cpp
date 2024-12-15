//--------------------------------------------------------------------------------------
// File: EnemyBird.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBird.h"
#include "Game/Scene/Play/Enemy/Bird/States/BirdPatrol.h"
#include "Game/Scene/Play/Enemy/Bird/States/BirdChase.h"
#include "Game/Scene/Play/Enemy/Bird/States/BirdAttack.h"
#include "Game/Scene/Play/Enemy/Bird/States/BirdEscape.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Libraries/Microsoft/DebugDraw.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBird::EnemyBird()
	:
	m_model{},
	m_state{ DEAD }, 
	m_BoundingSphere{},
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_angle{},
	m_health{},
	m_patrol{},
	m_chase{},
	m_attack{},
	m_escape{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBird::~EnemyBird()
{
}

void EnemyBird::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// ���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("dice", L"Resources/Models/dice.cmo");
	//��Ԃ̐ݒ�
	m_state = state;
	// �o�E���f�B���O�X�t�B�A�𐶐�����
	m_BoundingSphere = CreateBoundingSphere(11.0f);
	//���W������������
	m_position = position;
	//���x
	m_velocity = Vector3::Zero;
	//��]
	m_rotate = Quaternion::FromToRotation(Vector3::UnitZ, -Vector3::UnitZ);
	//�s��
	m_world = Matrix::Identity;
	//�p�x
	m_angle = 0.0f;
	//HP
	m_health = 100.0f;

	//�X�e�[�g
	m_patrol = std::make_unique<BirdPatrol>(this);
	m_chase  = std::make_unique<BirdChase>(this);
	m_attack = std::make_unique<BirdAttack>(this);
	m_escape = std::make_unique<BirdEscape>(this);
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void EnemyBird::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
	//m_position = m_velocity;
	if (m_health <= 0.0f)
	{
		m_state = DEAD;
	}
}

/// <summary>
/// �`��֐�
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�ˉe�s��</param>
void EnemyBird::Render(
	Vector3 pos,
	Matrix normal
)
{
	m_position = pos;
	m_BoundingSphere.Center = m_position;
	Matrix rotation, translation;
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = rotation * normal * translation;

	// ���f����`�悷��
	if (m_state != DEAD)
	{
		m_model->DrawModel("dice", m_world);
	}
}

//������Ԃ����f����
bool EnemyBird::IsActive()
{
	//��Ԃ����S�ȊO�Ȃ琶�����Ȃ̂�true��Ԃ�
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//�_���[�W���󂯂�
void EnemyBird::TakeDamage(float damage)
{
	m_health -= damage;
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere EnemyBird::CreateBoundingSphere(const float& radius)
{
	// �o�E���f�B���O�X�t�B�A��錾����
	DirectX::BoundingSphere turretBoundingSphere;
	// �o�E���f�B���O�X�t�B�A�̔��a��ݒ肷��
	turretBoundingSphere.Radius = radius;
	// �o�E���f�B���O�X�t�B�A��Ԃ�
	return turretBoundingSphere;
}

// �o�E���f�B���O�X�t�B�A��`�悷��
void EnemyBird::DrawBoundingSphere()
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


//�X�e�[�g�̍X�V
void EnemyBird::UpdateState(Vector3 player)
{
	switch (m_state)
	{
		case Patrol:
			m_patrol->Update();
			break;
		case Chase:
			m_chase->Update(player);
			break;
		case Battle:
			m_attack->Update();
			break;
		case Escape:
			m_escape->Update(player);
			break;
		case DEAD:
			break;
		default:
			break;
	}
}
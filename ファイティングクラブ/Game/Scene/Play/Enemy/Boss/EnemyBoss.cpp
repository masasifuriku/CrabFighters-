//--------------------------------------------------------------------------------------
// File: EnemyBoss.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyBoss.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossPatrol.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossChase.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossAttack.h"
#include "Game/Scene/Play/Enemy/Boss/States/BossEscape.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Framework/Collision.h"

#include "Libraries/Microsoft/DebugDraw.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyBoss::EnemyBoss(PlayerBody* player)
	:
	m_model{},
	m_state{ DEAD }, 
	m_BoundingSphere{},
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_health{},
	m_angle{},
	m_player{ player },
	m_patrol{},
	m_chase{},
	m_attack{},
	m_escape{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// ���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Boss", L"Resources/Models/dice.cmo");
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
	//�̗�
	m_health = 300.0f;
	//�p�x
	m_angle = 0.0f;

	//�X�e�[�g
	m_patrol = std::make_unique<BossPatrol>(this);
	m_chase  = std::make_unique<BossChase>(this);
	m_attack = std::make_unique<BossAttack>(this);
	m_escape = std::make_unique<BossEscape>(this);

	Collision::GetInstance()->SetBoss(this);
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void EnemyBoss::Update(float timer)
{
	UNREFERENCED_PARAMETER(timer);
	UpdateState();
}

/// <summary>
/// �`��֐�
/// </summary>
void EnemyBoss::Render(
	Vector3 pos,
	Matrix normal
)
{
	m_position = pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(3.0f);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

	// ���f����`�悷��
	if (m_state != DEAD)
	{
		m_model->DrawModel("Boss", m_world);
	}
}

//������Ԃ����f����
bool EnemyBoss::IsActive()
{
	//��Ԃ����S�ȊO�Ȃ琶�����Ȃ̂�true��Ԃ�
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//�_���[�W���󂯂�
void EnemyBoss::TakeDamage(float damage)
{
	m_health -= damage;
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere EnemyBoss::CreateBoundingSphere(const float& radius)
{
	// �o�E���f�B���O�X�t�B�A��錾����
	DirectX::BoundingSphere turretBoundingSphere;
	// �o�E���f�B���O�X�t�B�A�̔��a��ݒ肷��
	turretBoundingSphere.Radius = radius;
	// �o�E���f�B���O�X�t�B�A��Ԃ�
	return turretBoundingSphere;
}

// �o�E���f�B���O�X�t�B�A��`�悷��
void EnemyBoss::DrawBoundingSphere()
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
void EnemyBoss::UpdateState()
{
	switch (m_state)
	{
		case Patrol:
			m_patrol->Update();
			break;
		case Chase:
			m_chase->Update(m_player->GetPos());
			break;
		case Battle:
			m_attack->Update();
			break;
		case Escape:
			m_escape->Update(m_player->GetPos());
			break;
		case DEAD:
			break;
		default:
			break;
	}
}
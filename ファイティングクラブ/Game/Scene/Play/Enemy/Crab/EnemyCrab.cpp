//--------------------------------------------------------------------------------------
// File: EnemyCrab.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrab.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/Crab/EnemyCrabHand.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabPatrol.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabChase.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabAttack.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabEscape.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Libraries/Microsoft/DebugDraw.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyCrab::EnemyCrab(PlayerBody* player)
	:
	m_model{},
	m_hand{},
	m_state{ DEAD }, 
	m_BoundingSphere{},
	m_position{},
	m_rotate{},
	m_world{},
	m_angle{},
	m_size{},
	m_health{},
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
EnemyCrab::~EnemyCrab()
{
}

void EnemyCrab::Initialize(DirectX::SimpleMath::Vector3 position)
{
	// ���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("crab", L"Resources/Models/ogani-.cmo");
	//�v���C���[�̘r
	m_hand = std::make_unique<EnemyCrabHand>();
	m_hand->Initialize();
	//��Ԃ̐ݒ�
	m_state = NONE;
	// �o�E���f�B���O�X�t�B�A�𐶐�����
	m_BoundingSphere = CreateBoundingSphere(0.9f);
	//���W������������
	m_position = position;
	//��]
	m_rotate = Quaternion::Identity;
	//�s��
	m_world = Matrix::Identity;
	//�p�x
	m_angle = 0.0f;
	//�T�C�Y
	m_size = 0.08f;
	//HP
	m_health = 100.0f;

	//�X�e�[�g
	m_patrol = std::make_unique<CrabPatrol>(this);
	m_chase  = std::make_unique<CrabChase>(this);
	m_attack = std::make_unique<CrabAttack>(this, m_player,m_hand.get());
	m_escape = std::make_unique<CrabEscape>(this);

	Collision::GetInstance()->SetCrab(this);
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void EnemyCrab::Update(float timer)
{
	ChangeState();
	UpdateState(timer);
}

/// <summary>
/// �`��֐�
/// </summary>
void EnemyCrab::Render(
	Vector3 pos,
	Matrix normal
)
{
	//�X�e�[�W�Ƃ̔���
	m_position = pos;
	//�o�E���f�B���O�X�t�B�A�̒��S�_��ݒ�
	m_BoundingSphere.Center = m_position;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(m_size);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

	// ���f����`�悷��
	if (m_state != DEAD)
	{
		m_model->DrawModel("crab",m_world);
		m_hand->Render(m_world);
		//DrawBoundingSphere();
	}
}

//������Ԃ����f����
bool EnemyCrab::IsActive()
{
	//��Ԃ����S�ȊO�Ȃ琶�����Ȃ̂�true��Ԃ�
	if (m_state != DEAD)
	{
		return true;
	}
	return false;
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere EnemyCrab::CreateBoundingSphere(const float& radius)
{
	// �o�E���f�B���O�X�t�B�A��錾����
	DirectX::BoundingSphere turretBoundingSphere;
	// �o�E���f�B���O�X�t�B�A�̔��a��ݒ肷��
	turretBoundingSphere.Radius = radius;
	// �o�E���f�B���O�X�t�B�A��Ԃ�
	return turretBoundingSphere;
}

// �o�E���f�B���O�X�t�B�A��`�悷��
void EnemyCrab::DrawBoundingSphere()
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

void EnemyCrab::ChangeState()
{
	//�G�̃X�e�[�g�Ǘ�
	//�v���C���[�ƓG�̈ʒu
	Vector3 Ppos = m_player->GetPos();
	Vector3 Cpos = m_position;
	//�v���C���[�ƓG�̋���
	float dx = Ppos.x - Cpos.x;
	float dy = Ppos.y - Cpos.y;
	float dz = Ppos.z - Cpos.z;
	float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
	//�G�̒ǐՔ͈�
	float SearchRange = 5.0f;
	//�X�e�[�g���p�g���[���ɂ���
	if (distance >= SearchRange)
	{
		m_state = Patrol;
	}
	//�X�e�[�g��ǐՂɂ���
	else if (distance <= SearchRange)
	{
		m_state = Chase;
	}
	//�X�e�[�g���U������
	if (Collision::GetInstance()->CheckHitAttackCrabsToPlayer())
	{
		m_state = Battle;
	}
	//�X�e�[�g�𓦑��ɂ���
	if (m_health <= 20.0f)
	{
		m_state = Escape;
		if (distance >= 15.0f)
		{
			m_state = Patrol;
		}
	}
	//�X�e�[�g�����S�ɂ���
	if (m_health <= 0.0f)
	{
		m_state = DEAD;
	}
	//�v���C���[����J�j�ւ̍U��
	if (Collision::GetInstance()->CheckHitAttackPlayerToCrab())
	{
		//�v���C���[�̏�Ԃ��U���Ȃ�G�Ƀ_���[�W������
		if (m_player->GetState() == PlayerBody::ATTACK)
		{
			TakeDamage(5.0f);
		}
	}
}

//�X�e�[�g�̍X�V
void EnemyCrab::UpdateState(float time)
{
	switch (m_state)
	{
		case NONE:
			break;
		case Patrol:
			m_patrol->Update();
			break;
		case Chase:
			m_chase->Update(m_player->GetPos());
			break;
		case Battle:
			m_attack->Update(time);
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
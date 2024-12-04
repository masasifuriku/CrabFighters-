//--------------------------------------------------------------------------------------
// File: EnemyCrab.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrab.h"
#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabPatrol.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabChase.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabAttack.h"
#include "Game/Scene/Play/Enemy/Crab/States/CrabEscape.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyCrab::EnemyCrab(PlayerBody* player)
	:
	m_model{},
	m_state{ DEAD }, 
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

void EnemyCrab::Initialize(
	IEnemy::EnemyState state,
	DirectX::SimpleMath::Vector3 position)
{
	// ���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("dice", L"Resources/Models/ogani-.cmo");
	//��Ԃ̐ݒ�
	m_state = state;
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
	m_attack = std::make_unique<CrabAttack>(this, m_player);
	m_escape = std::make_unique<CrabEscape>(this);

	/*std::vector<Vector3> vec;

	vec.emplace_back(Vector3::Zero);
	vec.emplace_back(Vector3::Zero);
	vec.emplace_back(Vector3::Zero);
	vec.emplace_back(Vector3::Zero);

	m_goals2.push_back(vec);
	m_goals2.push_back(vec);*/
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void EnemyCrab::Update(float timer)
{
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
	m_position = pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(m_size);
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * normal * translation;

	// ���f����`�悷��
	if (m_state != DEAD)
	{
		m_model->DrawModel("dice",m_world);
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

//�_���[�W���󂯂�
void EnemyCrab::TakeDamage(float damage)
{
	m_health -= damage;
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere EnemyCrab::GetBoundingSphere(Vector3 center)
{
	BoundingSphere sphere;
	sphere.Center = center;
	sphere.Radius = 0.6f;
	return sphere;
}

//�X�e�[�g�̍X�V
void EnemyCrab::UpdateState(float time)
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
//--------------------------------------------------------------------------------------
// File: EnemyCrab.cpp
//
// �G�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "EnemyCrab.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyCrab::EnemyCrab()
	:
	m_model{},
	m_state{ DEAD }, 
	m_position{},
	m_velocity{},
	m_rotate{},
	m_world{},
	m_angle{},
	m_currentGoalNo{},
	m_goals{},
	m_isInside{},
	m_health{},
	m_count{}
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
	m_model->AddModelData("dice", L"Resources/Models/dice.cmo");
	//��Ԃ̐ݒ�
	m_state = state;
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

	// �S�[���ԍ�
	m_currentGoalNo = 0;
	// �S�[���z����쐬����
	m_goals.emplace_back(Vector3{ -40.0f, -0.000008f, -40.0f });
	m_goals.emplace_back(Vector3{ 40.0f ,1.752317f ,40.0f });
	m_goals.emplace_back(Vector3{ -30.056952f, -0.902425f, -1.161875f });
	m_goals.emplace_back(Vector3{ -20.0f ,1.710116f, 30.0f });
	// �����t���O������������
	m_isInside = false;
	//HP
	m_health = 100.0f;
	m_count = 0.0f;

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
void EnemyCrab::Update(float timer,Vector3 Ppos)
{
	UpdateState(timer,Ppos);
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
	Matrix rotation, translation;
	rotation = Matrix::CreateRotationY(m_angle);
	translation = Matrix::CreateTranslation(m_position);
	m_world = rotation * normal * translation;

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
void EnemyCrab::UpdateState(float time, Vector3 player)
{
	switch (m_state)
	{
		case Patrol:
			CrabPatrol(time);
			break;
		case Chase:
			CrabChase(player);
			break;
		case Battle:
			CrabBattle();
			break;
		case Escape:
			CrabEscape(player);
			break;
		case DEAD:
			break;
		default:
			break;
	}
}

//�T���s��
void EnemyCrab::CrabPatrol(float timer)
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.35, Matrix::CreateRotationY(m_angle));

	// �S�[���֌������x�N�g��
	Vector3 toGoal = m_goals[m_currentGoalNo] - m_position;

	// �^�[�Q�b�g�Ƃ̋������߂����Ȃ����
	if (toGoal.LengthSquared() > SPEED * SPEED)
	{
		// �ړ�����
		m_position += (heading * SPEED);

		//�^�[�Q�b�g�̕����֏��X�ɉ�]����
		// �u�i�s�����x�N�g���v�Ɓu�^�[�Q�b�g�̕����v����cos�Ƃ��v�Z����
		float cosTheta = heading.Dot(toGoal) / (toGoal.Length() * heading.Length());

		// acos�̈����Ŏw��ł���͈͂́u-1�`1�v�Ȃ̂ŁA�l��␳����
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		// cos�Ƃ���Ƃ��v�Z����
		//** acos�̌��ʂ́u0�`�΁v
		float theta = std::acos(cosTheta);

		// �P�t���[���ł̉�]�p�𐧌��l�ȓ��ɕ␳����
		theta = std::min(0.1f, theta);

		if (heading.Cross(toGoal).y < 0.0f)
		{
			theta *= (-1.0f);
		}
		// �p�x���X�V����
		m_angle += theta;
		// �S�[���ɒB������A�S�[�������X�V����
		if (m_isInside == false && toGoal.Length() < 0.5f)
		{
			m_currentGoalNo++;
			m_currentGoalNo %= 4;
		}
	}
	//�K�`�����_��
	//m_count += timer;
	//if (m_count >= 2.0f)
	//{
	//	// �����_���ȕ����Ɉړ�
	//	float randomX = (rand() % 200 - 100);
	//	float randomZ = (rand() % 200 - 100);
	//	m_count = 0.0f;
	//	// �����_���ȕ����ɑ��x�x�N�g����ݒ�
	//	m_velocity = Vector3(randomX, 0.0f, randomZ);
	//}
	//// ���x�x�N�g���𐳋K�����A���x���悶��
	//m_velocity.Normalize();
	//// �|�W�V�������X�V
	//m_position += m_velocity * timer;
	//// �i�s�����Ɍ����ĉ�]
	////m_rotate = Quaternion::CreateFromRotationMatrix(Matrix::CreateLookAt(Vector3::Zero, m_velocity, Vector3::Up));
}
//�ǐՍs��
void EnemyCrab::CrabChase(Vector3 pos)
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_angle));
	// �v���C���[�֌������x�N�g��
	Vector3 toTarget = pos - m_position;

	// �v���C���[�Ƃ̋������߂����Ȃ����
	if (toTarget.LengthSquared() > SPEED * SPEED)
	{
		// �ړ�����
		m_position += (heading * SPEED);

		// �u�i�s�����x�N�g���v�Ɓu�^�[�Q�b�g�̕����v����cos�Ƃ��v�Z����
		float cosTheta = heading.Dot(toTarget) / (toTarget.Length() * heading.Length());

		// acos�̈����Ŏw��ł���͈͂́u-1�`1�v�Ȃ̂ŁA�l��␳����
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		// cos�Ƃ���Ƃ��v�Z����
		//** acos�̌��ʂ́u0�`�΁v
		float theta = std::acos(cosTheta);

		// �P�t���[���ł̉�]�p�𐧌��l�ȓ��ɕ␳����
		theta = std::min(0.1f, theta);

		// �E���ɍs�������ꍇ�͊p�x�̕�����t���ւ���
		if (heading.Cross(toTarget).y < 0.0f)
		{
			theta *= (-1.0f);
		}
	
		//�p�x���X�V����
		m_angle += theta;
	}
}
//�퓬�s��
void EnemyCrab::CrabBattle()
{

}
//�����s��
void EnemyCrab::CrabEscape(Vector3 pos)
{
	// �i�s�����x�N�g��
	Vector3 heading = Vector3::Transform(Vector3::Forward * 0.5, Matrix::CreateRotationY(m_angle));
	//�v���C���[���瓦����x�N�g��
	Vector3 awayFromPlayer = m_position - pos;

	// �^�[�Q�b�g���牓������x�N�g�����v�Z
	float cosTheta = heading.Dot(awayFromPlayer) / (awayFromPlayer.Length() * heading.Length());

	// acos�̈����Ŏw��ł���͈͂́u-1�`1�v�Ȃ̂ŁA�l��␳����
	cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

	// cos�Ƃ���Ƃ��v�Z����
	float theta = std::acos(cosTheta);

	// �P�t���[���ł̉�]�p�𐧌��l�ȓ��ɕ␳����
	theta = std::min(0.1f, theta);

	// ���E�ǂ���ɉ�]���邩�����߂�
	if (heading.Cross(awayFromPlayer).y < 0.0f)
	{
		theta *= (-1.0f);
	}

	// �p�x���X�V����
	m_angle += theta;

	// ��������
	m_position += heading * SPEED;
}

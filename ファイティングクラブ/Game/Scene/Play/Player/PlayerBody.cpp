//--------------------------------------------------------------------------------------
// File: PlayerBody.cpp
//
// �v���C���[�N���X
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "PlayerBody.h"
#include "Game/Screen.h"
#include "PlayerHand.h"
#include "Game/Scene/Play/Stage/Stage.h"

#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Input.h"

#include "Libraries/MyLib/UtilityMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerBody::PlayerBody(Stage* stage)
	:
	m_model{},
	m_hand{},
	m_stage{ stage },
	m_state{ NONE }, 
	m_position{},
	m_velocity{},
	m_rotate{},
	m_size{},
	m_health{},
	m_stamina{},
	m_attackCoolTime{},
	m_world{},
	m_torus{},
	m_torusPosition{},
	m_torusWorld{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerBody::~PlayerBody()
{
}

void PlayerBody::Initialize()
{
	// �v���C���[���f����ǂݍ���
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("CrabBody", L"Resources/Models/CrabBody.cmo");

	//�v���C���[�̘r
	m_hand = std::make_unique<PlayerHand>();
	m_hand->Initialize();

	//���W������������
	m_position = Vector3::Zero;
	//�s��
	m_world = Matrix::Identity;
	//���x
	m_velocity = Vector3::Zero;
	//��]
	m_rotate = Quaternion::Identity;
	//�T�C�Y
	m_size = 0.08f;
	//�̗�
	m_health = 100.0f;
	//�X�^�~�i
	m_stamina = 100.0f;
	//�U���N�[���^�C��
	m_attackCoolTime = 0.0f;

	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//�}�E�X����n
	m_torus = GeometricPrimitive::CreateTorus(context);
	//���W
	m_torusPosition = Vector3::Zero;
	//���[���h�s��
	m_torusWorld = Matrix::Identity;
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void PlayerBody::Update(float timer)
{
	//��Ԃ�����������
	m_state = NONE;
	//�v���C���[�̎�̍X�V
	m_hand->Update(timer);
	//�L�[�{�[�h����
	KeyBoardEvent();
	//�}�E�X�ړ�����
	MouseEvent();
	//�U���N�[���^�C������
	m_attackCoolTime -= timer;
	//���S����
	if (m_health <= 0.0f)
	{
		m_state = DEAD;
	}

	m_position = m_velocity;
	//�X�e�[�W�Ƃ̔���
	m_position = m_stage->NormalHitDetection(m_position).pos;
	m_rotateNormal = m_stage->NormalHitDetection(m_position).rotate;
}

/// <summary>
/// �`��֐�
/// </summary>
void PlayerBody::Render()
{
	Matrix view = Graphics::GetInstance()->GetViewMatrix();
	Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	Matrix size, rotation, translation;
	size = Matrix::CreateScale(m_size);
	rotation = Matrix::CreateFromQuaternion(m_rotate);
	translation = Matrix::CreateTranslation(m_position);
	m_world = size * rotation * m_rotateNormal * translation;

	if (m_state != DEAD)
	{
		// ���f����`�悷��
		m_model->DrawModel("CrabBody", m_world);
		m_hand->Render(m_world);

		m_torus->Draw(m_torusWorld, view, proj, Colors::DarkGreen);
	}
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere PlayerBody::GetBoundingSphere(Vector3 center)
{
	BoundingSphere sphere;
	sphere.Center = center;
	sphere.Radius = 0.75f;
	return sphere;
}

//�_���[�W���󂯂�
void PlayerBody::TakeDamage(float damage)
{
	m_health -= damage;
}

//�L�[�{�[�h����
void PlayerBody::KeyBoardEvent()
{
	//�L�[�X�e�[�g
	const auto& kbState = Input::GetInstance()->GetKeyState();

	//�ړ����Ƀ��t�g�V�t�g����������_�b�V��
	if (kbState.IsKeyDown(Keyboard::LeftShift))
	{
		//�X�^�~�i�������
		m_stamina--;
		//�X�^�~�i������Ƃ�
		if (m_stamina >= 0.0f)
		{
			m_velocity += Vector3::Transform(Vector3(0.1f, 0.0f, 0.0f), m_rotate);
		}
		//�X�^�~�i��0�ȉ��ɂȂ�Ȃ��悤�ɂ���
		else if (m_stamina <= 0.0f)
		{
			m_stamina = 0.0f;
		}
	}
	else
	{
		//�����Ă��Ȃ��Ƃ��X�^�~�i��
		m_stamina++;
		//�X�^�~�i��100�ȏ�ɂȂ�Ȃ��悤��
		if (m_stamina >= 100.0f)
		{
			m_stamina = 100.0f;
		}
	}

	//�X�y�[�X����������
	if (kbState.IsKeyDown(Keyboard::Space) && m_attackCoolTime <= 0.0f)
	{
		//�U������
		m_state = ATTACK;
		m_hand->AttackMotion();
		//�N�[���^�C����ݒ�
		m_attackCoolTime = 1.0f;
	}
}

//�}�E�X����
void PlayerBody::MouseEvent()
{
	//�}�E�X�X�e�[�g
	const auto& moState = Input::GetInstance()->GetMouseState();
	
	Matrix view = Graphics::GetInstance()->GetViewMatrix();
	Matrix proj = Graphics::GetInstance()->GetProjectionMatrix();

	//�N�I�[�^�j�I���ۑ��p
	Quaternion q;

	//�g�[���X�̍��W���w�肷��
	if (moState.leftButton)
	{
		//�}�E�X���C���擾����
		Ray mouseRay = mylib::GetMouseRay(moState.x, moState.y, Screen::WIDTH, Screen::HEIGHT, view, proj);

		//ZX�̖������ʂ𐶐�����
		Plane planeZX(0, 1, 0, 0);

		//Ray��Plane�̏Փ˔���
		float distance = 0.0f;
		bool isHit = mouseRay.Intersects(planeZX, distance);

		//Ray��Plane�̏Փˍ��W���g�[���X�̍��W�ɂ���
		if (isHit)
		{
			m_torusPosition = Vector3{ mouseRay.position + mouseRay.direction * distance };
		}
	}

	//�v���C���[�̈ړ��x�N�g��
	Vector3 velocity = Vector3::Transform(Vector3(0.07f, 0.0f, 0.0f), m_rotate);

	// �v���C���[�̐��ʃx�N�g��
	Vector3 forward = Vector3::Transform(Vector3(1.0f, 0.0f, 0.0f), m_rotate);
	forward.Normalize();

	//�v���C���[����g�[���X�֌������x�N�g��
	Vector3 toTorus = m_torusPosition - m_position;
	Vector3 v = toTorus;
	v.Normalize();

	//�v���C���[�̎���p
	constexpr float viewAngle = XMConvertToRadians(90.0f);

	//�v���C���[�ƃg�[���X�̋������߂����Ȃ����
	//������x�Ë�
	if (toTorus.LengthSquared() > 0.3f)
	{
		// forward��v�̊Ԃ̊p�x��cos�l�Ōv�Z
		float dot = forward.Dot(v);
		float angle = std::acos(dot);

		//�v���C���[���g�[���X�̕����ɉ�]����
		//�u�v���C���[�̈ړ��x�N�g���v�Ɓu�g�[���X�̕����v����cos��
		float cosTheta = velocity.Dot(toTorus) / (toTorus.Length() * velocity.Length());

		//acos�̈����Ŏw��ł���͈͂́u-1�`1�v�Ȃ̂ŁA�l��␳����
		cosTheta = std::max(-1.0f, std::min(cosTheta, 1.0f));

		//cos�Ƃ���Ƃ��v�Z����
		float theta = std::acos(cosTheta);

		//�P�t���[���ł̉�]�p�𐧌��l�ȓ��ɕ␳����
		theta = std::min(1.0f, theta);

		//�E���ɍs�������ꍇ�͊p�x�̕�����t���ւ���
		if (velocity.Cross(toTorus).y < 0.0f)
		{
			theta *= (-1.0f);
		}

		// �v���C���[�̊p�x���X�V����
		q *= Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(theta));

		//�N�I�[�^�j�I������]�Ɋ|����
		m_rotate = q * m_rotate;

		//�p�x�����킹�Ȃ�����ړ�
		m_velocity += Vector3::Transform(Vector3(0.03f, 0.0f, 0.0f), m_rotate);

		//�ړI�n�Ɋp�x����������ړ�
		if (angle < std::cos(viewAngle / 1.5f))
		{
			//�v���C���[���ړ�����
			m_velocity += velocity;
		}
	}

	//�g�[���X�̃��[���h�s����v�Z����
	m_torusPosition = m_stage->NormalHitDetection(m_torusPosition).pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(0.5f, 0.01f, 0.5f);
	rotation = m_stage->NormalHitDetection(m_torusPosition).rotate;
	translation = Matrix::CreateTranslation(m_torusPosition);
	m_torusWorld = size * rotation * translation;
}
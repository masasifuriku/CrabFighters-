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
#include "Framework/Collision.h"

#include "Libraries/MyLib/UtilityMath.h"
#include "Libraries/Microsoft/DebugDraw.h"


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
	m_BoundingSphere{},
	m_position{},
	m_velocity{},
	m_rotate{},
	m_size{},
	m_health{},
	m_stamina{},
	m_attackCoolTime{},
	m_world{},
	m_isHit{},
	m_torus{},
	m_torusPosition{},
	m_torusWorld{},
	m_attackCount{}
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
	m_size = 0.1f;
	//�̗�
	m_health = 100.0f;
	//�X�^�~�i
	m_stamina = 100.0f;
	//�U���N�[���^�C��
	m_attackCoolTime = 0.0f;
	//�Փ˔���
	m_isHit = false;

	auto context = Graphics::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//�}�E�X����n
	m_torus = GeometricPrimitive::CreateTorus(context);
	//���W
	m_torusPosition = Vector3::Zero;
	//���[���h�s��
	m_torusWorld = Matrix::Identity;

	//�U���J�E���g
	m_attackCount = 0;

	// �o�E���f�B���O�X�t�B�A�𐶐�����
	m_BoundingSphere = CreateBoundingSphere(m_size * 10);

	Collision::GetInstance()->SetPlayer(this);
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="timer">StepTimer���󂯎��</param>
void PlayerBody::Update(float timer)
{
	//�L�[�{�[�h����
	KeyBoardEvent();
	//�}�E�X�ړ�����
	MouseEvent();
	//�X�e�[�g���U���̎�
	if (m_state == ATTACK)
	{
		m_hand->AttackMotion();
		m_attackCount++;
		if (m_attackCount >= 8)
		{
			//�X�e�[�g���A�C�h�����O�ɕύX
			m_state = IDLING;
			m_attackCount = 0;
		}
	}
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

	//�o�E���f�B���O�X�t�B�A�̒��S�_��ݒ�
	m_BoundingSphere.Center = m_position;
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
		DrawBoundingSphere();

		m_torus->Draw(m_torusWorld, view, proj, Colors::DarkGreen);
	}
}

//�L�[�{�[�h����
void PlayerBody::KeyBoardEvent()
{
	//�L�[�X�e�[�g���擾
	const auto& kbState = Input::GetInstance()->GetKeyState();

	//�ړ����Ƀ��t�g�V�t�g����������_�b�V��
	if (kbState.IsKeyDown(Keyboard::LeftShift))
	{
		//�X�^�~�i�������
		m_stamina--;
		//�X�^�~�i������Ƃ�
		if (m_stamina >= 0.0f)
		{
			//�X�e�[�g���_�b�V���ɕύX
			m_state = DASH;
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
		//�X�e�[�g���U���ɂ���
		m_state = ATTACK;
		//�N�[���^�C����ݒ�
		m_attackCoolTime = 0.5f;
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
	Quaternion q = Quaternion::Identity;
	Vector3 velocity = Vector3::Zero;

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

	//�v���C���[�̐��ʃx�N�g��
	Vector3 forward = Vector3::Transform(Vector3(1.0f, 0.0f, 0.0f), m_rotate);
	forward.Normalize();
	//�v���C���[����g�[���X�֌������x�N�g��
	Vector3 toTorus = m_torusPosition - m_position;
	toTorus.Normalize();
	//�h�b�g�ς̌v�Z
	float dot = (forward.x * toTorus.x) + 
				(forward.y * toTorus.y) + 
				(forward.z * toTorus.z);

	//�v���C���[�ƃg�[���X�̋������߂����Ȃ����
	if (toTorus.LengthSquared() > 0.1f)
	{
		//XZ���ʏ�ł̕��������߂�
		Vector3 toTorusXZ = Vector3(toTorus.x, 0.0f, toTorus.z);
		Vector3 forwardXZ = Vector3(forward.x, 0.0f, forward.z);
		toTorusXZ.Normalize();
		forwardXZ.Normalize();

		//atan2��p���Č��݂̕����ƃg�[���X�����̊p�x���v�Z
		float angle = std::atan2(toTorusXZ.z, toTorusXZ.x) - std::atan2(forwardXZ.z, forwardXZ.x);

		//-�΁`�΂͈̔͂ɐ��K��
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}
		else if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		//1�t���[���ł̉�]�p�𐧌�
		constexpr float maxRotationPerFrame = XMConvertToRadians(1.0f); 
		angle = Clamp(angle, -maxRotationPerFrame, maxRotationPerFrame);

		Vector3 velocity;

		//�v���C���[�̉E
		if (dot > 0.0f) {
			//�v���C���[�̊p�x���X�V����
			q *= Quaternion::CreateFromAxisAngle(Vector3::UnitY, -angle);
			//�N�I�[�^�j�I������]�Ɋ|����
			m_rotate = q * m_rotate;
			//�X�e�[�g���A�C�h�����O�̎�
			if (m_state ==IDLING)
			{
				//���x��������
				velocity = Vector3::Transform(Vector3(-0.07f, 0.0f, 0.0f), m_rotate);
			}
			//�X�e�[�g���_�b�V���̎�
			if (m_state == DASH)
			{
				//���x��������
				velocity = Vector3::Transform(Vector3(-0.12f, 0.0f, 0.0f), m_rotate);

			}
			//�v���C���[���ړ�����
			m_velocity -= velocity;
		}
		//�v���C���[�̍�
		else if (dot < 0.0f) {
			//�v���C���[�̊p�x���X�V����
			q *= Quaternion::CreateFromAxisAngle(Vector3::UnitY, angle);
			//�N�I�[�^�j�I������]�Ɋ|����
			m_rotate = q * m_rotate;
			//�X�e�[�g���A�C�h�����O�̎�
			if (m_state == IDLING)
			{
				//���x��������
				velocity = Vector3::Transform(Vector3(0.07f, 0.0f, 0.0f), m_rotate);
			}
			//�X�e�[�g���_�b�V���̎�
			if (m_state == DASH)
			{
				//���x��������
				velocity = Vector3::Transform(Vector3(0.12f, 0.0f, 0.0f), m_rotate);
			}
			//�v���C���[���ړ�����
			m_velocity -= velocity;
		}
	}
	
	//�g�[���X�̃��[���h�s����v�Z����
	auto hitDetectionResult = m_stage->NormalHitDetection(m_torusPosition);
	m_torusPosition = hitDetectionResult.pos;
	Matrix size, rotation, translation;
	size = Matrix::CreateScale(0.5f, 0.01f, 0.5f);
	rotation = hitDetectionResult.rotate;
	translation = Matrix::CreateTranslation(m_torusPosition);
	m_torusWorld = size * rotation * translation;
}

//�o�E���f�B���O�X�t�B�A����
DirectX::BoundingSphere PlayerBody::CreateBoundingSphere(const float& radius)
{
	//�o�E���f�B���O�X�t�B�A��錾����
	DirectX::BoundingSphere BoundingSphere;
	//�o�E���f�B���O�X�t�B�A�̔��a��ݒ肷��
	BoundingSphere.Radius = radius;
	//�o�E���f�B���O�X�t�B�A��Ԃ�
	return BoundingSphere;
}

//�o�E���f�B���O�X�t�B�A��`�悷��
void PlayerBody::DrawBoundingSphere()
{
	//����F��ݒ肷��
	DirectX::XMVECTOR color = DirectX::Colors::Yellow;
	auto batch = Graphics::GetInstance();
	//�v���~�e�B�u�`����J�n����
	batch->DrawPrimitiveBegin(batch->GetViewMatrix(), batch->GetProjectionMatrix());
	//�C���̋��E����`�悷��
	DX::Draw(batch->GetPrimitiveBatch(), m_BoundingSphere, color);
	//�v���~�e�B�u�`����I������
	batch->DrawPrimitiveEnd();
}

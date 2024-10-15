/*
	@file	TPS_Camera.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
mylib::TPS_Camera::TPS_Camera(const DirectX::SimpleMath::Vector3& target)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{ target },
	m_up{ DirectX::SimpleMath::Vector3::UnitY }
{
	CalculateEyePosition(DirectX::SimpleMath::Matrix::Identity);
	CalculateViewMatrix();
	CalculateProjectionMatrix();
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void mylib::TPS_Camera::Update(
	const DirectX::SimpleMath::Vector3& newTarget,
	const DirectX::SimpleMath::Matrix& rotate
)
{
	// target�̈ʒu���X�V����
	m_target =newTarget;

	// �J�������W���v�Z����
	CalculateEyePosition(rotate);

	// �r���[�s����X�V����
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateProjectionMatrix()
{
	// �E�B���h�E�T�C�Y
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

//-------------------------------------------------------------------
// �J�������W���v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate)
{
	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;

	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	forward = DirectX::SimpleMath::Vector3::Transform(forward, rotate);

	// �J�������W���v�Z����
	m_eye = m_target + forward;
}

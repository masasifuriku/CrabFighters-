/*
	@file	UtilityMath.h
	@brief	�֗��⏕�֐��̏W�܂�
*/
#pragma once
#include <SimpleMath.h>
#include <VertexTypes.h>

namespace mylib
{
	//-----------------------------------------------------
	// �r���[�|�[�g�ϊ��s����擾����
	//-----------------------------------------------------
	inline DirectX::SimpleMath::Matrix GetViewportMatrix(
		int screenWidth,
		int screenHeight
	)
	{
		// �r���[�|�[�g�ϊ��s����v�Z����
		DirectX::SimpleMath::Matrix viewport = DirectX::SimpleMath::Matrix::Identity;
		viewport._11 =  screenWidth  / 2.0f;
		viewport._22 = -screenHeight / 2.0f;
		viewport._41 =  screenWidth  / 2.0f;
		viewport._42 =  screenHeight / 2.0f;

		return viewport;
	}

	//-----------------------------------------------------
	// �ϊ��s����擾����F�X�N���[�����W->���[���h���W
	//-----------------------------------------------------
	inline DirectX::SimpleMath::Matrix GetMatrix_ScreenToWorld(
		int screenWidth,
		int screenHeight,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	)
	{
		// �r���[�|�[�g�ϊ��s����擾����
		DirectX::SimpleMath::Matrix viewport = mylib::GetViewportMatrix(screenWidth, screenHeight);
		
		// �u�r���[���ˉe���r���[�|�[�g�v�̋t�ϊ��s����v�Z����
		DirectX::SimpleMath::Matrix matrix = view * projection * viewport;
		matrix = matrix.Invert();

		return matrix;
	}

	//-----------------------------------------------------
	// �}�E�X���C���擾����
	//-----------------------------------------------------
	inline DirectX::SimpleMath::Ray GetMouseRay(
		int mouseX,
		int mouseY,
		int screenWidth,
		int screenHeight,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	)
	{
		// �u�r���[���ˉe���r���[�|�[�g�v�̋t�ϊ��s����v�Z����
		DirectX::SimpleMath::Matrix matrix = mylib::GetMatrix_ScreenToWorld(
			screenWidth, screenHeight, view, projection
		);

		// near�v���[���̃x�N�g�������
		DirectX::SimpleMath::Vector3 nearPointWorld = DirectX::SimpleMath::Vector3(
			static_cast<float>(mouseX),
			static_cast<float>(mouseY),
			0.0f
		);
		// far�v���[���̃x�N�g�������
		DirectX::SimpleMath::Vector3 farPointWorld  = DirectX::SimpleMath::Vector3(
			static_cast<float>(mouseX),
			static_cast<float>(mouseY),
			1.0f
		);

		// near/far�����[���h���W�ɕϊ�����
		nearPointWorld = DirectX::SimpleMath::Vector3::Transform(nearPointWorld, matrix);
		farPointWorld  = DirectX::SimpleMath::Vector3::Transform(farPointWorld,  matrix);

		// �}�E�X���C�̎n�_�Ɛi�s�����x�N�g�����v�Z����
		const DirectX::SimpleMath::Vector3 rayOrigin = nearPointWorld;
		const DirectX::SimpleMath::Vector3 rayDirection = farPointWorld - nearPointWorld;

		// �}�E�X���C���쐬����
		DirectX::SimpleMath::Ray ray(rayOrigin, rayDirection);

		return ray;
	}
}
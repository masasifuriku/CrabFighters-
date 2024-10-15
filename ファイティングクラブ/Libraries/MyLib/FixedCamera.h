/*
	@file	FixedCamera.h
	@brief	固定カメラクラス
*/
#pragma once

namespace mylib
{
	class FixedCamera
	{
	private:
		// 画角
		const float FOV = DirectX::XMConvertToRadians(60.0f);
		
		// 近い投影面
		const float NEAR_PLANE = 1.0f;
		
		// 遠い投影面
		const float FAR_PLANE  = 100.0f;

		// ビュー行列
		DirectX::SimpleMath::Matrix m_view;

		// プロジェクション行列
		DirectX::SimpleMath::Matrix m_projection;

		// カメラ座標
		DirectX::SimpleMath::Vector3 m_eye;

		// 注視点
		DirectX::SimpleMath::Vector3 m_target;

		// カメラの頭の方向
		DirectX::SimpleMath::Vector3 m_up;


	public:
		// コンストラクタ
		FixedCamera(
			const DirectX::SimpleMath::Vector3& eye,
			const DirectX::SimpleMath::Vector3& target,
			const DirectX::SimpleMath::Vector3& up = DirectX::SimpleMath::Vector3::UnitY
		);

		// デストラクタ
		~FixedCamera() = default;

		// getter
		const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_view; }

		const DirectX::SimpleMath::Matrix& GetProjectionMatrix() const { return m_projection; }

		const DirectX::SimpleMath::Vector3& GetEyePosition() const { return m_eye; }

		const DirectX::SimpleMath::Vector3& GetTargetPosition() const { return m_target; }

		const DirectX::SimpleMath::Vector3& GetUpVector() const { return m_up; }


	private:
		// ビュー行列を計算する
		void CalculateViewMatrix();

		// プロジェクション行列を計算する
		void CalculateProjectionMatrix();
	};
}

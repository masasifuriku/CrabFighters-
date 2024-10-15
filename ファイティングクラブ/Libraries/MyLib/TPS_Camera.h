/*
	@file	TPS_Camera.h
	@brief	TPSカメラクラス
*/
#pragma once

namespace mylib
{
	class TPS_Camera
	{
	private:
		// ターゲットからのデフォルト距離
		const float CAMERA_DISTANCE = 10.0f;
		const float CAMERA_HIGHT = 7.5f;

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
		TPS_Camera(const DirectX::SimpleMath::Vector3& target = DirectX::SimpleMath::Vector3::Zero);

		// デストラクタ
		~TPS_Camera() = default;

		// 更新処理
		void Update(
			const DirectX::SimpleMath::Vector3& newTarget,
			const DirectX::SimpleMath::Matrix& rotate
		);


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

		// カメラ座標を計算する
		void CalculateEyePosition(const DirectX::SimpleMath::Matrix& rotate);
	};
}

/*
	@file	SkyDome.cpp
	@brief	天球クラス
*/
#include "pch.h"
#include "SkyDome.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
SkyDome::SkyDome()
	:
	m_projection{},
	m_model{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
SkyDome::~SkyDome()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void SkyDome::Initialize()
{
	RECT rect = Graphics::GetInstance()->GetDeviceResources()->GetOutputSize();
	// 射影行列を作成する
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);

	// モデルを読み込む
		// プレイヤーモデルを読み込む
	m_model = std::make_unique<Ede::ModelManager>();
	m_model->AddModelData("Dome", L"Resources/Models/seaDome.cmo");
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void SkyDome::Render()
{
	// ワールド行列を更新する
	Matrix  size, world;
	size = Matrix::CreateScale(1.1f);
	world = size;


	// モデルを描画する
	m_model->DrawModel("Dome", world);
}


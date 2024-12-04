/*
	@file	SkyDome.h
	@brief	天球クラス
*/
#pragma once
#include "Libraries/EdeLib/ModelManager.h"

// 一般的なシーンクラス
class SkyDome
{
private:
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;

public:
	SkyDome();
	~SkyDome();

	void Initialize();
	void Render();
};

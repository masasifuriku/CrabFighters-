//--------------------------------------------------------------------------------------
// File: Enemy.h
//
// 敵クラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"



class Enemy
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Render();
public:
};

//--------------------------------------------------------------------------------------
// File: Player.h
//
// プレイヤークラス
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"



class Player
{
private:
	// モデル
	std::unique_ptr<Ede::ModelManager> m_model;
public:
	Player();
	~Player();

	void Initialize();
	void Update();
	void Render();
public:

private:
};

//--------------------------------------------------------------------------------------
// File: Player.h
//
// �v���C���[�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"



class Player
{
private:
	// ���f��
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

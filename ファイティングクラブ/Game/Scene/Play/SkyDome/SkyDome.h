/*
	@file	SkyDome.h
	@brief	�V���N���X
*/
#pragma once
#include "Libraries/EdeLib/ModelManager.h"

// ��ʓI�ȃV�[���N���X
class SkyDome
{
private:
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;

public:
	SkyDome();
	~SkyDome();

	void Initialize();
	void Render();
};

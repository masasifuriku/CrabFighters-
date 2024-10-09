/*
	@file	Scene.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once
#include <unordered_map>

// �O���錾
class CommonResources;

// ��ʓI�ȃV�[���N���X
class Scene
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};

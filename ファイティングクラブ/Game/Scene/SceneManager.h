/*
	@file	SceneManager.h
	@brief	�V�[���}�l�[�W���N���X
*/
#pragma once
#include "Interface/IScene.h"

class SceneManager
{
private:
	std::unique_ptr<IScene> m_currentScene;


public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Update(float elapsedTime);
	void Render();
	void Finalize();


private:
	void ChangeScene(IScene::SceneID sceneID);
	void CreateScene(IScene::SceneID sceneID);
	void DeleteScene();
};

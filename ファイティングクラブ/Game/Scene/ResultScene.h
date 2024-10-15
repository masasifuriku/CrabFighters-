/*
	@file	ResultScene.h
	@brief	���U���g�V�[���N���X
*/
#pragma once
#include "Interface/IScene.h"
#include "Libraries/EdeLib/ModelManager.h"

namespace mylib
{
	class GridFloor;
}


class ResultScene final :
    public IScene
{
private:
	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	
public:
	ResultScene();
	~ResultScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};

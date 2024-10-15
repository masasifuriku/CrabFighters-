/*
	@file	ResultScene.h
	@brief	リザルトシーンクラス
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
	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	// モデル
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

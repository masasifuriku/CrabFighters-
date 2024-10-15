/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Interface/IScene.h"

// 前方宣言
class Player;
class Enemy;

namespace mylib
{
	class TPS_Camera;
	class GridFloor;
}


class PlayScene final :
    public IScene
{
private:
	// デバッグカメラ
	std::unique_ptr<mylib::TPS_Camera> m_camera;

	// 格子床
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	//プレイヤー
	std::unique_ptr<Player> m_player;
	//敵
	std::unique_ptr<Enemy> m_enemy;
	
	
public:
	PlayScene();
	~PlayScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};

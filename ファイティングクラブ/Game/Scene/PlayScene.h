/*
	@file	PlayScene.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Interface/IScene.h"

// 前方宣言
class PlayerBody;
class EnemyManager;
class Stage;

namespace mylib
{
	class TPS_Camera;
}


class PlayScene final :
    public IScene
{
private:
	// TPSカメラ
	std::unique_ptr<mylib::TPS_Camera> m_camera;

	// シーンチェンジフラグ
	bool m_isChangeScene;

	//プレイヤー
	std::unique_ptr<PlayerBody> m_player;
	//敵
	std::unique_ptr<EnemyManager> m_enemy;
	//ステージ
	std::unique_ptr<Stage> m_stage;

	//スプライトバッチ
	DirectX::SpriteBatch* m_Batch;
	//スプライトフォント
	DirectX::SpriteFont* m_Font;
	
	
public:
	PlayScene();
	~PlayScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;

private:
	//カニの更新
	void UpdateCrabs();
	//サメの更新
	void UpdateSharks();
	//鳥の更新
	void UpdateBirds();
	//ボスの更新
	void UpdateBoss();

	//デバック情報
	void DrawDebug();
};

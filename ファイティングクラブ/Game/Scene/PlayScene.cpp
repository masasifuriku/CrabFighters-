/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "Libraries/MyLib/TPS_Camera.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/EnemyManager.h"
#include "Game/Scene/Play/Stage/Stage.h"
#include "Game/Scene/Play/SkyDome/SkyDome.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_camera{},
	m_isChangeScene{},
	m_player{},
	m_enemy{},
	m_stage{},
	m_dome{},
	m_Batch{},
	m_Font{},
	m_collision{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayScene::Initialize()
{
	// カメラを作成する
	m_camera = std::make_unique<mylib::TPS_Camera>();

	//ステージの生成
	m_stage = std::make_unique<Stage>();
	m_stage->Initialize();
	//プレイヤーの生成
	m_player = std::make_unique<PlayerBody>(m_stage.get());
	m_player->Initialize();
	//敵の生成
	m_enemy = std::make_unique<EnemyManager>(m_stage.get(), m_player.get());
	m_enemy->Initialize();
	//天球の生成
	m_dome = std::make_unique<SkyDome>();
	m_dome->Initialize();

	//バッチとフォントを持ってくる
	m_Batch = Graphics::GetInstance()->GetSpriteBatch();
	m_Font = Graphics::GetInstance()->GetFont();

	// シーン変更フラグを初期化する
	m_isChangeScene = false;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	//カメラの更新
	m_camera->Update(m_player->GetPos(), Matrix::Identity);

	//プレイヤーの更新
	m_player->Update(elapsedTime);

	//敵の更新
	m_enemy->Update(elapsedTime);

	//ビューと射影行列の生成
	Graphics::GetInstance()->SetProjectionMatrix(m_camera->GetProjectionMatrix());
	Graphics::GetInstance()->SetViewMatrix(m_camera->GetViewMatrix());

	// 敵の出現ファイルが終わって敵を全部倒したらリザルトに移行
	if (m_enemy->GetCSV() == true && m_enemy->GetActiveEnemyCount() == 0 ||
		m_player->GetHP() <= 0.0f)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	//プレイヤーの描画
	m_player->Render();
	//敵の描画
	m_enemy->Render();
	//ステージの描画
	m_stage->Render();
	//天球の描画
	m_dome->Render();
	//デバッグ表示
	DrawDebug();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::RESULT;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}

//デバック情報をまとめておく
void PlayScene::DrawDebug()
{
	//始める
	m_Batch->Begin();
	//// デバッグ情報を「DebugString」で表示する
	m_Font->DrawString(m_Batch, L"Play Scene", Vector2(10, 10), Colors::Black);
	//生存中のカニの情報
	float yPosition = 30.0f;
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		std::wstring crabHP = L"Crab:" + std::to_wstring(crab->GetHP());
		std::wstring crabState = L" State: " +std::to_wstring(crab->GetState());
		std::wstring CisAttacking = L" CAttack: " + BoolToString(Collision::GetInstance()->CheckHitAttackCrabsToPlayer());
		std::wstring PisAttacking = L" PAttack: " + BoolToString(Collision::GetInstance()->CheckHitAttackPlayerToCrab());
		m_Font->DrawString(m_Batch, crabHP.c_str(), Vector2(10, yPosition), Colors::Black);
		m_Font->DrawString(m_Batch, crabState.c_str(), Vector2(180, yPosition), Colors::Black);
		m_Font->DrawString(m_Batch, CisAttacking.c_str(), Vector2(260, yPosition), Colors::Black);
		m_Font->DrawString(m_Batch, PisAttacking.c_str(), Vector2(410, yPosition), Colors::Black);
		yPosition += 20.0f; 
	}
	////ボスの情報
	//auto& boss = m_enemy->GetBoss();
	//std::wstring bossHP = L"Boss:" + std::to_wstring(boss->GetHP());
	//m_Font->DrawString(m_Batch, bossHP.c_str(), Vector2(10, 90), Colors::Aqua);
	//生存中の敵の総数
	std::wstring ActiveEnemy = L"ActiveEnemy:" + std::to_wstring(m_enemy->GetActiveEnemyCount());
	m_Font->DrawString(m_Batch, ActiveEnemy.c_str(), Vector2(10, 110), Colors::Black);
	//プレイヤーのスタミナ
	std::wstring PSta = L"Player/Stamina:" + std::to_wstring(m_player->GetStamina());
	m_Font->DrawString(m_Batch, PSta.c_str(), Vector2(10, 130), Colors::Black);
	//プレイヤーの体力
	std::wstring Php = L"Player/HP:" + std::to_wstring(m_player->GetHP());
	m_Font->DrawString(m_Batch, Php.c_str(), Vector2(10, 150), Colors::Black);
	//終わり
	m_Batch->End();
}
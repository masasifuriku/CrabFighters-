/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "FrameWork/DeviceResources.h"
#include "FrameWork/Graphics.h"
#include "FrameWork/Input.h"
#include "Libraries/MyLib/TPS_Camera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Scene/Play/Player/PlayerBody.h"
#include "Game/Scene/Play/Enemy/EnemyManager.h"
#include "Game/Scene/Play/Stage/Stage.h"

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
	m_stage{}
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
	m_enemy = std::make_unique<EnemyManager>(m_stage.get());
	m_enemy->Initialize();

	// シーン変更フラグを初期化する
	m_isChangeScene = false;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//カメラの更新
	m_camera->Update(m_player->GetPos(), Matrix::Identity);

	//プレイヤーの更新
	m_player->Update(elapsedTime);

	//敵の更新
	m_enemy->Update(elapsedTime, IEnemy::Patrol, m_player->GetPos());

	UpdateCrabs();
	UpdateSharks();
	UpdateBirds();
	UpdateBoss();

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

	DrawDebug();
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
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

void PlayScene::UpdateCrabs()
{
	//プレイヤーと敵(カニ)の判定など
	for (auto& crab : m_enemy->GetActiveCrabs())
	{
		//敵のステート管理
		//プレイヤーと敵の位置
		Vector3 Ppos = m_player->GetPos();
		Vector3 Cpos = crab->GetPos();
		//プレイヤーと敵の距離
		float dx = Ppos.x - Cpos.x;
		float dy = Ppos.y - Cpos.y;
		float dz = Ppos.z - Cpos.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		//敵の追跡範囲
		float SearchRande = 5.0f;
		//ステートをパトロールにする
		if (distance >= SearchRande)
		{
			crab->SetEnemyState(IEnemy::EnemyState::Patrol);
		}
		//ステートを追跡にする
		else if (distance <= SearchRande)
		{
			crab->SetEnemyState(IEnemy::EnemyState::Chase);
		}
		//ステートを逃走にする
		if (crab->GetHP() <= 20.0f)
		{
			crab->SetEnemyState(IEnemy::EnemyState::Escape);
			if (distance >= 15.0f)
			{
				crab->SetEnemyState(IEnemy::EnemyState::Patrol);
			}
		}
		//ステートを死亡にする
		if (crab->GetHP() <= 0.0f)
		{
			crab->SetEnemyState(IEnemy::EnemyState::DEAD);
		}
		//プレイヤーからカニへの攻撃
		if (m_player->GetBoundingSphere(
			m_player->GetPos()).
			Intersects(
				crab->GetBoundingSphere(crab->GetPos())))
		{
			//プレイヤーの状態が攻撃なら敵にダメージが入る
			if (m_player->GetState() == PlayerBody::ATTACK)
			{
				crab->TakeDamage(30.0f);
			}
		}
	}
}

void PlayScene::UpdateSharks()
{
	//プレイヤーと敵(サメ)の当たり判定
	for (auto& shark : m_enemy->GetActiveSharks())
	{
		//敵のステート管理
		//プレイヤーと敵の位置
		Vector3 Ppos = m_player->GetPos();
		Vector3 Spos = shark->GetPos();
		//プレイヤーと敵の距離
		float dx = Ppos.x - Spos.x;
		float dy = Ppos.y - Spos.y;
		float dz = Ppos.z - Spos.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		//敵の追跡範囲
		float SearchRande = 5.0f;
		//ステートをパトロールにする
		if (distance >= SearchRande)
		{
			shark->SetEnemyState(IEnemy::EnemyState::Patrol);
		}
		//ステートを追跡にする
		else if (distance <= SearchRande)
		{
			shark->SetEnemyState(IEnemy::EnemyState::Chase);
		}
		//ステートを逃走にする
		if (shark->GetHP() <= 20.0f)
		{
			shark->SetEnemyState(IEnemy::EnemyState::Escape);
		}
		//ステートを死亡にする
		if (shark->GetHP() <= 0.0f)
		{
			shark->SetEnemyState(IEnemy::EnemyState::DEAD);
		}
		//プレイヤーからサメへの攻撃
		if (m_player->GetBoundingSphere(
			m_player->GetPos()).
			Intersects(
				shark->GetBoundingSphere(shark->GetPos())))
		{
			//プレイヤーの状態が攻撃なら敵にダメージが入る
			if (m_player->GetState() == PlayerBody::ATTACK)
			{
				shark->TakeDamage(30.0f);
			}
		}
	}
}

void PlayScene::UpdateBirds()
{
	//プレイヤーと敵(鳥)の当たり判定
	for (auto& bird : m_enemy->GetActiveBirds())
	{
		//敵のステート管理
		//プレイヤーと敵の位置
		Vector3 Ppos = m_player->GetPos();
		Vector3 Bpos = bird->GetPos();
		//プレイヤーと敵の距離
		float dx = Ppos.x - Bpos.x;
		float dy = Ppos.y - Bpos.y;
		float dz = Ppos.z - Bpos.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		//敵の追跡範囲
		float SearchRande = 5.0f;
		//ステートをパトロールにする
		if (distance >= SearchRande)
		{
			bird->SetEnemyState(IEnemy::EnemyState::Patrol);
		}
		//ステートを追跡にする
		else if (distance <= SearchRande)
		{
			bird->SetEnemyState(IEnemy::EnemyState::Chase);
		}
		//ステートを逃走にする
		if (bird->GetHP() <= 20.0f)
		{
			bird->SetEnemyState(IEnemy::EnemyState::Escape);
		}
		//ステートを死亡にする
		if (bird->GetHP() <= 0.0f)
		{
			bird->SetEnemyState(IEnemy::EnemyState::DEAD);
		}
		//プレイヤーから鳥への攻撃
		if (m_player->GetBoundingSphere(m_player->GetPos()).
			Intersects(
				bird->GetBoundingSphere(bird->GetPos())))
		{
			//プレイヤーの状態が攻撃なら敵にダメージが入る
			if (m_player->GetState() == PlayerBody::ATTACK)
			{
				bird->TakeDamage(30.0f);
			}
		}
	}
}

void PlayScene::UpdateBoss()
{
	//ボスを入れておく
	auto& boss = m_enemy->GetBoss();

	//ボスのステート管理
	//プレイヤーとボスの位置
	Vector3 Ppos = m_player->GetPos();
	Vector3 Bpos = boss->GetPos();
	//プレイヤーとボスの距離
	float dx = Ppos.x - Bpos.x;
	float dy = Ppos.y - Bpos.y;
	float dz = Ppos.z - Bpos.z;
	float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
	//ボスの追跡範囲
	float SearchRande = 5.0f;
	//ステートをパトロールにする
	if (distance >= SearchRande)
	{
		boss->SetEnemyState(IEnemy::EnemyState::Patrol);
	}
	//ステートを追跡にする
	else if (distance <= SearchRande)
	{
		boss->SetEnemyState(IEnemy::EnemyState::Chase);
	}
	//ステートを逃走にする
	if (boss->GetHP() <= 20.0f)
	{
		boss->SetEnemyState(IEnemy::EnemyState::Escape);
	}
	//ステートを死亡にする
	if (boss->GetHP() <= 0.0f)
	{
		boss->SetEnemyState(IEnemy::EnemyState::DEAD);
	}
	//プレイヤーから鳥への攻撃
	if (m_player->GetBoundingSphere(m_player->GetPos()).
		Intersects(
			boss->GetBoundingSphere(boss->GetPos())))
	{
		//プレイヤーの状態が攻撃なら敵にダメージが入る
		if (m_player->GetState() == PlayerBody::ATTACK)
		{
			boss->TakeDamage(30.0f);
		}
	}
}

//デバック情報をまとめておく
void PlayScene::DrawDebug()
{
	//// デバッグ情報を「DebugString」で表示する
	//auto debugString = m_commonResources->GetDebugString();
	//debugString->AddString("Play Scene");
	////生存中のカニの情報
	//for (auto& crab : m_enemy->GetActiveCrabs())
	//{
	//	debugString->AddString("Crab:%f", crab->GetHP());
	//}
	////生存中のサメの情報
	//for (auto& shark : m_enemy->GetActiveSharks())
	//{
	//	debugString->AddString("Shark:%f", shark->GetHP());
	//}	
	////生存中の鳥の情報
	//for (auto& bird : m_enemy->GetActiveBirds())
	//{
	//	debugString->AddString("Bird:%f", bird->GetHP());
	//}
	////ボスの情報
	//auto& boss = m_enemy->GetBoss();
	//debugString->AddString("Boss:%f", boss->GetHP());
	////生存中の敵の総数
	//debugString->AddString("ActiveEnemy:%d", m_enemy->GetActiveEnemyCount());
	////プレイヤーのスタミナ
	//debugString->AddString("Player/Stamina:%f", m_player->GetStamina());
}

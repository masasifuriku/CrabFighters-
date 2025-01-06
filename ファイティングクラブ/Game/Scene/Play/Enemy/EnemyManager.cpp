/**
 * @file   EnemyManager.cpp
 *
 * @brief  敵に関するソースファイル
 *
 * @author kaede
 *
 * @date   2023/11/08
 */

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyManager.h"
#include<fstream>
#include<sstream>
#include "Game/Scene/Play/Stage/Stage.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// メンバ関数の定義 ===========================================================
/**
 * @brief デフォルトコンストラクタ
 *
 * @param[in] なし
 */
EnemyManager::EnemyManager(Stage* stage,PlayerBody* player)
	:
	m_crabs{},
	m_sharks{},
	m_birds{},
	m_boss{},
	m_activeEnemyCount{},
	m_enemyDataList{},
	m_frameCounter{},
	m_nowListNumber{},
	m_activeCrabs{},
	m_activeSharks{},
	m_activeBirds{},
	m_CSVFlag{},
	m_stage{ stage },
	m_player{ player }
{
}



/**
 * @brief デストラクタ
 */
EnemyManager::~EnemyManager()
{

}



/**
 * @brief 初期化処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Initialize()
{
	// 敵を生成する
	for (int i = 0; i < MAX_ENEMY_COUNT; i++)
	{
		m_crabs[i] = std::make_unique<EnemyCrab>(m_player);
		m_sharks[i] = std::make_unique<EnemyShark>(m_player);
		m_birds[i] = std::make_unique<EnemyBird>();
	}
	//ボスを生成する
	m_boss = std::make_unique<EnemyBoss>(m_player);
	//生存中の敵の数を初期化する
	m_activeEnemyCount = 0;

	//敵の出現リストをロードする
	LoadCSV("Resources\\CSV\\enemy.csv");
	m_CSVFlag = false;
}




/**
 * @brief 更新処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Update(float timer, IEnemy::EnemyState state)
{
	// フレームをカウントする
	m_frameCounter++;

	// 敵をスポーンする
	Spawn(state);

	//配列をクリアする
	m_activeEnemyCount = 0;
	m_activeCrabs.clear();
	m_activeSharks.clear();
	m_activeBirds.clear();

	//カニの更新
	for (auto& crab : m_crabs)
	{
		assert(crab);

		// アクティブなカニだけ更新する
		if (!crab->IsActive())
		{
			continue;
		}

		crab->Update(timer);

		// アクティブな敵をカウントする
		m_activeEnemyCount++;

		// アクティブなカニだけ配列に入れる
		m_activeCrabs.push_back(crab.get());
	}
	//サメの更新
	for (auto& shark : m_sharks)
	{
		assert(shark);

		// アクティブなサメだけ更新する
		if (!shark->IsActive())
		{
			continue;
		}

		shark->Update(timer);

		// アクティブな敵をカウントする
		m_activeEnemyCount++;

		// アクティブなサメだけ配列に入れる
		m_activeSharks.push_back(shark.get());
	}
	//鳥の更新
	for (auto& bird : m_birds)
	{
		assert(bird);

		// アクティブな鳥だけ更新する
		if (!bird->IsActive())
		{
			continue;
		}

		bird->Update(timer);

		// アクティブな敵をカウントする
		m_activeEnemyCount++;

		// アクティブな鳥だけ配列に入れる
		m_activeBirds.push_back(bird.get());
	}
	//ボスの更新
	m_boss->Update(timer);
}




/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void EnemyManager::Render()
{
	//カニの描画
	for (auto& crab : m_crabs)
	{
		assert(crab);

		// アクティブな敵だけ描画する
		if (!crab->IsActive())
		{
			continue;
		}
		//生存中のカニとステージの判定
		Vector3 pos = m_stage->NormalHitDetection(crab->GetPos()).pos;
		Matrix normal = m_stage->NormalHitDetection(crab->GetPos()).rotate;
	
		crab->Render(pos, normal);
	}
	//サメの描画
	for (auto& shark : m_sharks)
	{
		assert(shark);

		// アクティブな敵だけ描画する
		if (!shark->IsActive())
		{
			continue;
		}
		//生存中のサメとステージの判定
		Vector3 pos = m_stage->NormalHitDetection(shark->GetPos()).pos;
		Matrix normal = m_stage->NormalHitDetection(shark->GetPos()).rotate;

		shark->Render(pos, normal);
	}
	//鳥の描画
	for (auto& bird : m_birds)
	{
		assert(bird);

		// アクティブな敵だけ描画する
		if (!bird->IsActive())
		{
			continue;
		}
		//生存中の鳥とステージの判定
		Vector3 pos = m_stage->NormalHitDetection(bird->GetPos()).pos;
		Matrix normal = m_stage->NormalHitDetection(bird->GetPos()).rotate;

		bird->Render(pos, normal);
	}
	//ボスの描画
	//ボスとステージの判定
	Vector3 Bpos = m_stage->NormalHitDetection(m_boss->GetPos()).pos;
	Matrix Bnormal = m_stage->NormalHitDetection(m_boss->GetPos()).rotate;
	m_boss->Render(Bpos, Bnormal);
}


// 敵を出現させる
bool EnemyManager::Spawn(IEnemy::EnemyState state)
{
	// 出現データリストが終了した
	if (m_nowListNumber >= m_enemyDataList.size())
	{
		//ファイルが終了
		m_CSVFlag = true;
		return false;
	}

	// フレームカウンタが敵の出現時間になっていない
	if (m_enemyDataList[m_nowListNumber].time > m_frameCounter)
	{
		return false;
	}

	// 敵のインスタンス配列からアクティブでないものを利用する
	for (int i = 0; i < MAX_ENEMY_COUNT; i++)
	{
		//どれも生存中じゃなければ続けない
		if (m_crabs[i]->IsActive()  ||
			m_sharks[i]->IsActive() ||
			m_birds[i]->IsActive())
		{
			continue;
		}
		//IDを見て対応する敵を初期化
		switch (m_enemyDataList[m_nowListNumber].id)
		{
			case 0:
				if (!m_crabs[i]->IsActive())
				{
					m_crabs[i]->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			case 1:
				if (!m_sharks[i]->IsActive())
				{
					m_sharks[i]->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			case 2:
				if (!m_birds[i]->IsActive())
				{
					m_birds[i]->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			case 3:
				if (!m_boss->IsActive())
				{
					m_boss->Initialize(state,
						m_enemyDataList[m_nowListNumber].position);
				}
				break;
			default:
				break;
		}

		// 出現データリストの添え字を更新する
		m_nowListNumber++;

		// 敵を出現させた
		return true;
	}

	// 敵がすべて使用中だった
	return false;
}

//---------------------------------------------------------
// CSVをロードする
//---------------------------------------------------------
void EnemyManager::LoadCSV(const char* fileName)
{
	std::ifstream ifs;     //ファイルストリーム
	std::string line;      //1行分のデータ	
	std::istringstream iss;//文字列ストリーム

	//ファイルストリームを開く
	ifs.open(fileName);

	assert(ifs && "EnemyManager::LoadCSV::ファイルを開けませんでした！");

	//ヘッダ行を読み飛ばす
	std::getline(ifs, line);

	//ifs末尾までデータを処理する
	//ifsから１行分のデータを取り出す
	while (std::getline(ifs, line))
	{
		//カンマ区切りを空白区切りに変換する
		std::replace(line.begin(), line.end(), ',', ' ');

		//おまじない
		iss.clear(std::istringstream::goodbit);

		//一行分のデータをissに読み込む
		iss.str(line);

		//データを分割
		float time;
		int id;
		float x;
		float y;
		float z;
		iss >> time >> id >> x >> y >> z;

		//追加する敵データを作成する
		EnemyData data;
		data.time = time;
		data.id = id;
		data.position = { x,y,z };

		//敵データを敵リストに追加
		m_enemyDataList.push_back(data);
	}
	//閉じる
	ifs.close();
}
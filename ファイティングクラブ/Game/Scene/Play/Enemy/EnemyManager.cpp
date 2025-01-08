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
	m_boss{},
	m_activeEnemyCount{},
	m_enemyDataList{},
	m_frameCounter{},
	m_nowListNumber{},
	m_activeCrabs{},
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
void EnemyManager::Update(float timer)
{
	// フレームをカウントする
	m_frameCounter++;

	// 敵をスポーンする
	Spawn();

	//配列をクリアする
	m_activeEnemyCount = 0;
	m_activeCrabs.clear();

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

	//ボスの描画
	//ボスとステージの判定
	Vector3 Bpos = m_stage->NormalHitDetection(m_boss->GetPos()).pos;
	Matrix Bnormal = m_stage->NormalHitDetection(m_boss->GetPos()).rotate;
	m_boss->Render(Bpos, Bnormal);
}


// 敵を出現させる
bool EnemyManager::Spawn()
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
		if (m_crabs[i]->IsActive())
		{
			continue;
		}
		//IDを見て対応する敵を初期化
		switch (m_enemyDataList[m_nowListNumber].id)
		{
			case 0:
				if (!m_crabs[i]->IsActive())
				{
					m_crabs[i]->Initialize(m_enemyDataList[m_nowListNumber].position);
				}
				break;
			case 3:
				if (!m_boss->IsActive())
				{
					m_boss->Initialize(m_enemyDataList[m_nowListNumber].position);
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
/**
 * @file   EnemyManager.h
 *
 * @brief  敵に関するヘッダファイル
 *
 * @author kaede
 *
 * @date   2023/11/08
 */

// 多重インクルードの防止 =====================================================
#pragma once
#include "Interface/IEnemy.h"
#include "Crab/EnemyCrab.h"
#include "Shark/EnemyShark.h"
#include "Bird/EnemyBird.h"
#include "Boss/EnemyBoss.h"
#include <vector>

class Stage;


// クラスの定義 ===============================================================
/**
  * @brief ゲーム
  */
class EnemyManager
{
// データメンバの宣言
private:
	struct EnemyData
	{
		float time = 0.0f;					// 出現時間
		int id = 0;                     //敵の種類
		DirectX::SimpleMath::Vector3 position;	        // 出現座標
	};

	// 敵の総数
	static const int MAX_ENEMY_COUNT = 1;
	// 敵の配列
	std::unique_ptr<IEnemy>  m_crabs[MAX_ENEMY_COUNT];
	std::unique_ptr<IEnemy> m_sharks[MAX_ENEMY_COUNT];
	std::unique_ptr<IEnemy>  m_birds[MAX_ENEMY_COUNT];
	//ボス
	std::unique_ptr<IEnemy> m_boss;
	// 生存中の敵数カウンタ
	int m_activeEnemyCount;
	// 敵の出現リスト
	std::vector<EnemyData>m_enemyDataList;
	// フレームカウンタ
	int m_frameCounter;
	// 敵の出現リスト、どこまで実行したか
	int m_nowListNumber;
	// アクティブな敵配列
	std::vector<IEnemy*>  m_activeCrabs;
	std::vector<IEnemy*> m_activeSharks;
	std::vector<IEnemy*>  m_activeBirds;

	//ファイルが終わったか
	bool m_CSVFlag;

	//ステージのポインタ
	Stage* m_stage;

// メンバ関数の宣言
public:
	// コンストラクタ
	EnemyManager(Stage* stage);

	// デストラクタ
	~EnemyManager();

// 操作
public:
	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(float timer, IEnemy::EnemyState state, DirectX::SimpleMath::Vector3 Ppos);

	// 描画処理
	void Render();

public:
	// 敵を出現させる
	bool Spawn(IEnemy::EnemyState state);
	// 全敵数を返す
	static int GetTotalEnemyCount() { return MAX_ENEMY_COUNT; }
	// 生存中の敵数を返す
	int GetActiveEnemyCount() const { return m_activeEnemyCount; }
	// 生存中の敵配列を取得する
	std::vector<IEnemy*>& GetActiveCrabs() { return m_activeCrabs; }
	std::vector<IEnemy*>& GetActiveSharks() { return m_activeSharks; }
	std::vector<IEnemy*>& GetActiveBirds() { return m_activeBirds; }
	//ボスを取得する 
	std::unique_ptr<IEnemy>& GetBoss() { return m_boss; }
	//ファイルが終了したか
	bool GetCSV()const { return m_CSVFlag; }

private:
	//CSVをロードする
	void LoadCSV(const char* fileName);
};

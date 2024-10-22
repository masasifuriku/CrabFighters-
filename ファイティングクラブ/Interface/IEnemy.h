/*
	@file	IEnemy.h
	@brief	敵のインターフェイスクラス
*/
#pragma once
#include "pch.h"

class IEnemy
{
public:
	//敵の状態
	enum EnemyState 
	{
		Patrol,  //プレイヤーを探してパトロール
		Chase,	 //見つけて追跡
		Battle,	 //交戦中
		Escape,	 //逃走
		DEAD     //死亡
	};

public:
	//現在の位置の取得
	virtual DirectX::SimpleMath::Vector3 GetPos()const = 0;
	//敵の状態を設定する
	virtual void SetEnemyState(EnemyState state) = 0;
	// 敵が生存中か
	virtual bool IsActive() = 0;
	//ダメージを受ける
	virtual void TakeDamage(float damage) = 0;
	//当たり判定生成
	//バウンディングスフィア
	virtual DirectX::BoundingSphere GetBoundingSphere(DirectX::SimpleMath::Vector3 center) = 0;
	//体力を取得する
	virtual float GetHP()const = 0;
public:
	//仮想デストラクタ
	virtual ~IEnemy() = default;
	//初期化
	virtual void Initialize(EnemyState state,DirectX::SimpleMath::Vector3 position) = 0;
	//更新
	virtual void Update(float elapsedTime, DirectX::SimpleMath::Vector3 Ppos) = 0;
	//描画
	virtual void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal
	) = 0;
};

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
		NONE,
		Patrol,  //プレイヤーを探してパトロール
		Chase,	 //見つけて追跡
		Battle,	 //交戦中
		Escape,	 //逃走
		DEAD     //死亡
	};

public:
	//現在の位置の渡す
	virtual DirectX::SimpleMath::Vector3 GetPos()const = 0;
	//位置を受け取る
	virtual void SetPos(DirectX::SimpleMath::Vector3 pos) = 0;
	//現在の角度を渡す
	virtual float GetAngle()const = 0;
	//角度を受け取る
	virtual void SetAngle(float angle) = 0;
	//敵の状態を設定する
	virtual void SetEnemyState(EnemyState state) = 0;
	// 敵が生存中か
	virtual bool IsActive() = 0;
	//ダメージを受ける
	virtual void TakeDamage(float damage) = 0;
	//当たり判定生成
	// バウンディングスフィアを作成する
	virtual DirectX::BoundingSphere CreateBoundingSphere(const float& radius) = 0;
	//バウンディングスフィア
	virtual DirectX::BoundingSphere& GetBodyBoundingSphere() = 0;
	// バウンディングスフィアを描画する
	virtual void DrawBoundingSphere() = 0;
	//体力を取得する
	virtual float GetHP()const = 0;
public:
	//仮想デストラクタ
	virtual ~IEnemy() = default;
	//初期化
	virtual void Initialize(EnemyState state,DirectX::SimpleMath::Vector3 position) = 0;
	//更新
	virtual void Update(float elapsedTime) = 0;
	//描画
	virtual void Render(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Matrix normal
	) = 0;
};

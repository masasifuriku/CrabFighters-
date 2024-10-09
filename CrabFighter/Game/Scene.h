/*
	@file	Scene.h
	@brief	一般的なシーンクラス
*/
#pragma once
#include <unordered_map>

// 前方宣言
class CommonResources;

// 一般的なシーンクラス
class Scene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

public:
	Scene();
	~Scene();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void Finalize();
};

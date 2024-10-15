/*
	@file	IScene.h
	@brief	�V�[���̃C���^�[�t�F�C�X�N���X
*/
#pragma once

class IScene
{
public:
	// �V�[���h�c
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		PLAY,
		RESULT
	};


public:
	virtual ~IScene() = default;

	virtual void Initialize() = 0;

	virtual void Update(float elapsedTime) = 0;

	virtual void Render() = 0;

	virtual void Finalize() = 0;

	virtual SceneID GetNextSceneID() const = 0;
};

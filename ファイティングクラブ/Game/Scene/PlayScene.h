/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Interface/IScene.h"

// �O���錾
class Player;
class Enemy;

namespace mylib
{
	class TPS_Camera;
	class GridFloor;
}


class PlayScene final :
    public IScene
{
private:
	// �f�o�b�O�J����
	std::unique_ptr<mylib::TPS_Camera> m_camera;

	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	//�v���C���[
	std::unique_ptr<Player> m_player;
	//�G
	std::unique_ptr<Enemy> m_enemy;
	
	
public:
	PlayScene();
	~PlayScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};

/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Interface/IScene.h"

// �O���錾
class PlayerBody;
class EnemyManager;
class Stage;

namespace mylib
{
	class TPS_Camera;
}


class PlayScene final :
    public IScene
{
private:
	// TPS�J����
	std::unique_ptr<mylib::TPS_Camera> m_camera;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	//�v���C���[
	std::unique_ptr<PlayerBody> m_player;
	//�G
	std::unique_ptr<EnemyManager> m_enemy;
	//�X�e�[�W
	std::unique_ptr<Stage> m_stage;

	//�X�v���C�g�o�b�`
	DirectX::SpriteBatch* m_Batch;
	//�X�v���C�g�t�H���g
	DirectX::SpriteFont* m_Font;
	
	
public:
	PlayScene();
	~PlayScene() override;

	void Initialize() override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;

private:
	//�J�j�̍X�V
	void UpdateCrabs();
	//�T���̍X�V
	void UpdateSharks();
	//���̍X�V
	void UpdateBirds();
	//�{�X�̍X�V
	void UpdateBoss();

	//�f�o�b�N���
	void DrawDebug();
};

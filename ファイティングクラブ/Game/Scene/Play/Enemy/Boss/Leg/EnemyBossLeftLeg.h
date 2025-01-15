//--------------------------------------------------------------------------------------
// File: EnemyBossLeftLeg.h
//
// �{�X�����N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "StepTimer.h"
#include "Libraries/EdeLib/ModelManager.h"

class EnemyBossLeftLeg 
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_BoundingSphere;

public:
	EnemyBossLeftLeg();
	~EnemyBossLeftLeg();

	void Initialize();
	void Update(float timer);
	void Render();
public:
	//�o�E���f�B���O�X�t�B�A����
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius) ;
	//�o�E���f�B���O�X�t�B�A���擾����
	DirectX::BoundingSphere& GetBodyBoundingSphere(){ return m_BoundingSphere; }
	// �o�E���f�B���O�X�t�B�A��`�悷��
	void DrawBoundingSphere();
private:
};

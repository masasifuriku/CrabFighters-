//--------------------------------------------------------------------------------------
// File: Stage.h
//
// �X�e�[�W�N���X
//
//-------------------------------------------------------------------------------------

#pragma once
#include "Libraries/EdeLib/ModelManager.h"

namespace mylib
{
	class CollisionMesh;
}

struct Normal 
{
	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Matrix rotate;
};


class Stage
{
private:
	// ���f��
	std::unique_ptr<Ede::ModelManager> m_model;
	//�R���W�������b�V��
	std::unique_ptr<mylib::CollisionMesh> m_collisionMesh;

	// ���f���\���t���O
	bool m_isVisible;

	//�n�`�̔���p
	//�|���S����Ray�̏Փˍ��W
	DirectX::SimpleMath::Vector3 m_hitPosition;
	//���W�ۑ��p
	Normal m_normal;
	//�Փ˂����|���S���̔ԍ�
	int m_hitPolygonNo;
	

public:
	Stage();
	~Stage();

	void Initialize();
	void Render();

public:
	//�@���Ƃ̓����蔻��
	Normal NormalHitDetection(DirectX::SimpleMath::Vector3 pos);
};

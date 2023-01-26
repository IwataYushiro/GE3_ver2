#pragma once
#include "Input.h"
#include "Model.h"
#include "Object3d.h"
#include "PlayerBullet.h"
#include <DirectXMath.h>
#include <list>
#include <memory>

class Player
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	Player();
	~Player();
	

	//������
	void Initialize(Model* model, Object3d* obj, Input* input);
	//���Z�b�g����
	void Reset();
	
	//�X�V
	void Update();

	//�v���C���[�̈ړ�����
	void Move();

	//�v���C���[�̍U������
	void Attack();

	//�]��
	void Trans();

	//���[���h���W���擾
	XMFLOAT3 GetWorldPosition();

	//�`��
	void Draw();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	//�e���X�g���擾
	static const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

private:
	//�e
	static std::list<std::unique_ptr<PlayerBullet>> bullets_;
	
	//���f��
	Model* model_ = nullptr;
	Model* modelBullet_ = nullptr;

	Object3d* obj_ = nullptr;
	Object3d* objBullet_ = nullptr;

	//�C���v�b�g
	Input* input_ = nullptr;
	
	//�|�W�V����
	XMFLOAT3 pos;
	//�A���O��
	XMFLOAT3 angle;

	//���S�t���O�ƃ��C�t
	static bool isDead_;
	static int life_;

public: //�A�N�Z�b�T�A�C�����C���֐�
	static bool IsDead() { return isDead_; }

};

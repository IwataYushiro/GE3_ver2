#pragma once
#include "Audio.h"
#include "Input.h"
#include "Model.h"
#include "Object3d.h"
#include <DirectXMath.h>
#include <memory>

class Player {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//������
	void Initialize(Model* model, Object3d* obj, Input* input, XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f });

	//�X�V
	void Update();
	//�]��
	void Trans();
	//�`��
	void Draw();

	//���Z�b�g����
	void Reset();

	// ���S
	void IsDead() { isDead_ = true; }

	// �����蔻��
	void OnCollisionStage(bool collisionFlag);
	static void OnCollisionPlayer(bool collisionFlag);

private:
	//�v���C���[�̈ړ�����
	void Move();

private:
	//�C���v�b�g
	Input* input_ = nullptr;
	
	//���f��
	Model* model_ = nullptr;
	Object3d* obj_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�T�E���h�f�[�^
	uint32_t jumpSound_ = 0;

	// ���[���h�ϊ��f�[�^
	XMFLOAT3 pos_;
	// �O�t���[�����W
	XMFLOAT3 prePos_{};
	// ���a
	float radius_ = 1.5f;
	//���S�t���O
	bool isDead_;
	static bool isDeads_;

public: //�A�N�Z�b�T�A�C�����C���֐�
	bool IsDead() const { return isDead_; }
	XMFLOAT3 GetPosition() const { return pos_; }
	float GetRadius() const { return radius_; }

};

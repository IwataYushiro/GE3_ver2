#pragma once
#include "Model.h"
#include "Object3d.h"
#include <DirectXMath.h>

class Switch {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	// ������
	void Initialize(Model* model, Object3d* obj);

	// �X�V
	void Update();
	//�]��
	void Trans();
	// �`��
	void Draw();

	// �X�C�b�`�I��
	void OnCollisionSwitch();

private:
	// ���f��
	Model* model_ = nullptr;
	//�I�u�W�F�N�g
	Object3d* obj_ = nullptr;
	// ���[���h�ϊ��f�[�^
	XMFLOAT3 pos_;
	XMFLOAT3 scale_;

	// �t���O
	bool isFlag_ = false;

public: // �A�N�Z�b�T
	bool GetFlag() { return isFlag_; }
	void SetPosition(XMFLOAT3 pos); 
};
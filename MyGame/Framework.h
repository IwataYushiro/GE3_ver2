#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "SpriteCommon.h"

//�Q�[���S��
class Framework
{
public://�����o�֐�
	virtual ~Framework() = default;
	//������
	virtual void Initialize();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw() = 0;
	//�I������
	virtual void Finalize();
	//�I���t���O�̎�t
	virtual bool IsEndRequest() { return EndGame_; }

	//���s
	void Run();

protected:
	//WinApp
	WinApp* winApp_ = new WinApp();
	//DXCommon
	DirectXCommon* dxCommon_ = new DirectXCommon();
	//SpriteCommon
	SpriteCommon* sprCommon_ = new SpriteCommon();
	//Input
	Input* input_ = new Input();

	//�Q�[���I���t���O
	bool EndGame_ = false;
};
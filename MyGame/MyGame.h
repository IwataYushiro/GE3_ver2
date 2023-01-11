#pragma once
#include "Framework.h"
#include "WinApp.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"

class MyGame :public Framework
{
public:
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�I��
	void Finalize() override;
	
private:
	//WinApp
	WinApp* winApp_ = new WinApp();
	//DXCommon
	DirectXCommon* dxCommon_ = new DirectXCommon();
	//SpriteCommon
	SpriteCommon* sprCommon_ = new SpriteCommon();
	//Sprite
	Sprite* sprite_ = new Sprite();
	//Audio
	Audio* audio_ = new Audio();
	//Input
	Input* input_ = new Input();
	//imgui
	ImGuiManager* imguiManager_ = new ImGuiManager();

	//�T�E���h�ǂݍ���
	Audio::SoundData sound;

	//���f��
	Model* model_ = nullptr;

	//3D�I�u�W�F�N�g
	Object3d* object3D_ = nullptr;

	//�Q�[���I���t���O
	bool EndGame_ = false;

};


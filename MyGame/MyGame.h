#pragma once
#include "WinApp.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"

class MyGame
{
public:
	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�I��
	void Finalize();
	
private:

	WinApp* winApp = new WinApp();

	DirectXCommon* dxCommon = new DirectXCommon();

	SpriteCommon* sprCommon = new SpriteCommon();

	Sprite* sprite = new Sprite();

	Audio* audio = new Audio();

	Input* input = new Input();

	ImGuiManager* imguiManager = new ImGuiManager();
};


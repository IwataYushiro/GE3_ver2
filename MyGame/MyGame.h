#pragma once
#include "Framework.h"
#include "Audio.h"
#include "ImGuiManager.h"
#include "Object3d.h"
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

	//Sprite
	Sprite* sprite_ = new Sprite();
	//Audio
	Audio* audio_ = new Audio();

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


#pragma once
#include "Framework.h"
#include "Audio.h"
#include "ImGuiManager.h"
#include "Object3d.h"
#include "Sprite.h"

#include "Player.h"

class MyGame :public Framework
{
public:

	enum Scene { //�V�[��ID
		title,
		howtoplay,
		stage,
		clear,
		gameover,
	};

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
	Model* modelPlayer_ = nullptr;
	Model* modelEnemy_ = nullptr;
	//�V��
	Model* modelSkyDome_ = nullptr;

	//3D�I�u�W�F�N�g
	Object3d* object3DPlayer_ = nullptr;
	Object3d* object3DEnemy_ = nullptr;
	Object3d* object3DSkyDome_ = nullptr;

	Player* player_ = nullptr;

	//�V�[��
	size_t scene_;

	//�Q�[���I���t���O
	bool EndGame_ = false;

};


#include "WinApp.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"

using namespace DirectX;

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#pragma region �|�C���^�u����
	WinApp* winApp = new WinApp();

	DirectXCommon* dxCommon = new DirectXCommon();

	SpriteCommon* sprCommon = new SpriteCommon();

	Sprite* sprite = new Sprite();

	Audio* audio = new Audio();

	Input* input = new Input();

	ImGuiManager* imguiManager = new ImGuiManager();

#pragma endregion

#pragma region Windows������
	winApp->Initialize();
#pragma endregion
	// DirectX�����������@��������

	//DirectX������
	dxCommon->Initialize(winApp);
	
	//�X�v���C�g���
	sprCommon->Initialize(dxCommon);
	//����
	input->Initialize(winApp);
	//imgui
	imguiManager->Initialize(winApp);

	// DirectX�����������@�����܂�

	//��U������imgui�e�X�g
	
	// �`�揉���������@��������
#pragma region �`�揉��������
	
	//�����f�[�^
	audio->Initialize();

	Audio::SoundData sound = audio->SoundLordWave("Resources/TestMusic.wav");
	//�����Đ��Ăяo����
	audio->SoundPlayWave(audio->GetXAudio2(), sound);

	//�����Ńe�N�X�`�����w�肵�悤
	UINT texindex = 00;
	sprCommon->LoadTexture(texindex, "texture.png");
	sprite->Initialize(sprCommon, texindex);
	
	//3D�I�u�W�F�N�g�֌W
	Object3d::StaticInitialize(dxCommon->GetDevice(), winApp->window_width, winApp->window_height);
	
	//OBJ�t�@�C�����烂�f���f�[�^��ǂݍ���
	Model* model = Model::LoadFromOBJ("triangle_mat");
	//3D�I�u�W�F�N�g����
	Object3d* object3d = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f���R�t����
	object3d->SetModel(model);

#pragma endregion
	// �`�揉���������@�����܂�

	//�Q�[�����[�v
	while (true)
	{
		//Windows�̃��b�Z�[�W����
		if (winApp->ProcessMessage())
		{
			//�Q�[�����[�v�𔲂���
			break;
		}

		// DirectX���t���[�������@��������
		
		input->Update();
		// �X�V������������
		
		//�X�v���C�g�Ăяo����
		sprite->Update();
	
		//���f���Ăяo����
		object3d->Update();
		// �����܂�
		
		//�`��O����
		dxCommon->PreDraw();

		//�w�i�X�v���C�g�`��
		
		//�X�v���C�g�`��O����
		sprCommon->PreDraw();
		//�X�v���C�g�`��
		sprite->Draw();
		
		//���f���`��

		//���f���`��O����
		object3d->PreDraw(dxCommon->GetCommandList());

		//���f���`��
		object3d->Draw();

		//���f���`��㏈��
		object3d->PostDraw();

		//�O�i�X�v���C�g�`�� 

		//�`��㏈��

		dxCommon->PostDraw();
		// 4.�`��R�}���h�����܂�

		// DirectX���t���[�������@�����܂�
		
	}
	//�I������
	audio->Finalize();
	winApp->Finalize();

	//���
	//�e�퉹��
	audio->SoundUnLoad(&sound);
	//�����S��
	delete audio;

	//�X�v���C�g
	delete sprite;

	//���f��
	//3D�I�u�W�F�N�g
	delete object3d;
	//3D���f��
	delete model;

	//��Ռn
	delete imguiManager;
	delete sprCommon;
	delete input;
	delete dxCommon;
	delete winApp;
	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello DilectX!!\n");

	return 0;
}
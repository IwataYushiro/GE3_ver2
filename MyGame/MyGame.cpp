#include "MyGame.h"

using namespace DirectX;

void MyGame::Initialize()
{
	Framework::Initialize();
	//Sprite
	sprite_ = new Sprite();
	//Audio
	audio_ = new Audio();
	//imgui
	imguiManager_ = new ImGuiManager();

#pragma region Windows������
#pragma endregion
	// DirectX�����������@��������
	//imgui
	imguiManager_->Initialize(winApp_, dxCommon_);

	// DirectX�����������@�����܂�
	// �`�揉���������@��������
#pragma region �`�揉��������
	//�����f�[�^
	audio_->Initialize();
	sound = audio_->SoundLordWave("Resources/TestMusic.wav");
	//�����Đ��Ăяo����
	audio_->SoundPlayWave(audio_->GetXAudio2(), sound);

	//�����Ńe�N�X�`�����w�肵�悤
	UINT texindex = 00;
	sprCommon_->LoadTexture(texindex, "texture.png");
	sprite_->Initialize(sprCommon_, texindex);

	//3D�I�u�W�F�N�g�֌W
	object3D_->StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);

	//OBJ�t�@�C�����烂�f���f�[�^��ǂݍ���
	model_ = Model::LoadFromOBJ("triangle_mat");
	//3D�I�u�W�F�N�g����
	object3D_ = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f���R�t����
	object3D_->SetModel(model_);

#pragma endregion
	// �`�揉���������@�����܂�
}

void MyGame::Update()
{
	// DirectX���t���[�������@��������
	// �X�V������������
	Framework::Update();

	//�X�v���C�g�Ăяo����
	sprite_->Update();

	//���f���Ăяo����
	XMFLOAT3 pos = object3D_->GetPosition();

	if (input_->PushKey(DIK_RIGHT))
	{
		pos.x += 0.1f;
	}
	if (input_->PushKey(DIK_LEFT))
	{
		pos.x -= 0.1f;
	}
	if (input_->PushKey(DIK_UP))
	{
		pos.y += 0.1f;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		pos.y -= 0.1f;
	}

	object3D_->SetPosition(pos);

	object3D_->Update();

	//imgui
	imguiManager_->Update();
	// �����܂�
}

void MyGame::Draw()
{
	//�`��O����
	dxCommon_->PreDraw();

	//�w�i�X�v���C�g
	//�X�v���C�g�`��O����
	sprCommon_->PreDraw();
	//�X�v���C�g�`��
	sprite_->Draw();

	//���f��
	//���f���`��O����
	object3D_->PreDraw(dxCommon_->GetCommandList());

	//���f���`��
	object3D_->Draw();

	//���f���`��㏈��
	object3D_->PostDraw();

	//�O�i�X�v���C�g

	//ImGui�̕\��
	imguiManager_->Draw();
	//�`��㏈��
	dxCommon_->PostDraw();
}

void MyGame::Finalize()
{
	//�I������
	imguiManager_->Finalize();
	audio_->Finalize();

	//���
	//�e�퉹��
	audio_->SoundUnLoad(&sound);
	//�����S��
	delete audio_;

	//�X�v���C�g
	delete sprite_;

	//���f��
	//3D�I�u�W�F�N�g
	delete object3D_;
	//3D���f��
	delete model_;

	//��Ռn
	delete imguiManager_;

	Framework::Finalize();
}

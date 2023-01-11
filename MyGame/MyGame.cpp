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
	Object3d::StaticInitialize(dxCommon_->GetDevice(), winApp_->window_width, winApp_->window_height);
	
	//OBJ�t�@�C�����烂�f���f�[�^��ǂݍ���
	
	modelSkyDome_ = Model::LoadFromOBJ("playerbullet");
	modelPlayer_ = Model::LoadFromOBJ("player");
	modelEnemy_ = Model::LoadFromOBJ("enemy1");
	

	//3D�I�u�W�F�N�g����
	object3DSkyDome_ = Object3d::Create();
	object3DPlayer_ = Object3d::Create();
	object3DEnemy_ = Object3d::Create();


	//�I�u�W�F�N�g�Ƀ��f���R�t����
	object3DSkyDome_->SetModel(modelSkyDome_);
	object3DPlayer_->SetModel(modelPlayer_);
	object3DEnemy_->SetModel(modelEnemy_);
	
	//�|�W�V����
	object3DPlayer_->SetPosition({ 0.0f,0.0f,600.0f });
	object3DEnemy_->SetPosition({ 0.0f,0.0f,1000.0f });
	
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
	XMFLOAT3 pos = object3DPlayer_->GetPosition();
	XMFLOAT3 enemyPos = object3DEnemy_->GetPosition();

	if (input_->PushKey(DIK_RIGHT))
	{
		pos.x += 3.0f;
	}
	if (input_->PushKey(DIK_LEFT))
	{
		pos.x -= 3.0f;
	}
	if (input_->PushKey(DIK_UP))
	{
		pos.y += 3.0f;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		pos.y -= 3.0f;
	}
	enemyPos.z -= 0.2f;

	object3DPlayer_->SetPosition(pos);
	object3DEnemy_->SetPosition(enemyPos);

	object3DSkyDome_->Update();

	object3DPlayer_->Update();
	object3DEnemy_->Update();
	

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
	Object3d::PreDraw(dxCommon_->GetCommandList());
	
	//���f���`��
	object3DSkyDome_->Draw();
	object3DPlayer_->Draw();
	object3DEnemy_->Draw();

	//���f���`��㏈��
	Object3d::PostDraw();
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
	delete object3DPlayer_;
	delete object3DEnemy_;
	delete object3DSkyDome_;
	//3D���f��
	delete modelPlayer_;
	delete modelEnemy_;
	delete modelSkyDome_;

	//��Ռn
	delete imguiManager_;

	Framework::Finalize();
}

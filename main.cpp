#include "WinApp.h"
#include "DirectXCommon.h"
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

	Input* input = new Input();

#pragma endregion

#pragma region Windows������
	winApp->Initialize();
#pragma endregion
	// DirectX�����������@��������

	//DirectX������
	dxCommon->Initialize(winApp);
	
	//�X�v���C�g�֌W
	sprCommon->Initialize(dxCommon);
	
	//3D�I�u�W�F�N�g�֌W
	Object3d::StaticInitialize(dxCommon->GetDevice(), winApp->window_width, winApp->window_height);
	
	//OBJ�t�@�C�����烂�f���f�[�^��ǂݍ���
	Model* model = Model::LoadFromOBJ("triangle_mat");
	//3D�I�u�W�F�N�g����
	Object3d* object3d = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f���R�t����
	object3d->SetModel(model);

	// DirectX�����������@�����܂�


	// �`�揉���������@��������
#pragma region �`�揉��������

	//����
	input->Initialize(winApp);

	
	//�����Ńe�N�X�`�����w�肵�悤
	UINT texindex = 00;
	sprCommon->LoadTexture(texindex, "texture.png");
	sprite->Initialize(sprCommon, texindex);

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
		
		// �X�V������������
		input->Update();

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
	winApp->Finalize();

	//���
	//�X�v���C�g
	delete sprite;

	//���f��
	//3D�I�u�W�F�N�g
	delete object3d;
	//3D���f��
	delete model;

	//��Ռn
	delete sprCommon;
	delete input;
	delete dxCommon;
	delete winApp;
	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello DilectX!!\n");

	return 0;
}
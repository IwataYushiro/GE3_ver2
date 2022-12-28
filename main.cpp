#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
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
	Sprite* sprite2 = new Sprite();

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
	
	// DirectX�����������@�����܂�


	// �`�揉���������@��������
#pragma region �`�揉��������

	//����
	input->Initialize(winApp);

	
	//�����Ńe�N�X�`�����w�肵�悤
	UINT texindex1 = 00;
	sprCommon->LoadTexture(texindex1, "texture.png");
	sprite->Initialize(sprCommon, texindex1);
	
	uint16_t texindex2 = 01;
	sprCommon->LoadTexture(texindex2, "reimu.png");
	sprite2->Initialize(sprCommon, texindex2);

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

		XMFLOAT2 pos = sprite2->GetPosition();

		pos.x = 600.0f;
		pos.y = 300.0f;

		sprite->SetPosition(pos);
		sprite2->SetPosition(pos);
	
		sprite2->Update();
		// �����܂�
		
		//�`��O����
		dxCommon->PreDraw();

		//�w�i�X�v���C�g�`��
		sprCommon->PreDraw();
		sprite->Draw();
		sprite2->Draw();
		//���f���`��

		//�O�i�X�v���C�g�`�� 

		//�`��㏈��

		dxCommon->PostDraw();
		// 4.�`��R�}���h�����܂�

		// DirectX���t���[�������@�����܂�
		
	}
	winApp->Finalize();

	//���
	delete sprite;
	delete sprite2;

	delete sprCommon;
	delete input;
	delete dxCommon;
	delete winApp;
	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello DilectX!!\n");

	return 0;
}
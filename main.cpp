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

	Input* input = new Input();

#pragma endregion

#pragma region Windows������
	winApp->Initialize();
#pragma endregion
	// DirectX�����������@��������

	//DirectX������
	dxCommon->Initialize(winApp);
	// DirectX�����������@�����܂�

	// �`�揉���������@��������
#pragma region �`�揉��������

	//����
	input->Initialize(winApp);

	//�X�v���C�g�֌W
	sprCommon->Initialize(dxCommon);
	sprite->Initialize(sprCommon,input);

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
		float flipX = sprite->GetFlipX();
		float flipY = sprite->GetFlipY();
		XMFLOAT2 pos = sprite->GetPosition();
		
		//flipX = true;
		flipY = true;

		pos.x = 300.0f;
		pos.y = 300.0f;

		sprite->SetFlipX(flipX);
		sprite->SetFlipY(flipY);
		sprite->SetPosition(pos);

		sprite->Update();
		// �����܂�
		
		//�`��O����
		dxCommon->PreDraw();

		//�w�i�X�v���C�g�`��
		sprCommon->PreDraw();
		sprite->Draw();
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
	delete sprCommon;
	delete input;
	delete dxCommon;
	delete winApp;
	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello DilectX!!\n");

	return 0;
}
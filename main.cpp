#include "MyGame.h"

// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	MyGame game;
	//������
	game.Initialize();

	//�Q�[�����[�v
	while (true)
	{
		game.Update();

		//�I�����N�G�X�g�������烋�[�v�𔲂���
		if (game.IsEndRequest())
		{
			//�Q�[�����[�v�𔲂���
			break;
		}
		//�`�揈����������
		game.Draw();
		// �`�揈�������܂�

		// DirectX���t���[�������@�����܂�

	}
	//�I������
	game.Finalize();

	return 0;
}


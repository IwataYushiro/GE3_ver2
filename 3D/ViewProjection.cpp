#include "ViewProjection.h"
#include <cassert>
#include "WinApp.h"

using namespace DirectX;

void ViewProjection::Initialize()
{
	//�e�x�N�g��
	eye_ = { 0.0f, 0.0f, -100.0f };
	target_ = { 0.0f, 0.0f, 0.0f };
	up_ = { 0.0f,1.0f,0.0f };
	
	//����p
	angle_ = XMConvertToRadians(45.0f);
	//�A�X�y�N�g��
	aspect_ = (float)WinApp::window_width / WinApp::window_height;
	//�j�A�N���b�v(��O���̐[�x���E)
	nearZ_ = 0.1f;
	//�t�@�[�N���b�v(�����̐[�x���E)
	farZ = 1000.0f;

	//�s��
	matView_ = XMMatrixIdentity();
	matProjection_ = XMMatrixIdentity();

	
}

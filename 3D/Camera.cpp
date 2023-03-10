#include "Camera.h"
#include "WinApp.h"

using namespace DirectX;
Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	// �r���[�s��̐���
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	// ���s���e�ɂ��ˉe�s��̐���
	//constMap->mat = XMMatrixOrthographicOffCenterLH(
	//	0, window_width,
	//	window_height, 0,
	//	0, 1);
	
	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),
		(float)WinApp::window_width / WinApp::window_height,
		0.1f, 1000.0f
	);
}

void Camera::Update()
{
}

void Camera::SetEye(const XMFLOAT3& eye)
{
}

void Camera::SetTarget(const XMFLOAT3& target)
{
}

void Camera::SetUp(const XMFLOAT3& up)
{
}

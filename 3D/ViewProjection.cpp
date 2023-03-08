#include "ViewProjection.h"
#include <cassert>
#include "WinApp.h"
#include "DirectXCommon.h"

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

	//�萔�o�b�t�@����
	CreateConstBuffer();
	//�}�b�s���O
	MapingCB();
}

void ViewProjection::CreateConstBuffer()
{
	HRESULT result;

	D3D12_HEAP_PROPERTIES cbHeapProp{};		//�q�[�v�ݒ�
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD; //GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourseDesc{};
	cbResourseDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourseDesc.Width = (sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff;//256�o�C�g�A���C�������g
	cbResourseDesc.Height = 1;
	cbResourseDesc.DepthOrArraySize = 1;
	cbResourseDesc.MipLevels = 1;
	cbResourseDesc.SampleDesc.Count = 1;
	cbResourseDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@�̐���
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&cbResourseDesc, //���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void ViewProjection::MapingCB()
{
	HRESULT result;

	result = constBuff_->Map(0, nullptr, (void**)&constMap_);
	assert(SUCCEEDED(result));
}

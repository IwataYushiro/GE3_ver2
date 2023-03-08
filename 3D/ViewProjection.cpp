#include "ViewProjection.h"
#include <cassert>
#include "WinApp.h"
#include "DirectXCommon.h"

using namespace DirectX;

void ViewProjection::Initialize()
{
	//各ベクトル
	eye_ = { 0.0f, 0.0f, -100.0f };
	target_ = { 0.0f, 0.0f, 0.0f };
	up_ = { 0.0f,1.0f,0.0f };
	
	//視野角
	angle_ = XMConvertToRadians(45.0f);
	//アスペクト比
	aspect_ = (float)WinApp::window_width / WinApp::window_height;
	//ニアクリップ(手前側の深度限界)
	nearZ_ = 0.1f;
	//ファークリップ(奥側の深度限界)
	farZ = 1000.0f;

	//行列
	matView_ = XMMatrixIdentity();
	matProjection_ = XMMatrixIdentity();

	//定数バッファ生成
	CreateConstBuffer();
	//マッピング
	MapingCB();
}

void ViewProjection::CreateConstBuffer()
{
	HRESULT result;

	D3D12_HEAP_PROPERTIES cbHeapProp{};		//ヒープ設定
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD; //GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC cbResourseDesc{};
	cbResourseDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourseDesc.Width = (sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff;//256バイトアラインメント
	cbResourseDesc.Height = 1;
	cbResourseDesc.DepthOrArraySize = 1;
	cbResourseDesc.MipLevels = 1;
	cbResourseDesc.SampleDesc.Count = 1;
	cbResourseDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファの生成
	result = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourseDesc, //リソース設定
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

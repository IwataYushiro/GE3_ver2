#include "Sprite.h"

using namespace DirectX;

void Sprite::Initialize(SpriteCommon* spCommon, Input* input)
{
	HRESULT result;
	assert(spCommon);
	this->spCommon_ = spCommon;
	this->input_ = input;

	//サイズ
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	//頂点バッファ
	D3D12_HEAP_PROPERTIES heapProp{};	//ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPU転送用
	//リソース設定
	
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//頂点バッファ生成
	result = spCommon_->GetDxCommon()->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));

	assert(SUCCEEDED(result));

	//GPU上のバッファに対応した仮想メモリを取得
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	//全頂点に対して
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];	//座標をコピー
	}
	//繋がりを解除
	vertBuff->Unmap(0, nullptr);

	//定数バッファ
	//マテリアル
	CreateConstBufferMaterial();
	constMapMaterial->color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	
	//変換行列
	CreateConstBufferTransform();
	//平行投影変換
	constMapTransform->mat = XMMatrixOrthographicOffCenterLH(0,(float)WinApp::window_width,(float)WinApp::window_height, 0, 0, 1);

	//シェーダーリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};				//設定構造体
	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping =
		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;

	//ハンドルの指す位置にシェーダーリソースビュー作成
	 spCommon_->GetDxCommon()->GetDevice()->
		 CreateShaderResourceView(spCommon_->GetTextureBuffer().Get(), &srvDesc,spCommon_->GetSRVHandle());

	//頂点バッファビュー
	//GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	//頂点一つ分のサイズ
	vbView.StrideInBytes = sizeof(vertices[0]);
}
void Sprite::Update()
{
	XMMATRIX matRot, matTrans;
	//スケーリング等計算
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotationZ);

	matTrans = XMMatrixTranslation(position.x,position.y,0.0f);
	//ワールド行列合成
	matWorld = XMMatrixIdentity();
	matWorld *= matRot;		//回転反映
	matWorld *= matTrans;	//平行移動反映

	constMapTransform->mat = matWorld;
	if (input_->PushKey(DIK_UP) || input_->PushKey(DIK_DOWN) || input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_LEFT))
	{
		if (input_->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input_->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input_->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input_->PushKey(DIK_LEFT)) { position.x -= 1.0f; }
	}

}
void Sprite::Draw()
{
	//頂点バッファビューの設定コマンド
	spCommon_->GetDxCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	//定数バッファビュー(CBVの設定コマンド)
	spCommon_->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

	spCommon_->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());
	//描画コマンド
	spCommon_->GetDxCommon()->GetCommandList()->DrawInstanced(_countof(vertices), 1, 0, 0);
}

void Sprite::CreateConstBufferMaterial()
{
	HRESULT result;

	D3D12_HEAP_PROPERTIES cbHeapProp{};		//ヒープ設定
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD; //GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC cbResourseDesc{};
	cbResourseDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourseDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;//256バイトアラインメント
	cbResourseDesc.Height = 1;
	cbResourseDesc.DepthOrArraySize = 1;
	cbResourseDesc.MipLevels = 1;
	cbResourseDesc.SampleDesc.Count = 1;
	cbResourseDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファの生成
	result = spCommon_->GetDxCommon()->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourseDesc, //リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));

	//定数バッファのマッピング
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);//マッピング
	assert(SUCCEEDED(result));
}
void Sprite::CreateConstBufferTransform()
{
	HRESULT result;

	D3D12_HEAP_PROPERTIES cbHeapProp{};		//ヒープ設定
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD; //GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC cbResourseDesc{};
	cbResourseDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourseDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;//256バイトアラインメント
	cbResourseDesc.Height = 1;
	cbResourseDesc.DepthOrArraySize = 1;
	cbResourseDesc.MipLevels = 1;
	cbResourseDesc.SampleDesc.Count = 1;
	cbResourseDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファの生成
	result = spCommon_->GetDxCommon()->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourseDesc, //リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform));
	assert(SUCCEEDED(result));

	//定数バッファのマッピング
	result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);//マッピング
	assert(SUCCEEDED(result));
}
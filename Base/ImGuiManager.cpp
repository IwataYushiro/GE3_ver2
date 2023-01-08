#include "ImGuiManager.h"
#include <cassert>

void ImGuiManager::Initialize(WinApp* winApp, DirectXCommon* dxCommon)
{
	HRESULT result;

	this->winApp_ = winApp;
	this->dxCommon_ = dxCommon;

	//ImGuiのコンテキストを生成
	ImGui::CreateContext();
	//ImGuiのスタイルを指定
	ImGui::StyleColorsDark();
	
	//デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	//生成
	result = dxCommon_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvHeap_));
	assert(SUCCEEDED(result));

	//Win32の初期関数
	ImGui_ImplWin32_Init(winApp_->GetHwnd());
	//DX12の初期関数
	ImGui_ImplDX12_Init(
		dxCommon_->GetDevice(),
		static_cast<int>(dxCommon_->GetBuckBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap_.Get(),
		srvHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvHeap_->GetGPUDescriptorHandleForHeapStart()
	);
	//標準フォントの追加
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

}

void ImGuiManager::Update()
{
}

void ImGuiManager::Finalize()
{
}

#include "ImGuiManager.h"
#include <cassert>

void ImGuiManager::Initialize(WinApp* winApp, DirectXCommon* dxCommon)
{
	HRESULT result;

	this->winApp_ = winApp;
	this->dxCommon_ = dxCommon;

	//ImGui�̃R���e�L�X�g�𐶐�
	ImGui::CreateContext();
	//ImGui�̃X�^�C�����w��
	ImGui::StyleColorsDark();
	
	//�f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	//����
	result = dxCommon_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvHeap_));
	assert(SUCCEEDED(result));

	//Win32�̏����֐�
	ImGui_ImplWin32_Init(winApp_->GetHwnd());
	//DX12�̏����֐�
	ImGui_ImplDX12_Init(
		dxCommon_->GetDevice(),
		static_cast<int>(dxCommon_->GetBuckBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap_.Get(),
		srvHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvHeap_->GetGPUDescriptorHandleForHeapStart()
	);
	//�W���t�H���g�̒ǉ�
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();

}

void ImGuiManager::Begin()
{
	//imgui�t���[���J�n
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::End()
{
	//�`��O����
	ImGui::Render();
}

void ImGuiManager::Draw()
{
	//�R�}���h���X�g
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	//�f�X�N���v�^�q�[�v�̔z����Z�b�g����R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap_.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//�`��R�}���h�̎��s
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);
}

void ImGuiManager::Finalize()
{
	//�㏈��
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//�f�X�N���v�^�q�[�v�J��
	srvHeap_.Reset();
}

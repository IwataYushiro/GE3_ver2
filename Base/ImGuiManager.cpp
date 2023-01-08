#include "ImGuiManager.h"

void ImGuiManager::Initialize(WinApp* winApp)
{
	this->winApp_ = winApp;
	//ImGui�̃R���e�L�X�g�𐶐�
	ImGui::CreateContext();
	//ImGui�̃X�^�C�����w��
	ImGui::StyleColorsDark();
	//Win32�̏����֐�
	ImGui_ImplWin32_Init(winApp_->GetHwnd());
}

void ImGuiManager::Update()
{
}

void ImGuiManager::Finalize()
{
}

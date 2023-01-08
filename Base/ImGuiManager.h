#pragma once
#include "WinApp.h"
#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

//ImGui�Ǘ�
class ImGuiManager
{
public:
	
	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();
	//�I��
	void Finalize();

private:
	//WinApp
	WinApp* winApp_ = nullptr;
};

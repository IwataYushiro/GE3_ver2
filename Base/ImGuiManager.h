#pragma once
#include "WinApp.h"
#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

//ImGui管理
class ImGuiManager
{
public:
	
	//初期化
	void Initialize(WinApp* winApp);
	//更新
	void Update();
	//終了
	void Finalize();

private:
	//WinApp
	WinApp* winApp_ = nullptr;
};

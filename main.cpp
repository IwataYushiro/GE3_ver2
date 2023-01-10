#include "WinApp.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"

using namespace DirectX;


void ImGuiStyleShowSample() {
	static char buf[50] = {};
	static float f = 0.0f;

	ImGui::Text("Hello, world %d", 184);

	if (ImGui::Button("Style Classic")) { ImGui::StyleColorsClassic(); }
	if (ImGui::Button("Style Light")) { ImGui::StyleColorsLight(); }
	if (ImGui::Button("Style Dack")) { ImGui::StyleColorsDark(); }

	ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
}

void ImGuiMyFirstToolColor()
{
	// Create a window called "My First Tool", with a menu bar.
	static bool my_tool_active = true;
	static float my_color[4] = { 0.0f,0.0f,0.0f,0.0f };

	ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Edit a color stored as 4 floats
	ImGui::ColorEdit4("Color", my_color);

	// Generate samples and plot them
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();
}
// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#pragma region �|�C���^�u����
	WinApp* winApp = new WinApp();

	DirectXCommon* dxCommon = new DirectXCommon();

	SpriteCommon* sprCommon = new SpriteCommon();

	Sprite* sprite = new Sprite();

	Audio* audio = new Audio();

	Input* input = new Input();

	ImGuiManager* imguiManager = new ImGuiManager();

#pragma endregion

#pragma region Windows������
	winApp->Initialize();
#pragma endregion
	// DirectX�����������@��������

	//DirectX������
	dxCommon->Initialize(winApp);

	//�X�v���C�g���
	sprCommon->Initialize(dxCommon);
	//����
	input->Initialize(winApp);
	//imgui
	imguiManager->Initialize(winApp, dxCommon);

	// DirectX�����������@�����܂�

	//��U������imgui�e�X�g
	
	// �`�揉���������@��������
#pragma region �`�揉��������

	//�����f�[�^
	audio->Initialize();

	Audio::SoundData sound = audio->SoundLordWave("Resources/TestMusic.wav");
	//�����Đ��Ăяo����
	audio->SoundPlayWave(audio->GetXAudio2(), sound);

	//�����Ńe�N�X�`�����w�肵�悤
	UINT texindex = 00;
	sprCommon->LoadTexture(texindex, "texture.png");
	sprite->Initialize(sprCommon, texindex);

	//3D�I�u�W�F�N�g�֌W
	Object3d::StaticInitialize(dxCommon->GetDevice(), winApp->window_width, winApp->window_height);

	//OBJ�t�@�C�����烂�f���f�[�^��ǂݍ���
	Model* model = Model::LoadFromOBJ("triangle_mat");
	//3D�I�u�W�F�N�g����
	Object3d* object3d = Object3d::Create();
	//�I�u�W�F�N�g�Ƀ��f���R�t����
	object3d->SetModel(model);

#pragma endregion
	// �`�揉���������@�����܂�

	//�Q�[�����[�v
	while (true)
	{
		//Windows�̃��b�Z�[�W����
		if (winApp->ProcessMessage())
		{
			//�Q�[�����[�v�𔲂���
			break;
		}

		// DirectX���t���[�������@��������

		// �X�V������������
		input->Update();
		//�X�v���C�g�Ăяo����
		sprite->Update();

		//���f���Ăяo����
		object3d->Update();

		//ImGui�Ăяo��
		imguiManager->Begin();
		//��������ImGui�̕\�����ڂ�ǉ�����
		ImGuiMyFirstToolColor();
		//�\�����ڂ����܂�
		imguiManager->End();

		// �����܂�

		//�`�揈����������
		//�`��O����
		dxCommon->PreDraw();

		//�w�i�X�v���C�g
		//�X�v���C�g�`��O����
		sprCommon->PreDraw();
		//�X�v���C�g�`��
		sprite->Draw();

		//���f��
		//���f���`��O����
		object3d->PreDraw(dxCommon->GetCommandList());

		//���f���`��
		object3d->Draw();

		//���f���`��㏈��
		object3d->PostDraw();

		//�O�i�X�v���C�g

		//ImGui�̕\��
		imguiManager->Draw();
		//�`��㏈��
		dxCommon->PostDraw();
		// �`�揈�������܂�

		// DirectX���t���[�������@�����܂�

	}
	//�I������
	imguiManager->Finalize();
	audio->Finalize();
	winApp->Finalize();

	//���
	//�e�퉹��
	audio->SoundUnLoad(&sound);
	//�����S��
	delete audio;

	//�X�v���C�g
	delete sprite;

	//���f��
	//3D�I�u�W�F�N�g
	delete object3d;
	//3D���f��
	delete model;

	//��Ռn
	delete imguiManager;
	delete sprCommon;
	delete input;
	delete dxCommon;
	delete winApp;
	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello DilectX!!\n");

	return 0;
}


#pragma once
#include <xaudio2.h>
#include <fstream>
#include <wrl.h>

#pragma comment(lib,"xaudio2.lib")

class Audio
{
private://�G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�����o�֐�
	
	//������
	void Initialize();

	//�X�V

private://�����o�ϐ�

	ComPtr<IXAudio2> xaudio2;

	IXAudio2MasteringVoice* masterVoice;
};

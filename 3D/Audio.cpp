#include "Audio.h"

void Audio::Initialize()
{
	HRESULT result;

	//XAudio�̃C���X�^���X�𐶐�
	result = XAudio2Create(&xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);

	//�}�X�^�[�{�C�X�𐶐�
	result = xaudio2->CreateMasteringVoice(&masterVoice);

}
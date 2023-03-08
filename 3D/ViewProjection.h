#pragma once
#include <DirectXMath.h>
#include <wrl.h>
#include <d3d12.h>

struct ViewProjection
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�\���́A�o�b�t�@��
	struct ConstBufferDataViewProjection
	{
		XMMATRIX view;
		XMMATRIX projection;
		XMFLOAT3 cameraPos;
	};
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff_;
	//�}�b�s���O
	ConstBufferDataViewProjection* constMap_;

public://�֐�
	//������
	void Initialize();
	//�萔�o�b�t�@����
	void CreateConstBuffer();
	//�}�b�s���O
	void MapingCB();

public://�ϐ�
	//���_
	XMFLOAT3 eye_;
	//�����_
	XMFLOAT3 target_;
	//������x�N�g��
	XMFLOAT3 up_;

	//����p
	float angle_;
	//�A�X�y�N�g��
	float aspect_;
	//�j�A�N���b�v(��O���̐[�x���E)
	float nearZ_;
	//�t�@�[�N���b�v(�����̐[�x���E)
	float farZ;

	//�r���[�s��
	XMMATRIX matView_;
	//�v���W�F�N�V�����s��
	XMMATRIX matProjection_;
	//�r���[�v���W�F�N�V�����s��(�����p)
	XMMATRIX matViewProjection_;

	

};
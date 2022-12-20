#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

//�X�v���C�g��ՃN���X

class SpriteCommon
{
public:
	//�G�C���A�X�e���v���[�g�Ƃ��ŐF�X�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public://�����o�֐�

	~SpriteCommon();
	//������
	void Initialize(DirectXCommon* dxCommon);

	//�e�N�X�`���ǂݍ���
	
	//�`��O����
	void PreDraw();

private://�����o�ϐ�

	DirectXCommon* dxCommon_ = nullptr;

	//SRV�̍ő��
	static const size_t kMaxSRVCount = 2056;

	//�e�N�X�`���o�b�t�@�̐���
	ComPtr<ID3D12Resource> texbuff = nullptr;
	// �摜�C���[�W�f�[�^�z��
	XMFLOAT4* imageData;

	//�ݒ�����Ƃ�SRV�p�f�X�N���v�^�q�[�v�𐶐�
	ComPtr<ID3D12DescriptorHeap> srvHeap;
	//SRV�q�[�v�̃n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;


	//�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> vsBlob = nullptr;		//���_�V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob = nullptr;		//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob = nullptr;	//�G���[�I�u�W�F�N�g

	//�p�C�v���C���X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
	// ���[�g�V�O�l�`���̃V���A���C�Y
	ComPtr<ID3DBlob> rootSigBlob = nullptr;

public://�A�N�Z�b�T

	DirectXCommon* GetDxCommon() { return dxCommon_; }
	ComPtr<ID3D12Resource> GetTextureBuffer() { return texbuff; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVHandle() { return srvHandle; }
};

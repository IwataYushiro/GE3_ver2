#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>

class Model
{
private://�G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private://�T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};

public://�ÓI�����o�֐�
	//OBJ�t�@�C������3D���f����ǂݍ���
	static Model* LoadFromOBJ();

private://�����o�ϐ�
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;

public://�A�N�Z�b�T�u����

private://�����o�֐�
	//OBJ�t�@�C������3D���f����ǂݍ���(����J)
	Model* LoadFromOBJInternal();
};


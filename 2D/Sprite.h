#pragma once
#include "SpriteCommon.h"
#include "Input.h"
#include <DirectXMath.h>

//1��1���̃X�v���C�g�N���X

class Sprite
{
public: // �����o�֐�
	//�G�C���A�X�e���v���[�g�Ƃ��ŐF�X�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private://�\���̗�
	//�}�e���A��
	struct ConstBufferDataMaterial
	{
		XMFLOAT4 color;
	};

	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	ComPtr<ID3D12Resource> constBuffMaterial = nullptr;
	//�}�b�s���O�p�̃|�C���^
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	//�}�e���A��
	struct ConstBufferDataTransform
	{
		XMMATRIX mat;	//3D�ϊ��s��
		
	};
//�A�t�B���ϊ����
		XMFLOAT2 scale = { 1.0f,1.0f};
		float rotationZ = 0.0f;
		XMFLOAT2 position = { 0.0f,0.0f};
		//���[���h�ϊ��s��
		XMMATRIX matWorld=DirectX::XMMatrixIdentity();
		

	//�萔�o�b�t�@��GPU���\�[�X�̃|�C���^
	ComPtr<ID3D12Resource> constBuffTransform = nullptr;
	//�}�b�s���O�p�̃|�C���^
	ConstBufferDataTransform* constMapTransform = nullptr;

	//���_�f�[�^�\����
	struct Vertex
	{
		XMFLOAT3 pos;		//xyz���W
		XMFLOAT2 uv;		//uv���W
	};


public://�����o�֐�

	//������
	void Initialize(SpriteCommon* spCommon, Input* input);
	//�X�V
	void Update();
	//�`��
	void Draw();

	//�萔�o�b�t�@
	//�}�e���A��
	void CreateConstBufferMaterial();
	//3D���W
	void CreateConstBufferTransform();
private://�����o�ϐ�
	//���_��
	static const size_t verticesCount = 4;

	//���_�f�[�^
	Vertex vertices[verticesCount] = {
		{{  0.0f,100.0f,0.0f},{0.0f,1.0f}},	//����
		{{  0.0f,  0.0f,0.0f},{0.0f,0.0f}},		//����
		{{100.0f,100.0f,0.0f},{1.0f,1.0f}},	//�E��
		{{100.0f,  0.0f,0.0f},{1.0f,0.0f}},	//�E��
	};

	//�C���v�b�g
	Input* input_ = nullptr;
	SpriteCommon* spCommon_ = nullptr;
	
	//���_�o�b�t�@�̃��\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
};

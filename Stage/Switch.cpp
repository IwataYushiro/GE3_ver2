#include "Switch.h"

using namespace DirectX;

void Switch::Initialize(Model* model, Object3d* obj) {
	// ���f���ǂݍ���
	model_ = model;
	obj_ = obj;

	isFlag_ = false;
}

void Switch::Update() {
	isFlag_ = false;
}

void Switch::Trans()
{

	XMMATRIX world;
	//�s��X�V
	world = XMMatrixIdentity();
	XMMATRIX matWorld = XMMatrixIdentity();

	XMMATRIX matScale = XMMatrixScaling(obj_->GetScale().x, obj_->GetScale().y, obj_->GetScale().z);

	XMMATRIX matRot = XMMatrixRotationZ(obj_->GetRotation().z)
		* XMMatrixRotationX(obj_->GetRotation().x) * XMMatrixRotationY(obj_->GetRotation().y);

	XMMATRIX matTrans = XMMatrixTranslation(obj_->GetPosition().x,
		obj_->GetPosition().y, obj_->GetPosition().z);

	//����
	matWorld = matScale * matRot * matTrans;

	world = matWorld;
	obj_->SetWorld(world);

}

void Switch::Draw() {
	obj_->Draw();
}

void Switch::OnCollisionSwitch() {
	isFlag_ = true;
}

void Switch::SetPosition(XMFLOAT3 pos)
{
	// �X�P�[���ݒ�
	scale_ = { 2.0f, 2.0f, 2.0f };
	// ���W�ݒ�
	pos_ = pos;
	// �s��X�V
	Trans();

}

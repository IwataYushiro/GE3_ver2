#include "Player.h"
#include <DirectXMath.h>
#include <cassert>

using namespace DirectX;

Player::~Player() {
	//�I�v�V�����̉��
	delete model_;
	delete obj_;
}

void Player::Initialize(Model* model, Object3d* obj, Input* input) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	obj_ = obj;

	modelBullet_ = Model::LoadFromOBJ("playerbullet");
	objBullet_ = Object3d::Create();

	objBullet_->SetModel(modelBullet_);

	//�V���O���g���C���X�^���X���擾
	this->input_ = input;

	//���[���h�ϊ��̏�����
	pos = { 0.0f,0.0f,600.0f };
	obj_->SetPosition(pos);
	
}

void Player::Update() {

	if (!isDead_) {
		//���S�t���O�̗������e���폜
		bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

		//�ړ�����
		Move();
		//���񏈗�
		Rotate();
		//�U������
		Attack();

		//�e�X�V
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Update();
		}

		//�ړ�����
		MoveLimit();
	}

	obj_->Update();
}

void Player::Draw() {
	if (!isDead_) {
		obj_->Draw();

		//�e�`��
		for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
			bullet->Draw();
		}

	}
}

//�ړ�����
void Player::Move() {

	XMFLOAT3 move = obj_->GetPosition();
	float moveSpeed = 3.0f;

	//�L�[�{�[�h���͂ɂ��ړ�����
	XMMATRIX matTrans = XMMatrixIdentity();
	if (input_->PushKey(DIK_A)) {
		move.x -= moveSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += moveSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.y += moveSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y -= moveSpeed;
	}

	obj_->SetPosition(move);
	
}

//���񏈗�
void Player::Rotate() {

	XMFLOAT3 angle = obj_->GetRotation();
	float angleSpeed = 0.1f;

	if (input_->PushKey(DIK_Q)) {
		angle.y -= angleSpeed;
	}
	if (input_->PushKey(DIK_E)) {
		angle.y += angleSpeed;
	}

	obj_->SetRotation(angle);
}

//�U������
void Player::Attack() {

	if (input_->PushKey(DIK_SPACE)) {
		//�e�̑��x
		const float kBulletSpeed = 10.0f;
		XMFLOAT3 velocity(0.0f, 0.0f, kBulletSpeed);

		XMMATRIX matVec = XMMatrixIdentity();
		matVec.r[0].m128_f32[0] = velocity.x;
		matVec.r[0].m128_f32[1] = velocity.y;
		matVec.r[0].m128_f32[2] = velocity.z;
		matVec.r[0].m128_f32[3] = 0.0f;
		
		matVec *= obj_->GetWorld();
		obj_->SetWorld(matVec);
		
		velocity.x = matVec.r[0].m128_f32[0];
		velocity.y = matVec.r[0].m128_f32[1];
		velocity.z = matVec.r[0].m128_f32[2];
		
		//���L�����̍��W���R�s�[
		XMFLOAT3 position = obj_->GetPosition();

		//�e�𐶐���������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelBullet_,objBullet_, position, velocity);

		//�e��o�^
		bullets_.push_back(std::move(newBullet));
		//���郁�����̏��L��������unique_ptr�͂�����������݂ł��Ȃ�
		//���̏��L�������n���邽�߂̋@�\�� std::move()
	}
}

void Player::MoveLimit() {
	
	XMMATRIX world;
	//�s��X�V
	world = XMMatrixIdentity();
	XMMATRIX matWorld =XMMatrixIdentity();

	XMMATRIX matScale = XMMatrixScaling(obj_->GetScale().x, obj_->GetScale().y, obj_->GetScale().z);

	XMMATRIX matRot = XMMatrixRotationZ(obj_->GetRotation().z)
		*XMMatrixRotationX(obj_->GetRotation().x)*XMMatrixRotationY(obj_->GetRotation().y);

	XMMATRIX matTrans = XMMatrixTranslation(obj_->GetPosition().x,
		obj_->GetPosition().y, obj_->GetPosition().z);

	//����
	matWorld *= matScale *= matRot *= matTrans;

	world = matWorld;
	obj_->SetWorld(world);

}

//���[���h���W���擾
XMFLOAT3 Player::GetWorldPosition() {

	//���[���h���W���擾
	XMFLOAT3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = obj_->GetPosition().x;
	worldPos.y = obj_->GetPosition().y;
	worldPos.z = obj_->GetPosition().z;

	return worldPos;
}

//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
void Player::OnCollision() {
	life_--;
	if (life_ <= 0) {
		isDead_ = true;
	}
}

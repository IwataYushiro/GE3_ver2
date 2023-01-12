#pragma once
#include "Input.h"
#include "Model.h"
#include "Object3d.h"
#include <DirectXMath.h>
#include <list>
#include <memory>

//���@�N���X�̑O���錾
class Player;
//�Q�[���V�[����
class MyGame;
//�G
class Enemy {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	~Enemy();
	//�e���ˊԊu
	static const int kFireIntervalStage1 = 40;
	//������
	void Initialize(Model* model, Object3d* obj, Input* input);

	//���Z�b�g����
	void Reset();
	void EndingPosition();
	//�p�����[�^
	void Stage1Parameter();
	//�X�V
	void Update();
	//�e����
	void Fire();
	//���[���h���W���擾
	Vector3 GetWorldPosition();
	//�`��
	void DrawStage1();

	//��ԕω��p�̍X�V�֐�
	//�ڋ�
	void UpdateApproachStage1();
	//�U��
	void UpdateAttackStage1();
	//���E
	void UpdateLeave();

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollisionPlayer();
	
	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() { return enemyBullets_; }

private:
	
	//�e
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//�C���v�b�g
	Input* input_ = nullptr;
	
	//���f��
	Model* model_ = nullptr;	
	Model* modelBullet_ = nullptr;

	Object3d* obj_ = nullptr;
	Object3d* objBullet_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	//�s���t�F�[�Y
	enum class Phase {
		//��������X�e�[�W1
		ApproachStage1, //�ڋ�
		AttackStage1,   //�U��

		//�S��
		Leave, //���E
		//�G���f�B���O
		end,
	};

	//�t�F�[�Y
	Phase phase_;
	//�e���˃^�C�}�[
	int32_t fireTimer = 0;
	//�|�W�V����
	XMFLOAT3 pos;
	//�A���O��
	XMFLOAT3 angle;

	//���@
	Player* player_ = nullptr;
	//�Q�[���V�[��
	MyGame* gameScene_ = nullptr;

	//���S�t���O�ƃ��C�t
	bool isDead_;
	int life_;

	//���]�t���O
	bool isReverse_ = false;

public:
	bool IsDead() const { return isDead_; }
	void SetPlayer(Player* player) { player_ = player; }
};
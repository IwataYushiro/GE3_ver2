#pragma once
#include <DirectXMath.h>
#include <sstream>
#include "Model.h"
#include "Object3d.h"
#include "Switch.h"

class Stage {
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // �萔
	static const int STAGE_WIDTH = 20;
	static const int STAGE_HEIGHT = 20;

public:
	// ��
	enum STAGE {
		NONE,		// ��
		BLOCK,		// �n��, ��
		SWITCHR,	// �X�C�b�`R
		WALLR,		// �������R
		SWITCHB,	// �X�C�b�`B
		WALLB,		// �������B
		GOAL,		// �S�[��

		NONE2,
		NONE3,
	};

	// �\����
	struct StageData {
		XMFLOAT3 scale_; // �X�P�[��
		XMFLOAT3 pos_;	// ���W
		int type_;	// �u���b�N�̎��
		int line_;
		int row_;
	};

public:
	// �f�X�g���N�^
	~Stage();

	// ������
	void Initialize(Model* model,Object3d* obj);

	// �X�e�[�W������
	void StageInitialize(const std::string stageNum);

	// �X�V
	void Update();
	//�]��
	void Trans();
	// �`��
	void Draw();

	// �����̃u���b�N�𔻕ʂ���
	void CheckBlock(int line, int row);

	// ������͂ݏo���Ă��邩
	bool CheckFloorBlock(int line, int row);

	// ���W�Q�b�^�[
	XMFLOAT3 GetBlockPosition(int line, int row);

private:
	// �X�e�[�W���̓ǂݍ���
	void LoadFloorBlock();

	// �X�e�[�W�t�@�C���ǂݍ���
	void LoadStageData(const std::string stageNum);

	// �X�e�[�W�ǂݍ���
	void LoadStageCommands();

	// �u���b�N������
	void InitializeStageBlock(std::unique_ptr<StageData>& block, XMFLOAT3 pos, int line, int row);

	// ���X�g�Ƀu���b�N��ǉ�
	void PushStageBlockList(std::list<std::unique_ptr<StageData>>& blocks_, int type, int line, int row, float depth);

private:
	// ���f��
	Model* model_ = nullptr;
	Model* modelFloor_ = nullptr;
	Model* modelSwitchR_ = nullptr;
	Model* modelSwitchB_ = nullptr;
	Model* modelWallR_ = nullptr;
	Model* modelWallB_ = nullptr;
	Model* modelGoal_ = nullptr;

	Object3d* obj_ = nullptr;
	Object3d* objFloor_ = nullptr;
	Object3d* objSwitchR_ = nullptr;
	Object3d* objSwitchB_ = nullptr;
	Object3d* objWallR_ = nullptr;
	Object3d* objWallB_ = nullptr;
	Object3d* objGoal_ = nullptr;
	// �e�N�X�`���n���h��
	int32_t textureHandle_ = 0u;

	// �t�@�C���R�}���h
	std::stringstream stageCommands;
	// ���[���h�ϊ��f�[�^
	std::list<std::unique_ptr<StageData>> stageBlocks_;
	std::list<std::unique_ptr<StageData>> floorBlocks_;

	Switch* switchR_ = nullptr;
	Switch* switchB_ = nullptr;

	// �u���b�N�̔{��(Scale)
	float magnification_ = 2.0f;
	// �u���b�N�̔��a���a
	float radius_ = 2.0f;
	// �S�[���t���O
	bool isGoal_ = false;
	bool isSwitchDrawR_ = false;
	bool isSwitchDrawB_ = false;

public: // �A�N�Z�b�T
	float GetRadius() { return radius_; }
	bool GetIsGoal() { return isGoal_; }
};
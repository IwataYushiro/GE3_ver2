#include "Stage.h"
#include <cassert>
#include <fstream>

using namespace DirectX;

Stage::~Stage() {
	delete modelFloor_;
	delete modelGoal_;
	delete modelSwitchR_;
	delete modelSwitchB_;
	delete modelWallR_;
	delete modelWallB_;

	delete objFloor_;
	delete objSwitchR_;
	delete objSwitchB_;
	delete objWallR_;
	delete objWallB_;
	delete objGoal_;
	
	delete switchR_;
	delete switchB_;
}

void Stage::Initialize(Model* model, Object3d* obj) {
	obj_ = obj;
	objFloor_ = Object3d::Create();
	objSwitchR_= Object3d::Create();
	objSwitchB_= Object3d::Create();
	objWallR_= Object3d::Create();
	objWallB_= Object3d::Create();
	objGoal_= Object3d::Create();

	// ���f���ǂݍ���
	model_ = model;
	modelFloor_ = Model::LoadFromOBJ("floor");
	modelSwitchR_ = Model::LoadFromOBJ("rswitch");
	modelSwitchB_ = Model::LoadFromOBJ("bswitch");
	modelWallR_ = Model::LoadFromOBJ("cubeR");
	modelWallB_ = Model::LoadFromOBJ("cubeB");
	modelGoal_ = Model::LoadFromOBJ("goal");

	// �X�C�b�`
	switchR_ = new Switch();
	switchB_ = new Switch();
	switchR_->Initialize(modelSwitchR_, objSwitchR_);
	switchB_->Initialize(modelSwitchB_, objSwitchB_);

	// �X�e�[�W�̏���������
	LoadFloorBlock();
}

void Stage::StageInitialize(const std::string stageNum) {
	// �ŏ��Ɏc���Ă���v�f���폜
	stageBlocks_.clear();

	isSwitchDrawR_ = false;
	isSwitchDrawB_ = false;

	// �o�b�t�@���N���A
	stageCommands.str("");
	// ��Ԃ��N���A
	stageCommands.clear(std::stringstream::goodbit);

	// �X�e�[�W�p�t�@�C���ǂݍ���
	LoadStageData(stageNum);
	// �X�e�[�W�t�@�C���Ŋe�v�f��ݒ�
	LoadStageCommands();

	isGoal_ = false;
}

void Stage::Update() {
	if (switchR_->GetFlag()) {
		for (std::unique_ptr<StageData>& block : stageBlocks_) {
			if (block->type_ == WALLR) {
				block->type_ = NONE2;
			}
		}
	}
	else if (!switchR_->GetFlag()) {
		for (std::unique_ptr<StageData>& block : stageBlocks_) {
			if (block->type_ == NONE2) {
				block->type_ = WALLR;
			}
		}
	}

	if (switchB_->GetFlag()) {
		for (std::unique_ptr<StageData>& block : stageBlocks_) {
			if (block->type_ == WALLB) {
				block->type_ = NONE3;
			}
		}
	}
	else if (!switchB_->GetFlag()) {
		for (std::unique_ptr<StageData>& block : stageBlocks_) {
			if (block->type_ == NONE3) {
				block->type_ = WALLB;
			}
		}
	}

	switchR_->Update();
	switchB_->Update();

	isGoal_ = false;
}
void Stage::Trans()
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

void Stage::Draw() {
	// �X�e�[�W�`��
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		if (block->type_ == BLOCK) {
			// �Ǖ`��
			obj_->Draw();
		}
		else if (block->type_ == WALLR) {
			// �ԕǕ`��
			objWallR_->Draw();
		}
		else if (block->type_ == WALLB) {
			// �Ǖ`��
			objWallB_->Draw();
		}
		else if (block->type_ == GOAL) {
			// �S�[���`��
			block->pos_.y = -15.5f;
			objGoal_->Draw();
		}
	}

	// ���`��
	for (std::unique_ptr<StageData>& block : floorBlocks_) {
		objFloor_->Draw();
	}

	// �X�C�b�`�`��
	if (isSwitchDrawR_) switchR_->Draw();
	if (isSwitchDrawB_) switchB_->Draw();
}

void Stage::LoadStageData(const std::string stageNum) {
	// �t�@�C��
	std::ifstream file;
	// �p�X���擾
	const std::string name = "stage";
	const std::string filename = name + stageNum + ".csv";
	const std::string directoryPath = "Resources/" + name + "/";
	// �t�@�C�����J��
	file.open(directoryPath + filename);
	assert(file.is_open());
	// �t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	stageCommands << file.rdbuf();

	// �t�@�C�������
	file.close();
}

void Stage::LoadStageCommands() {
	// 1�s���̕����������ϐ�
	std::string line;
	// �}�b�v�`�b�v�p�ϐ�
	int mapLine = 0;	// X
	int mapRow = 0;	// Y

	// �R�}���h���s���[�v
	while (getline(stageCommands, line)) {
		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);
		// ������
		std::string word;
		// ,��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');

		// "//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			// �R�����g�s��ǂݔ�΂�
			continue;
		}

		while (mapLine != STAGE_WIDTH) {
			// �R�}���h�ǂݍ���
			if (word.find("NONE") == 0 || word.find("0") == 0 || word.find("7") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, NONE, mapLine, mapRow, -10.0f);
				// �C���N�������g
				mapLine++;
			}
			else if (word.find("BLOCK") == 0 || word.find("1") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, BLOCK, mapLine, mapRow, -10.0f);
				// �C���N�������g
				mapLine++;
			}
			else if (word.find("SWITCH") == 0 || word.find("2") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, SWITCHR, mapLine, mapRow, -10.0f);
				// �C���N�������g
				mapLine++;
			}
			else if (word.find("WALL") == 0 || word.find("3") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, WALLR, mapLine, mapRow, -10.0f);
				// �C���N�������g
				mapLine++;
			}
			else if (word.find("SWITCH") == 0 || word.find("4") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, SWITCHB, mapLine, mapRow, -10.0f);
				// �C���N�������g
				mapLine++;
			}
			else if (word.find("WALL") == 0 || word.find("5") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, WALLB, mapLine, mapRow, -10.0f);
				// �C���N�������g
				mapLine++;
			}
			else if (word.find("GOAL") == 0 || word.find("6") == 0) {
				// �X�e�[�W�̃u���b�N��ǉ�
				PushStageBlockList(stageBlocks_, GOAL, mapLine, mapRow, -10.0f);
				// �C���N�������g
				mapLine++;
			}
			// ���̓��e��
			getline(line_stream, word, ',');
		}
		// �}�b�v�`�b�vLine��20�𒴂����烊�Z�b�g����Row���C���N�������g
		if (mapLine == STAGE_WIDTH) {
			mapLine = 0;
			mapRow++;
		}
	}
}

void Stage::LoadFloorBlock() {
	for (int i = 0; i < STAGE_HEIGHT; i++) {
		for (int j = 0; j < STAGE_WIDTH; j++) {
			// �X�e�[�W�̃u���b�N��ǉ�
			PushStageBlockList(floorBlocks_, BLOCK, j, i, -14.0f);
		}
	}
}

void Stage::InitializeStageBlock(std::unique_ptr<StageData>& block, XMFLOAT3 pos, int line, int row) {
	
	// �X�P�[���ݒ�
	block->scale_ = { magnification_, magnification_, magnification_ };
	// ���W�ݒ�
	block->pos_ = pos;

	// �s��X�V
	Trans();

	block->line_ = line;
	block->row_ = row;
}

void Stage::PushStageBlockList(std::list<std::unique_ptr<StageData>>& blocks_, int type, int line, int row, float depth) {
	// ���X�g�ɓ���邽�߂ɐV�����錾
	std::unique_ptr<StageData> newBlock = std::make_unique<StageData>();
	// �u���b�N�̎��
	newBlock->type_ = type;
	// ���W
	XMFLOAT3 pos;
	pos.x = 2.0f + (4.0f * line);
	pos.y = depth;
	pos.z = 78.0f - (4.0f * row);

	// ����������
	InitializeStageBlock(newBlock, pos, line, row);
	// ���X�g�ɒǉ�
	blocks_.push_back(std::move(newBlock));

	if (type == SWITCHR) {
		pos.x -= 2.0f;
		pos.z += 2.0f;
		switchR_->SetPosition(pos);
		isSwitchDrawR_ = true;
	}
	if (type == SWITCHB) {
		pos.x -= 2.0f;
		pos.z += 2.0f;
		switchB_->SetPosition(pos);
		isSwitchDrawB_ = true;
	}
}

void Stage::CheckBlock(int line, int row) {
	// �͈�for
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		// NONE�͕Ԃ��Ȃ�
		if (block->type_ == SWITCHR) {
			// �w�肵���ԍ��ɍ��������W��Ԃ�
			if (block->line_ == line && block->row_ == row) {
				switchR_->OnCollisionSwitch();
			}
		}
		else if (block->type_ == SWITCHB) {
			// �w�肵���ԍ��ɍ��������W��Ԃ�
			if (block->line_ == line && block->row_ == row) {
				switchB_->OnCollisionSwitch();
			}
		}
		else if (block->type_ == GOAL) {
			// �w�肵���ԍ��ɍ��������W��Ԃ�
			if (block->line_ == line && block->row_ == row) {
				isGoal_ = true;
			}
		}
	}
}

bool Stage::CheckFloorBlock(int line, int row) {
	if (line < 0 || line > 19 || row < 0 || row > 19) {
		return true;
	}
	return false;
}

XMFLOAT3 Stage::GetBlockPosition(int line, int row) {
	// �͈�for
	for (std::unique_ptr<StageData>& block : stageBlocks_) {
		// �u���b�N�ƕǂ̎��͕Ԃ�
		if (block->type_ == BLOCK || block->type_ == WALLR || block->type_ == WALLB) {
			// �w�肵���ԍ��ɍ��������W��Ԃ�
			if (block->line_ == line && block->row_ == row) {
				return block->pos_;
			}
		}
	}
	// �Ȃ�������0��Ԃ�
	return XMFLOAT3(0.0f, 0.0f, 0.0f);
}
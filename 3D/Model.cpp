#include "Model.h"
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <Windows.h>

using namespace std;

//OBJ�t�@�C������3D���f����ǂݍ���
Model* Model::LoadFromOBJ()
{
	//�V����Model�^�̃C���X�^���X�̃��������m��
	Model* model = new Model();
	//OBJ�t�@�C������̃f�[�^�ǂݍ���
	model->LoadFromOBJInternal();
	//�ǂݍ��񂾃f�[�^�����Ɋe��o�b�t�@����

}

//OBJ�t�@�C������3D���f����ǂݍ���(����J)
Model* Model::LoadFromOBJInternal() {
	//�t�@�C���X�g���[��
	std::ifstream file;
	//obj�t�@�C�����J��
	const string modelname = "triangle_mat";
	const string filename = modelname + ".obj";					//"triangle_mat.obj"
	const string directoryPath = "Resources/" + modelname + "/";//"Resources/triangle_mat/"

	file.open(directoryPath + filename);//"Resources/triangle_mat/triangle_mat.obj"
	//�t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail())
	{
		assert(0);
	}

	vector<XMFLOAT3> positions;					//���_���W
	vector<XMFLOAT3> normals;					//�@���x�N�g��
	vector<XMFLOAT2> texcoords;					//�e�N�X�`��UV
	//1�s���ǂݍ���
	string line;
	while (getline(file, line))
	{
		//1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		//�擪������mtllib�Ȃ�}�e���A��
		if (key == "mtllib")
		{
			//�}�e���A���̃t�@�C�����ǂݍ���
			string filename;
			line_stream >> filename;
			//�}�e���A���ǂݍ���
			LoadMaterial(directoryPath, filename);
		}
		//�擪������v�Ȃ璸�_���W
		if (key == "v")
		{
			//X,Y,Z���W�ǂݍ���
			XMFLOAT3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//���W�f�[�^�ɒǉ�
			positions.emplace_back(position);

		}
		//�擪������vt�Ȃ�e�N�X�`��
		if (key == "vt")
		{
			//U,V�����ǂݍ���
			XMFLOAT2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;

			//V�������]
			texcoord.y = 1.0f - texcoord.y;
			//�e�N�X�`�����W�f�[�^�ɒǉ�
			texcoords.emplace_back(texcoord);

		}
		//�擪������vn�Ȃ�@���x�N�g��
		if (key == "vn")
		{
			//X,Y,Z�����ǂݍ���
			XMFLOAT3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;

			//�@���x�N�g���f�[�^�ɒǉ�
			normals.emplace_back(normal);
		}

		//�擪������f�Ȃ�|���S��(�O�p�`)
		if (key == "f")
		{
			//���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			string index_string;
			while (getline(line_stream, index_string, ' '))
			{
				//���_�C���f�b�N�X1���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexTexcoord, indexNormal;
				index_stream >> indexPosition;
				//�X���b�V�����΂�
				index_stream.seekg(1, ios_base::cur);
				index_stream >> indexTexcoord;
				//�X���b�V�����΂�
				index_stream.seekg(1, ios_base::cur);
				index_stream >> indexNormal;

				//���_�f�[�^�̒ǉ�
				VertexPosNormalUv vertex{};
				vertex.pos = positions[indexPosition - 1];
				vertex.normal = normals[indexNormal - 1];
				vertex.uv = texcoords[indexTexcoord - 1];
				vertices.emplace_back(vertex);

				//�C���f�b�N�X�f�[�^�̒ǉ�

				//���_�C���f�b�N�X�ɒǉ�
				indices.emplace_back((unsigned short)indices.size());
			}
		}
	}
	//�t�@�C�������
	file.close();

}
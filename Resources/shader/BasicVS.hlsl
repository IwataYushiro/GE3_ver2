#include "Basic.hlsli"

VSOutput main(float4 pos : POSITION,float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	VSOutput output;//�s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos	= mul(mat,pos);
	output.normal = normal;
	output.uv		= uv;
	return output;
}
//�@return pos + float4(<-X�I�t�Z�b�g+>,Y�I�t�Z�b�g,0,0) �w�肵�����������
//�@return pos * float4(X�g��, Y�g��, Y�k��, Y�k��) �w�肵�������g�k�����
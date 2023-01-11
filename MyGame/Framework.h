#pragma once

//�Q�[���S��
class Framework
{
public://�����o�֐�

	
	virtual ~Framework() = default;

	virtual void Initialize();

	virtual void Update();

	virtual void Draw() = 0;

	virtual void Finalize();

	virtual bool IsEndRequest() { return EndGame_; }

private:
	//�Q�[���I���t���O
	bool EndGame_ = false;
};
#pragma once
#include <array>

typedef std::array<char, 256> KEY_FLAG;

//���݂̉�����������
enum KEY_TYPE {
	KEY_TYPE_NOW,	//�������Ă���
	KEY_TYPE_OLD,	//�O�ڰтɉ�����
	KEY_TYPE_MAX
};

class Controller
{
public:
	Controller();
	~Controller();
	//���ݏ��̍X�V
	bool Update(void);
	//���ݏ��̎擾�֐�
	const KEY_FLAG &GetButtonInfo(KEY_TYPE type) const;

private:
	//���ݏ��̊i�[�ꏊ
	KEY_FLAG key;
	//�O�ڰтɉ��������ݏ��̊i�[�ꏊ
	KEY_FLAG keyOld;
};


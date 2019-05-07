#pragma once
#include <array>

typedef std::array<char, 256> KEY_FLAG;

//���݂̉�����������
enum KEY_TYPE {
	KEY_TYPE_NOW,	//������
	KEY_TYPE_OLD,	//�O�ڰтɉ���
	KEY_TYPE_MAX
};

// �ް��߯�ނ̉�����������
enum PAD_INPUT
{
	PAD_INPUT_OLD,	// �O�ڰтɉ���
	PAD_INPUT_NOW,	// ������
	PAD_INPUT_MAX
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
	// �ް��߯�ނ����ݏ��̎擾�֐�
	const PAD_INPUT &GetPadButtonInfo(PAD_INPUT inputType) const;

private:
	//���ݏ��̊i�[�ꏊ
	KEY_FLAG key;
	//�O�ڰтɉ��������ݏ��̊i�[�ꏊ
	KEY_FLAG keyOld;

	// ���ݏ��̊i�[
	PAD_INPUT PadInput;
	// �O�ڰтɉ������̊i�[
	PAD_INPUT PadInputOld;
};


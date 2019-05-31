#pragma once
#include <array>

// ��ׂ̈ړ�����
enum CAMERA_DIRECTION
{
	CAMERA_LEFT,
	CAMERA_RIGHT,
	CAMERA_UP,
	CAMERA_DOWN,
	CAMERA_MAX
};

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


typedef std::array<char, 256> KEY_FLAG;
typedef std::array<bool[CAMERA_MAX], KEY_TYPE_MAX> KEY_INPUT;

class Controller
{
public:
	Controller();
	~Controller();
	//���ݏ��̍X�V
	bool Update(void);
	//���ݏ��̎擾�֐�
	const KEY_INPUT& GetButtonInfo(void) const;
	//
	const KEY_FLAG &GetKeyButtonInfo(KEY_TYPE type) const;

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

	KEY_INPUT input;
	KEY_INPUT inputOld;
};


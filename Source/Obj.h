#pragma once
#include <string>
#include <map>
#include "Controller.h"
#include "AddList.h"
#include "VECTOR2.h"

// �e��޼ު�Ă̕���
enum DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};

// ��Ұ��݊֌W
enum ANIMATION
{
	ANIM_START,		//�J�n�ʒu
	ANIM_FLAME,		//�g�p�ϐ�
	ANIM_INTERVAL,	//
	ANIM_CNT,
	ANIM_MAX
};


class Obj
{
public:
	Obj();
	~Obj();
	virtual void Draw(void);
	//�ړ��i�e��ׂňړ������R�ɂ������̂ŏ������z�֐��j
	virtual void Move(const Controller& controll, WeakList objlist) = 0;
	//�e��׸���̈ړ�
	void Update(const Controller& controll, WeakList objlist);
	//�e��׸���̱�Ұ��݂Ɋւ��鏉����
	bool Init(std::string filename, VECTOR2 divcnt, VECTOR2 divsize);

	//��Ұ��݂̒ǉ�
	bool AddAnim(std::string animationName, int x, int y, int flame, int val);
	//��Ұ��݂̾��
	bool SetAnim(std::string animationName);
	//��Ұ��݂̖��O�擾
	std::string &GetAnimation(void)
	{
		return AnimationName;
	}

	// �w��̵�޼ު�Ă�ؽĂ�������׸ނ�Ԃ�
	bool Getdeleteflag(void)
	{
		return deleteflag;
	}
	// �w��̵�޼ު�Ă�ؽĂ������= true
	// �w��̵�޼ު�Ă������Ȃ�= false
	virtual void Delete(void)
	{
		deleteflag = true;
	}
private:
	//�摜�̖��O
	std::string ImageName;
	//�e��Ұ��݂̖��O
	std::string AnimationName;
	//��Ұ��݂Ɋւ����ڰѓ��̊i�[
	std::map<std::string, int[MAX]> animTbl;
	//��Ұ��ݶ���
	unsigned int AniCnt;
	bool deleteflag;

	//�摜�̕�������
	VECTOR2 DivSize;
	//�摜�̕�����
	VECTOR2 DivCnt;

protected:
	//��ׂ������Ă������
	DIR dir;
	//�e��ׂ��߼޼�݂̊i�[�ϐ�
	VECTOR2 pos;

	//�߼޼�ݾ��
	void SetPos(VECTOR2 pos)
	{
		Obj::pos = pos;
	}
};


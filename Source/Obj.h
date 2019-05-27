#pragma once
#include <string>
#include <map>
#include "NUM_TYPE.h"
#include "Map.h"
#include "Controller.h"
#include "AddList.h"
#include "VECTOR2.h"




// �e��޼ު�Ă̕���
enum DIR
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_MAX
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

// ��޼ު�Ă�����
enum OBJ_TYPE
{
	// ��ި�Ķ���
	TYPE_CURSOR,
	// ��ڲ԰
	TYPE_PREY,
	// �S
	TYPE_IT,
	TYPE_MAX
};




class Obj
{
public:
	Obj();
	~Obj();
	// �P�Ȃ�`��֐�
	virtual void Draw(void);

	// ���߂�id���̕`��֐�
	void Draw(unsigned int id);
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
	
	//�߼޼�ݎ擾
	const VECTOR2& GetPos(void)
	{
		return pos;
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
	virtual int GetPlayerCnt(void)
	{
		return playerCnt;
	}

	// ��޼ު�Ă����ߎ擾�֐�
	virtual bool GetType(OBJ_TYPE type) = 0;

	// ��޼ު�ĉ�������׸���̎擾
	virtual TYPE_NUM GetTypeNum(void) { return typeObjNum; };

	// individualsMapPos�̎擾(typeNum�ɂ���Ēl���Ⴄ�̂ŁA�������z�֐���)
	virtual VECTOR2& GetIndividualsMapPos(void) = 0;

private:
	//�摜�̖��O
	std::string ImageName;
	//�e��Ұ��݂̖��O
	std::string AnimationName;
	//��Ұ��݂Ɋւ����ڰѓ��̊i�[
	std::map<std::string, int[DIR_MAX]> animTbl;
	
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

	// ��׸���I�����ɑI��������ׂ��޼ު�Ă��邽�߂̕ϐ�
	TYPE_NUM typeObjNum;
	// ��׸���𐶐���������(1=1P 2 =2P 3 =3P)
	int playerCnt;

	// ϯ�ߑS��(12000 x 8640)����ɂ�����ذݒP�ʂł��߼޼��
	VECTOR2 individualsMapPos;

	// ����߼޼��(player(�S���܂߂�))
	VECTOR2 cameraPos;

	//��Ұ��ݶ���
	unsigned int AniCnt;

	// �ړ����݂̉����׸�
	int InputNow[DIR_MAX];
	// �O�ڰт̉����׸�
	int InputOld[DIR_MAX];

	
};


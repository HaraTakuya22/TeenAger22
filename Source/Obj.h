#pragma once
#include <string>
#include <map>
#include "Controller.h"
#include "AddList.h"
#include "VECTOR2.h"

// 各ｵﾌﾞｼﾞｪｸﾄの方向
enum DIR
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_MAX
};

// ｱﾆﾒｰｼｮﾝ関係
enum ANIMATION
{
	ANIM_START,		//開始位置
	ANIM_FLAME,		//使用ｺﾏ数
	ANIM_INTERVAL,	//
	ANIM_CNT,
	ANIM_MAX
};

// ｵﾌﾞｼﾞｪｸﾄのﾀｲﾌﾟ
enum OBJ_TYPE
{
	// ｴﾃﾞｨｯﾄｶｰｿﾙ
	TYPE_CURSOR,
	// ﾌﾟﾚｲﾔｰ
	TYPE_PREY,
	// 鬼
	TYPE_IT,
	TYPE_MAX
};


class Obj
{
public:
	Obj();
	~Obj();
	// 単なる描画関数
	virtual void Draw(void);

	// ﾁｯﾌﾟのid毎の描画関数
	void Draw(unsigned int id);
	//移動（各ｷｬﾗで移動を自由にしたいので純粋仮想関数）
	virtual void Move(const Controller& controll, WeakList objlist) = 0;
	//各ｷｬﾗｸﾀｰの移動
	void Update(const Controller& controll, WeakList objlist);
	//各ｷｬﾗｸﾀｰのｱﾆﾒｰｼｮﾝに関する初期化
	bool Init(std::string filename, int posx, int posy, VECTOR2 divcnt, VECTOR2 divsize);

	//ｱﾆﾒｰｼｮﾝの追加
	bool AddAnim(std::string animationName, int x, int y, int flame, int val);
	//ｱﾆﾒｰｼｮﾝのｾｯﾄ
	bool SetAnim(std::string animationName);
	//ｱﾆﾒｰｼｮﾝの名前取得
	std::string &GetAnimation(void)
	{
		return AnimationName;
	}
	//ﾎﾟｼﾞｼｮﾝ取得
	const VECTOR2 GetPos(void)
	{
		return pos;
	}
	// 指定のｵﾌﾞｼﾞｪｸﾄをﾘｽﾄから消すﾌﾗｸﾞを返す
	bool Getdeleteflag(void)
	{
		return deleteflag;
	}
	// 指定のｵﾌﾞｼﾞｪｸﾄをﾘｽﾄから消す= true
	// 指定のｵﾌﾞｼﾞｪｸﾄを消さない= false
	virtual void Delete(void)
	{
		deleteflag = true;
	}

	// ｵﾌﾞｼﾞｪｸﾄのﾀｲﾌﾟ取得関数
	virtual bool GetType(OBJ_TYPE type) = 0;

private:
	//画像の名前
	std::string ImageName;
	//各ｱﾆﾒｰｼｮﾝの名前
	std::string AnimationName;
	//ｱﾆﾒｰｼｮﾝに関するﾌﾚｰﾑ等の格納
	std::map<std::string, int[DIR_MAX]> animTbl;
	
	bool deleteflag;

	//画像の分割ｻｲｽﾞ
	VECTOR2 DivSize;
	//画像の分割数
	VECTOR2 DivCnt;

protected:
	//ｷｬﾗが向いている方向
	DIR dir;
	//各ｷｬﾗのﾎﾟｼﾞｼｮﾝの格納変数
	VECTOR2 pos;

	//ｱﾆﾒｰｼｮﾝｶｳﾝﾄ
	unsigned int AniCnt;

	// 移動ﾎﾞﾀﾝの押下ﾌﾗｸﾞ
	int InputNow[DIR_MAX];
	// 前ﾌﾚｰﾑの押下ﾌﾗｸﾞ
	int InputOld[DIR_MAX];

	//ﾎﾟｼﾞｼｮﾝｾｯﾄ
	void SetPos(VECTOR2 pos)
	{
		Obj::pos = pos;
	}
};


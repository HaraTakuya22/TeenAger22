#pragma once
#include <string>
#include <map>
#include "Controller.h"
#include "AddList.h"
#include "VECTOR2.h"

// 各ｵﾌﾞｼﾞｪｸﾄの方向
enum DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
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


class Obj
{
public:
	Obj();
	~Obj();
	virtual void Draw(void);
	//移動（各ｷｬﾗで移動を自由にしたいので純粋仮想関数）
	virtual void Move(const Controller& controll, WeakList objlist) = 0;
	//各ｷｬﾗｸﾀｰの移動
	void Update(const Controller& controll, WeakList objlist);
	//各ｷｬﾗｸﾀｰのｱﾆﾒｰｼｮﾝに関する初期化
	bool Init(std::string filename, VECTOR2 divcnt, VECTOR2 divsize);

	//ｱﾆﾒｰｼｮﾝの追加
	bool AddAnim(std::string animationName, int x, int y, int flame, int val);
	//ｱﾆﾒｰｼｮﾝのｾｯﾄ
	bool SetAnim(std::string animationName);
	//ｱﾆﾒｰｼｮﾝの名前取得
	std::string &GetAnimation(void)
	{
		return AnimationName;
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
private:
	//画像の名前
	std::string ImageName;
	//各ｱﾆﾒｰｼｮﾝの名前
	std::string AnimationName;
	//ｱﾆﾒｰｼｮﾝに関するﾌﾚｰﾑ等の格納
	std::map<std::string, int[MAX]> animTbl;
	//ｱﾆﾒｰｼｮﾝｶｳﾝﾄ
	unsigned int AniCnt;
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

	//ﾎﾟｼﾞｼｮﾝｾｯﾄ
	void SetPos(VECTOR2 pos)
	{
		Obj::pos = pos;
	}
};


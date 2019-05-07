#pragma once
#include <array>

typedef std::array<char, 256> KEY_FLAG;

//ﾎﾞﾀﾝの押下情報のﾀｲﾌﾟ
enum KEY_TYPE {
	KEY_TYPE_NOW,	//今押下
	KEY_TYPE_OLD,	//前ﾌﾚｰﾑに押下
	KEY_TYPE_MAX
};

// ｹﾞｰﾑﾊﾟｯﾄﾞの押下情報のﾀｲﾌﾟ
enum PAD_INPUT
{
	PAD_INPUT_OLD,	// 前ﾌﾚｰﾑに押下
	PAD_INPUT_NOW,	// 今押下
	PAD_INPUT_MAX
};

class Controller
{
public:
	Controller();
	~Controller();
	//ﾎﾞﾀﾝ情報の更新
	bool Update(void);
	//ﾎﾞﾀﾝ情報の取得関数
	const KEY_FLAG &GetButtonInfo(KEY_TYPE type) const;
	// ｹﾞｰﾑﾊﾟｯﾄﾞのﾎﾞﾀﾝ情報の取得関数
	const PAD_INPUT &GetPadButtonInfo(PAD_INPUT inputType) const;

private:
	//ﾎﾞﾀﾝ情報の格納場所
	KEY_FLAG key;
	//前ﾌﾚｰﾑに押したﾎﾞﾀﾝ情報の格納場所
	KEY_FLAG keyOld;

	// ﾎﾞﾀﾝ情報の格納
	PAD_INPUT PadInput;
	// 前ﾌﾚｰﾑに押下情報の格納
	PAD_INPUT PadInputOld;
};


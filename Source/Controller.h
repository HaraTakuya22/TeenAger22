#pragma once
#include <array>

typedef std::array<char, 256> KEY_FLAG;

//无垒偺墴壓忣曬偺啦踢
enum KEY_TYPE {
	NOW,	//崱墴偟偰偄傞
	OLD,	//慜腾把偵墴偟偨
	KEY_MAX
};

class Controller
{
public:
	Controller();
	~Controller();
	//无垒忣曬偺峏怴
	bool Update(void);
	//无垒忣曬偺庢摼娭悢
	const KEY_FLAG &GetButtonInfo(KEY_TYPE type) const;

private:
	//无垒忣曬偺奿擺応強
	KEY_FLAG key;
	//慜腾把偵墴偟偨无垒忣曬偺奿擺応強
	KEY_FLAG keyOld;
};


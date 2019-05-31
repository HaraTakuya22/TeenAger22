#pragma once
#include <array>

// ¶Ò×‚ÌˆÚ“®•ûŒü
enum CAMERA_DIRECTION
{
	CAMERA_LEFT,
	CAMERA_RIGHT,
	CAMERA_UP,
	CAMERA_DOWN,
	CAMERA_MAX
};

//ÎŞÀİ‚Ì‰Ÿ‰ºî•ñ‚ÌÀ²Ìß
enum KEY_TYPE {
	KEY_TYPE_NOW,	//¡‰Ÿ‰º
	KEY_TYPE_OLD,	//‘OÌÚ°Ñ‚É‰Ÿ‰º
	KEY_TYPE_MAX
};

// ¹Ş°ÑÊß¯ÄŞ‚Ì‰Ÿ‰ºî•ñ‚ÌÀ²Ìß
enum PAD_INPUT
{
	PAD_INPUT_OLD,	// ‘OÌÚ°Ñ‚É‰Ÿ‰º
	PAD_INPUT_NOW,	// ¡‰Ÿ‰º
	PAD_INPUT_MAX
};


typedef std::array<char, 256> KEY_FLAG;
typedef std::array<bool[CAMERA_MAX], KEY_TYPE_MAX> KEY_INPUT;

class Controller
{
public:
	Controller();
	~Controller();
	//ÎŞÀİî•ñ‚ÌXV
	bool Update(void);
	//ÎŞÀİî•ñ‚Ìæ“¾ŠÖ”
	const KEY_INPUT& GetButtonInfo(void) const;
	//
	const KEY_FLAG &GetKeyButtonInfo(KEY_TYPE type) const;

	// ¹Ş°ÑÊß¯ÄŞ‚ÌÎŞÀİî•ñ‚Ìæ“¾ŠÖ”
	const PAD_INPUT &GetPadButtonInfo(PAD_INPUT inputType) const;


private:
	//ÎŞÀİî•ñ‚ÌŠi”[êŠ
	KEY_FLAG key;
	//‘OÌÚ°Ñ‚É‰Ÿ‚µ‚½ÎŞÀİî•ñ‚ÌŠi”[êŠ
	KEY_FLAG keyOld;

	// ÎŞÀİî•ñ‚ÌŠi”[
	PAD_INPUT PadInput;
	// ‘OÌÚ°Ñ‚É‰Ÿ‰ºî•ñ‚ÌŠi”[
	PAD_INPUT PadInputOld;

	KEY_INPUT input;
	KEY_INPUT inputOld;
};


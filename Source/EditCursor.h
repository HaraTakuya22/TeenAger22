#pragma once
#include "Obj.h"

class EditCursor :
	public Obj
{
public:
	EditCursor(VECTOR2 pos);
	~EditCursor();
	void Move(const Controller& controll, WeakList objlist);

private:
	void Draw(void);

	// ¶°¿Ù‚ªËßºËßº“_–Å‚·‚é¶³İÄ
	int flickCnt;

	// ¶°¿Ù‚Ì•ÏŠ·ÎŞÀİ‚Ì‰Ÿ‰ºÌ×¸Ş(idi‚ß‚é)
	int ChangeInput;
	int ChangeInputOld;
	// ¶°¿Ù‚Ì•ÏŠ·ÎŞÀİ‚Ì‰Ÿ‰ºÌ×¸Ş(id–ß‚·)
	int ChangeInputBack;
	int ChangeInputBackOld;

	// idî•ñ‚ğ–„‚ß‚ŞÎŞÀİ‚Ì‰Ÿ‰ºÌ×¸Ş
	int SetInput;
	int SetInputOld;

	// Ã½Ä—p
	bool setF;

	int keyDefRng;
	int inputFrame;

	// ID
	objID id;
};


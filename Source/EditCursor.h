#pragma once
#include "Obj.h"


class EditCursor :
	public Obj
{
public:
	EditCursor(VECTOR2 pos,TYPE_NUM num,VECTOR2 camera);
	~EditCursor();
	void Move(const Controller& controll, WeakList objlist);

	bool GetType(OBJ_TYPE type)
	{
		return (type == TYPE_CURSOR);
	}
	
	// individualsMapPosæ“¾ŠÖ”
	//VECTOR2& GetIndividualsMapPos(void)
	//{
	//	return individualsMapPos;
	//}

	PLAYER& GetPlayerNum(void)
	{
		return player;
	}

	VECTOR2 GetCameraPosition(void)
	{
		return cameraPosition;
	}

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

	VECTOR2 cursorPos;

	int keyDefRng;
	int inputFrame;

	// ID
	objID id;
};


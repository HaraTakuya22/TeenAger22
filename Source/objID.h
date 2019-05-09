#pragma once

enum class objID{
	FLOOR,			// 床
	WALL,			// 壁
	CHAIR_1,		// 椅子1
	CHAIR_2,		// 椅子2
	CHAIR_3,		// 椅子3
	CHAIR_4,		// 椅子4
	BOOKSHELF,		// 本棚
	DRAWER,			// 引き出し
	LOCKER,			// ﾛｯｶｰ
	VASE_1,			// 花瓶1
	VASE_2,			// 花瓶2
	MIRRORTABLE,	// 鏡台
	FACE,			// 洗面台
	KITCHIN_1,		// 台所1
	KITCHIN_2,		// 台所2
	S_MONITOR,		// 小さいﾓﾆﾀｰ
	BED,			// ﾍﾞｯﾄﾞ
	DESK,			// 横に長い机
	MONITOR,		// 大きいﾓﾆﾀｰ
	S_TABLE,		// 小さいﾓﾆﾀｰ
	TABLE,			// 縦に長い机
	NON,			// 何もない
	ID_MAX
};

objID begin(objID);
objID end(objID);
objID operator++(objID &id);
objID operator+(objID &id, int k);
objID operator-(objID &id, int k);
objID operator*(objID &id);


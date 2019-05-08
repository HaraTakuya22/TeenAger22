#pragma once

enum class objID{
	FLOOR,			// 床
	WALL,			// 壁
	TABLE,			// 大きなﾃｰﾌﾞﾙ
	SUBTABLE,		// 縦に長いﾃｰﾌﾞﾙ
	SUBMONITOR,		// 小さいﾓﾆﾀｰ
	MONITOR,		// 大きいﾓﾆﾀｰ
	BED,			// ﾍﾞｯﾄﾞ
	VASE_1,			// 花瓶1
	VASE_2,			// 花瓶2
	DESK,			// 横に長い机
	MIRRORTABLE,	// 鏡台
	FACE,			// 洗面台
	KITCHIN_1,		// 台所1
	KITCHIN_2,		// 台所2
	BOOKSHELF,		// 本棚
	DRAWER,			// 引き出し付きの棚
	LOCKER,			// ﾛｯｶｰ
	CHAIR_1,		// 椅子(上向き)
	CHAIR_2,		// 椅子(右向き)
	CHAIR_3,		// 椅子(下向き)
	CHAIR_4,		// 椅子(左向き)
	NON,			// 何もない
	ID_MAX
};

objID begin(objID);
objID end(objID);
objID operator++(objID &id);
objID operator+(objID &id, int k);
objID operator-(objID &id, int k);
objID operator*(objID &id);


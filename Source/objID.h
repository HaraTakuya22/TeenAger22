#pragma once

enum class objID{
	PLAYER1,		// prey
	PLAYER2,
	PLAYER3,
	WALL,			// Η
	CHAIR_1,		// Φq1
	CHAIR_2,		// Φq2
	CHAIR_3,		// Φq3
	CHAIR_4,		// Φq4
	BOOKSHELF,		// {I
	DRAWER,			// ψ«o΅
	LOCKER,			// Ϋ―Ά°
	VASE_1,			// Τr1
	VASE_2,			// Τr2
	MIRRORTABLE,	// Ύδ
	FACE,			// τΚδ
	KITCHIN_1,		// δ1
	KITCHIN_2,		// δ2
	S_MONITOR,		// ¬³’ΣΖΐ°
	BED,			// Νή―Δή
	DESK,			// ‘Ι·’χ
	MONITOR,		// ε«’ΣΖΐ°
	S_TABLE,		// cΙ·’χ1
	TABLE,			// cΙ·’χ2
	NON,			// ½ΰΘ’
	ID_MAX
};

objID begin(objID);
objID end(objID);
objID operator++(objID &id);
objID operator+(objID &id, int k);
objID operator-(objID &id, int k);
objID operator*(objID &id);


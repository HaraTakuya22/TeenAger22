#pragma once

enum class objID{
	PLAYER1,			// prey
	PLAYER2,
	PLAYER3,
	PLAYER_IT,			// it
	WALL,			// ��
	CHAIR_1,		// �֎q1
	CHAIR_2,		// �֎q2
	CHAIR_3,		// �֎q3
	CHAIR_4,		// �֎q4
	BOOKSHELF,		// �{�I
	DRAWER,			// �����o��
	LOCKER,			// ۯ��
	VASE_1,			// �ԕr1
	VASE_2,			// �ԕr2
	MIRRORTABLE,	// ����
	FACE,			// ���ʑ�
	KITCHIN_1,		// �䏊1
	KITCHIN_2,		// �䏊2
	S_MONITOR,		// ����������
	BED,			// �ޯ��
	DESK,			// ���ɒ�����
	MONITOR,		// �傫������
	S_TABLE,		// �c�ɒ�����1
	TABLE,			// �c�ɒ�����2
	NON,			// �����Ȃ�
	ID_MAX
};

objID begin(objID);
objID end(objID);
objID operator++(objID &id);
objID operator+(objID &id, int k);
objID operator-(objID &id, int k);
objID operator*(objID &id);


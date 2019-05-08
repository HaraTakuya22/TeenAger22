#pragma once

enum class objID{
	FLOOR,			// ��
	WALL,			// ��
	TABLE,			// �傫��ð���
	SUBTABLE,		// �c�ɒ���ð���
	SUBMONITOR,		// ����������
	MONITOR,		// �傫������
	BED,			// �ޯ��
	VASE_1,			// �ԕr1
	VASE_2,			// �ԕr2
	DESK,			// ���ɒ�����
	MIRRORTABLE,	// ����
	FACE,			// ���ʑ�
	KITCHIN_1,		// �䏊1
	KITCHIN_2,		// �䏊2
	BOOKSHELF,		// �{�I
	DRAWER,			// �����o���t���̒I
	LOCKER,			// ۯ��
	CHAIR_1,		// �֎q(�����)
	CHAIR_2,		// �֎q(�E����)
	CHAIR_3,		// �֎q(������)
	CHAIR_4,		// �֎q(������)
	NON,			// �����Ȃ�
	ID_MAX
};

objID begin(objID);
objID end(objID);
objID operator++(objID &id);
objID operator+(objID &id, int k);
objID operator-(objID &id, int k);
objID operator*(objID &id);


#pragma once

enum class objID{
	ID_1,
	ID_2,
	ID_3,
	ID_4,
	ID_5,
	ID_6,
	ID_7,
	ID_8,
	ID_9,
	ID_NON,
	ID_MAX
};

objID begin(objID);
objID end(objID);
objID operator++(objID &id);
objID operator+(objID &id, int k);
objID operator-(objID &id, int k);
objID operator*(objID &id);


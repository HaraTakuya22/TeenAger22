#pragma once
// ÌßÚ²Ô°‚ÌŽí—Þ
enum TYPE_NUM
{
	NUM_CURSOR,
	PREY_1,
	PREY_2,
	PREY_3,
	NUM_IT,
	PREY_MAX
};

TYPE_NUM begin(TYPE_NUM);
TYPE_NUM end(TYPE_NUM);
TYPE_NUM operator++(TYPE_NUM &num);
TYPE_NUM operator+(TYPE_NUM &num, int k);
TYPE_NUM operator-(TYPE_NUM &num, int k);
TYPE_NUM operator*(TYPE_NUM &num);








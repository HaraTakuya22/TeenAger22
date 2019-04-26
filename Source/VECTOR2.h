#pragma once

class VECTOR2
{
public:
	VECTOR2();
	~VECTOR2();

	VECTOR2(int x, int y);

	int x;
	int y;

	VECTOR2& operator = (const VECTOR2& vec);
	int& operator[](int i);

	bool operator==(const VECTOR2& vec) const;

	bool operator!=(const VECTOR2& vec) const;

	VECTOR2& operator+=(const VECTOR2& vec);


	VECTOR2& operator-=(const VECTOR2& vec);
	VECTOR2& operator*=(const VECTOR2& vec);
	VECTOR2& operator/=(const VECTOR2& vec);
	VECTOR2 operator+()const;						//const = éQè∆ìnÇµÇÃç€Ç…égóp
	VECTOR2 operator-()const;

};
VECTOR2 operator+(const VECTOR2& u, const VECTOR2& v);
VECTOR2 operator+(const VECTOR2& u, int k);

VECTOR2 operator+(int k, const VECTOR2& v);
VECTOR2 operator-(const VECTOR2& u, int k);

//Vector3D-Vector3D
VECTOR2 operator-(const VECTOR2& u, const VECTOR2& v);
VECTOR2 operator%(const VECTOR2& u, const VECTOR2& v);
VECTOR2 operator%(const VECTOR2& u, int k);
VECTOR2 operator*(int k, const  VECTOR2& v);
bool operator==(const VECTOR2& vec, int k);
//Vector3D*int
VECTOR2 operator*(const VECTOR2& u, int k);

VECTOR2 operator/(const VECTOR2& u, int k);
VECTOR2 operator/(const int k, VECTOR2& v);
VECTOR2& operator+=(const VECTOR2& v, int k);

VECTOR2 operator<(const VECTOR2& u, VECTOR2& v);
VECTOR2 operator<(const VECTOR2& u, const int k);
VECTOR2 operator>(const int k, const VECTOR2& v);


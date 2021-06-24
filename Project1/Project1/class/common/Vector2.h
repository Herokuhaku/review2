#pragma once
#include <vector>



template <class T>
class Vector2Template
{
public:
	Vector2Template();
	~Vector2Template();
	Vector2Template(T x_,T y_);
	T x;
	T y;

	// ‘ã“ü‰‰ŽZŽq
	//Vector2Template& operator = (const Vector2Template& vec);
	Vector2Template<T>& operator = (const Vector2Template<double>& vec);
	Vector2Template<T>& operator = (const Vector2Template<float>& vec);
	Vector2Template<T>& operator = (const Vector2Template<int>& vec);

	// ’P€‰‰ŽZŽq
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const Vector2Template& vec);
	Vector2Template& operator /= (const Vector2Template& vec);

	// ”äŠr‰‰ŽZŽq
	bool operator >= (const Vector2Template& vec)const;
	bool operator <=  (const Vector2Template& vec)const;
	bool operator > (const Vector2Template& vec)const;
	bool operator <  (const Vector2Template& vec)const;
	bool operator ==  (const Vector2Template& vec)const;
	bool operator != (const Vector2Template& vec)const;

	// ˜_—‰‰ŽZŽq 
	bool operator && (const Vector2Template& vec)const;
	bool operator || (const Vector2Template& vec)const;

	// “Y‚¦Žš‰‰ŽZŽq
	T& operator[](const int& num);

	// 2€‰‰ŽZŽq
	Vector2Template operator +(const Vector2Template& vec)const;
	Vector2Template operator -(const Vector2Template& vec)const;
	Vector2Template operator *(const Vector2Template& vec)const;
	Vector2Template operator /(const Vector2Template& vec)const;
	Vector2Template operator %(const Vector2Template& vec)const;

	Vector2Template operator +()const;
	Vector2Template operator -()const;

	Vector2Template& operator++();
	Vector2Template operator++(int);

	Vector2Template& operator--();
	Vector2Template operator--(int);

	// •½•û˜a‚Ì•½•ûª‚ð•Ô‚·
	float Magnitude()const;	
	// ³‹K‰»(‘å‚«‚³‚ð‚P‚É)‚µ‚Ü‚·
	void Normalize();
	// ³‹K‰»‚µ‚½‚à‚Ì‚ð•Ô‚·
	Vector2Template Normalized()const;
};

// Vector2 ‚Æ int‚ÌŽl‘¥‰‰ŽZ
template <class T>
Vector2Template<T> operator +(const Vector2Template<T>& vec,const int& num);
template <class T>
Vector2Template<T> operator -(const Vector2Template<T>& vec, const int& num);
template <class T>
Vector2Template<T> operator *(const Vector2Template<T>& vec, const int& num);
template <class T>
Vector2Template<T> operator /(const Vector2Template<T>& vec, const int& num);

// int ‚Æ Vector2‚ÌŽl‘¥‰‰ŽZ
template <class T>
Vector2Template<T> operator +(const int& num,const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator -(const int& num, const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator *(const int& num, const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator /(const int& num, const Vector2Template<T>& vec);

// Vector2 ‚Æ float‚ÌŽl‘¥‰‰ŽZ
template <class T>
Vector2Template<T> operator + (const Vector2Template<T>& vec,const float& num);
template <class T>
Vector2Template<T> operator - (const Vector2Template<T>& vec, const float& num);
template <class T>
Vector2Template<T> operator * (const Vector2Template<T>& vec,const float& num);
template <class T>
Vector2Template<T> operator / (const Vector2Template<T>& vec, const float& num);
// float ‚Æ Vector2‚ÌŽl‘¥‰‰ŽZ
template <class T>
Vector2Template<T> operator + (const float& num,const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator * (const float& num,const Vector2Template<T>& vec);

using Int2 = Vector2Template<int>;
using Float2 = Vector2Template<float>;
using Double2 = Vector2Template<double>;

using VecInt = std::vector<int>;

//Float2 operator - (Int2 vec1, Float2 vec2);
//Float2 operator / (Int2 vec1, Float2 vec2);
//Float2 operator * (Int2 vec1, Float2 vec2);
#include "./detailes/Vector2.h"
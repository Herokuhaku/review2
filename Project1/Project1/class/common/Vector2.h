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

	// 代入演算子
	//Vector2Template& operator = (const Vector2Template& vec);
	Vector2Template<T>& operator = (const Vector2Template<double>& vec);
	Vector2Template<T>& operator = (const Vector2Template<float>& vec);
	Vector2Template<T>& operator = (const Vector2Template<int>& vec);

	// 単項演算子
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const Vector2Template& vec);
	Vector2Template& operator /= (const Vector2Template& vec);

	// 比較演算子
	bool operator >= (const Vector2Template& vec)const;
	bool operator <=  (const Vector2Template& vec)const;
	bool operator > (const Vector2Template& vec)const;
	bool operator <  (const Vector2Template& vec)const;
	bool operator ==  (const Vector2Template& vec)const;
	bool operator != (const Vector2Template& vec)const;

	// 論理演算子 
	bool operator && (const Vector2Template& vec)const;
	bool operator || (const Vector2Template& vec)const;

	// 添え字演算子
	T& operator[](const int& num);

	// 2項演算子
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

	// 平方和の平方根を返す
	float Magnitude()const;	
	// 正規化(大きさを１に)します
	void Normalize();
	// 正規化したものを返す
	Vector2Template Normalized()const;
};

// Vector2 と intの四則演算
template <class T>
Vector2Template<T> operator +(const Vector2Template<T>& vec,const int& num);
template <class T>
Vector2Template<T> operator -(const Vector2Template<T>& vec, const int& num);
template <class T>
Vector2Template<T> operator *(const Vector2Template<T>& vec, const int& num);
template <class T>
Vector2Template<T> operator /(const Vector2Template<T>& vec, const int& num);

// int と Vector2の四則演算
template <class T>
Vector2Template<T> operator +(const int& num,const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator -(const int& num, const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator *(const int& num, const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator /(const int& num, const Vector2Template<T>& vec);

// Vector2 と floatの四則演算
template <class T>
Vector2Template<T> operator + (const Vector2Template<T>& vec,const float& num);
template <class T>
Vector2Template<T> operator - (const Vector2Template<T>& vec, const float& num);
template <class T>
Vector2Template<T> operator * (const Vector2Template<T>& vec,const float& num);
template <class T>
Vector2Template<T> operator / (const Vector2Template<T>& vec, const float& num);
// float と Vector2の四則演算
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
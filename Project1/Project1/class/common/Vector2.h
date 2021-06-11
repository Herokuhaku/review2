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

	// ������Z�q
	Vector2Template& operator = (const Vector2Template& vec);

	// �P�����Z�q
	Vector2Template& operator += (const Vector2Template& vec);
	Vector2Template& operator -= (const Vector2Template& vec);
	Vector2Template& operator *= (const Vector2Template& vec);
	Vector2Template& operator /= (const Vector2Template& vec);

	// ��r���Z�q
	bool operator >= (const Vector2Template& vec)const;
	bool operator <=  (const Vector2Template& vec)const;
	bool operator > (const Vector2Template& vec)const;
	bool operator <  (const Vector2Template& vec)const;
	bool operator ==  (const Vector2Template& vec)const;
	bool operator != (const Vector2Template& vec)const;

	// �_�����Z�q 
	bool operator && (const Vector2Template& vec)const;
	bool operator || (const Vector2Template& vec)const;

	// �Y�������Z�q
	T& operator[](const int& num);

	// 2�����Z�q
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
};

// Vector2 �� int�̎l�����Z
template <class T>
Vector2Template<T> operator +(const Vector2Template<T>& vec,const int& num);
template <class T>
Vector2Template<T> operator -(const Vector2Template<T>& vec, const int& num);
template <class T>
Vector2Template<T> operator *(const Vector2Template<T>& vec, const int& num);
template <class T>
Vector2Template<T> operator /(const Vector2Template<T>& vec, const int& num);

// int �� Vector2�̎l�����Z
template <class T>
Vector2Template<T> operator +(const int& num,const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator -(const int& num, const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator *(const int& num, const Vector2Template<T>& vec);
template <class T>
Vector2Template<T> operator /(const int& num, const Vector2Template<T>& vec);

// Vector2 �� float�̎l�����Z
template <class T>
Vector2Template<T> operator + (const Vector2Template<T>& vec,const float& num);

template <class T>
Vector2Template<T> operator - (const Vector2Template<T>& vec, const float& num);

template <class T>
Vector2Template<T> operator * (const Vector2Template<T>& vec,const float& num);

template <class T>
Vector2Template<T> operator / (const Vector2Template<T>& vec, const float& num);

using Int2 = Vector2Template<int>;
using Float2 = Vector2Template<float>;
using Double2 = Vector2Template<double>;

using VecInt = std::vector<int>;

#include "./detailes/Vector2.h"
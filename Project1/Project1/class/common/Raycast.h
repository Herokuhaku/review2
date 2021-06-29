#pragma once
#include "Vector2.h"
#include "Collision.h"

class Raycast
{
public:
	struct Ray {
		Float2 p;	// �n�_
		Float2 v;	// �����x�N�g��
	};
	struct Line {
		Float2 p;	// �n�_
		Float2 end;	// �I�_
		//�n�_����I�_�ւ̃x�N�g��
		Float2 vec() {
			return end - p;
		}
	};
	bool CheckCollision(Ray ray,Collision col);
	bool CheckRay(Ray ray,Line line);
};


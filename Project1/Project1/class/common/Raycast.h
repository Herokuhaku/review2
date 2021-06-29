#pragma once
#include "Vector2.h"
#include "Collision.h"

class Raycast
{
public:
	struct Ray {
		Float2 p;	// 始点
		Float2 v;	// 方向ベクトル
	};
	struct Line {
		Float2 p;	// 始点
		Float2 end;	// 終点
		//始点から終点へのベクトル
		Float2 vec() {
			return end - p;
		}
	};
	bool CheckCollision(Ray ray,Collision col);
	bool CheckRay(Ray ray,Line line);
};


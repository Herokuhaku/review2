#include "Raycast.h"

bool Raycast::LineAndLine(Float2 A1, Float2 A2,Float2 B1, Float2 B2)
{
	Float2 base = B2 - B1;
	Float2 sub1 = A1 - B1;
	Float2 sub2 = A2 - B1;

	float r = Cross(base, sub1) * Cross(base,sub2);

	if (r > 0){
		return false;
	}

	base = A2 - A1;
	sub1 = B1 - A1;
	sub2 = B2 - A1;

	r = Cross(base, sub1) * Cross(base, sub2);

	if (r > 0){
		return false;
	}
	return true;
}

bool Raycast::CheckCollision(Ray ray, Collision col)
{
	std::vector<Line> line_;
	Line line[4];
	// ã•Ó
	line[0].p = col.first;
	line[0].end.y = line[0].p.y;
	line[0].end.x = col.first.x + col.second.x;
	// ‰E•Ó
	line[1].p = line[0].end;
	line[1].end.x = line[1].p.x;
	line[1].end.y = line[1].p.y + col.second.y;
	// ‰º•Ó
	line[2].p = line[1].end;
	line[2].end.y = line[2].p.y;
	line[2].end.x = line[2].p.x - col.second.x;
	// ¶•Ó
	line[3].p = line[2].end;
	line[3].end.x = line[3].p.x;
	line[3].end.y = line[3].p.y - col.second.y;
	
	bool flag = false;

	for (auto& l : line) {
		flag |= CheckRay(ray,l);
	}
	return flag;
}

bool Raycast::CheckRay(Ray ray, Line line)
{

	Float2 A1 = ray.p;
	Float2 A2 = ray.p + ray.v;

	Float2 B1 = line.p;
	Float2 B2 = line.end;

	return LineAndLine(A1, A2, B1, B2);
}
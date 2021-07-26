#pragma once
#include <map>
#include <vector>
#include <string>
#include "../common/Vector2.h"

using AnimVector = std::vector<std::pair<int, int>>;

enum class STATE
{
	up,	// �ʏ�
	left,
	right,
	down,
	MAX
};

class Animation
{
public:
	Animation(std::string key);
	~Animation();
	bool Init(void);
	bool Update(void);
	bool Draw(Float2 pos,Int2 size,float mag = 1.0f);
	// ��Ԃ�ω�������
	bool state(const std::string state);
	// �����̃L�[���擾����
	std::string GetKey(void);
	std::string GetState(void);
private:
	std::string key_;
	std::string state_;

	int animframe_;			// �t���[����
	int animcount_;			// ����܂������
};


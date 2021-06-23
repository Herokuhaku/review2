#pragma once
#include <map>
#include <vector>
#include <string>
#include "../common/Vector2.h"

using AnimVector = std::vector<std::pair<int, int>>;

enum class STATE
{
	UP,	// �ʏ�
	LEFT,
	RIGHT,
	DOWN,
	MAX
};

class Animation
{
public:
	Animation(std::string key);
	~Animation();
	bool Init(void);
	bool Update(void);
	bool Draw(Int2 pos,Int2 size,float mag = 1.0f);
	bool state(const STATE state);
	std::string GetKey(void);
private:
	std::string key_;
	STATE state_;

	int animframe_;			// �t���[����
	int animcount_;			// ����܂������
	//std::map<STATE, AnimVector>animMap_;// �A�j���[�V�����̃}�b�v

	//unsigned int animframe_;			// �t���[����
	//unsigned int animcount_;			// ����܂������
};


#pragma once
#include <map>
#include <vector>
#include <string>
#include "../../Tiled/TmxObj.h"

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
	bool Draw(Int2 pos);
	bool state(const STATE state);
	std::string GetKey(void);
private:
	std::string key_;
	STATE state_;

	unsigned int animframe_;			// �t���[����
	unsigned int animcount_;			// ����܂������
	//std::map<STATE, AnimVector>animMap_;// �A�j���[�V�����̃}�b�v

	//unsigned int animframe_;			// �t���[����
	//unsigned int animcount_;			// ����܂������
};


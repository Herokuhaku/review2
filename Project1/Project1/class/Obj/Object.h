#pragma once
#include <map>
#include "../common/Vector2.h"
#include "../input/Controller.h"
#include "../../Tiled/TmxObj.h"

using AnimVector = std::vector<std::pair<int, unsigned int>>;

enum class STATE
{
	UP,	// �ʏ�
	LEFT,
	RIGHT,
	DOWN,
	MAX
};

class Object
{
public:
	Object();
	~Object();
	virtual bool Init(CntType cntType) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void);
	bool state(const STATE state);	
	bool SetItem(const STATE state,std::string str);
	bool SetAnim(const STATE state, AnimVector& data);
protected:
	TmxObj tmx_;
	XmlItem xmlitem_;

	Int2 pos_;
	int speed_;
	STATE _state;

	std::unique_ptr<Controller>controller_;
	// 
	std::map<STATE, AnimVector>_animMap;// �A�j���[�V�����̃}�b�v

	//std::string _animKey;				// ���O
	unsigned int _animFrames;			// �t���[����
	unsigned int _animCount;			// ����܂������
};


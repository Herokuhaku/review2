#pragma once
#include <map>
#include "../common/Vector2.h"
#include "../input/Controller.h"
#include "../../Tiled/TmxObj.h"
#include "../Animation/Animation.h"

//using AnimVector = std::vector<std::pair<int,int>>;
//
//enum class STATE
//{
//	UP,	// �ʏ�
//	LEFT,
//	RIGHT,
//	DOWN,
//	MAX
//};

class Object
{
public:
	Object();
	~Object();
	// ������
	virtual bool Init(CntType cntType) = 0;
	// �X�V
	virtual void Update(void) = 0;
	// �`��
	virtual void Draw(void);
protected:
	//TmxObj tmx_;
	//XmlItem xmlitem_;

	Int2 pos_;
	int speed_;
	std::unique_ptr<Controller>controller_;
	// 
	//std::map<STATE, AnimVector>animMap_;// �A�j���[�V�����̃}�b�v
	std::unique_ptr<Animation> anim_;

	//unsigned int animframe_;			// �t���[����
	//unsigned int animcount_;			// ����܂������
	//unsigned int animframe_;			// �t���[����
	//unsigned int animcount_;			// ����܂������
};


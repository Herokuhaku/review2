#pragma once
#include <map>
#include "../common/Vector2.h"
#include "../input/Controller.h"
#include "../../Tiled/TmxObj.h"
#include "../Animation/Animation.h"
#include "../common/Raycast.h"

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
	virtual void Update(double delta) = 0;
	// �`��
	virtual void Draw(void);
	virtual void GravityUpdate(double delta);
protected:
	//TmxObj tmx_;
	//XmlItem xmlitem_;
	Raycast raycast_;
	// ���W
	Float2 pos_;
	// �����蔻��̒��S���W
	Float2 colpos_;
	std::map<std::string,std::list<Float2>> colvec_;
	Int2 size_;
	// Draw�̔{��
	float mag_;
	float speed_;
	std::unique_ptr<Controller>controller_;
	// 
	std::shared_ptr<TmxObj> tmx_;
	std::unique_ptr<Animation> anim_;
	float gravity_;
	float grav_;
	bool jump_;
	bool upflag_;
	bool gravitybool_;
	float jumppow_;
	float count_;
	float v0;
	float v1;
	double time_;
};


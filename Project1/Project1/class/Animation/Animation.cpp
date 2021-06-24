#include "Animation.h"

#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../common/AnimationMng.h"
//Animation::Animation()
//{
//}

Animation::Animation(std::string key):key_(key)
{
	Init();
}

Animation::~Animation()
{
}

bool Animation::Init(void)
{
	animcount_ = 0;
	animframe_ = 0;
	
	state_ = "up";
	return true;
}

bool Animation::Update(void)
{
	if (!lpAnimationMng.CheckAnim(key_,state_))
	{
		return false;
	}
	if (animframe_ < 0 || animframe_ >= lpAnimationMng.GetAnimSize(key_,state_))
	{
		return false;
	}

	if (animcount_++ >= lpAnimationMng.GetAnimFrame(key_, state_, animframe_))
	{
		if (lpAnimationMng.GetAnimID(key_, state_, animframe_) >= 0)
		{
			animframe_ += 1;
		}
	}

	if (animframe_ >= lpAnimationMng.GetAnimSize(key_, state_))
	{
		animframe_ = 0;
		animcount_ = 0;
	}
	return true;
}

bool Animation::Draw(Float2 pos,Int2 size,float mag)
{
	Update();
	size = size * mag;
	DrawRotaGraph(pos.x + (size.x/2),pos.y + (size.y/2),mag,0.0f, lpAnimationMng.GetAnimID(key_, state_, animframe_),true);
	//DrawGraph(pos.x, pos.y,lpImageMng.GetAnimID(key_, state_,animframe_), true);
	return true;
}

bool Animation::state(const std::string state)
{
	if (lpAnimationMng.CheckAnim(key_, state))
	{
		if (state != state_)//±∆“∞ºÆ›Ç™à·Ç¡ÇΩèÍçá0Ç©ÇÁénÇﬂÇÈ
		{
			animframe_ = 0;
			animcount_ = 0;
		}
		state_ = state;
		return true;
	}
	return false;
}

std::string Animation::GetKey(void)
{
	return key_;
}

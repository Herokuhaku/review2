#include "Animation.h"

#include <DxLib.h>
#include "../common/ImageMng.h"
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
	state_ = STATE::DOWN;
	animcount_ = 0;
	animframe_ = 0;
	return true;
}

bool Animation::Update(void)
{
	if (!lpImageMng.CheckAnim(key_,state_))
	{
		return false;
	}
	if (animframe_ < 0 || animframe_ >= lpImageMng.GetAnimSize(key_,state_))
	{
		return false;
	}

	if (animcount_++ >= lpImageMng.GetAnimFrame(key_, state_, animframe_))
	{
		if (lpImageMng.GetAnimID(key_, state_, animframe_) >= 0)
		{
			animframe_ += 1;
		}
	}

	if (animframe_ >= lpImageMng.GetAnimSize(key_, state_))
	{
		animframe_ = 0;
		animcount_ = 0;
	}
	return true;
}

bool Animation::Draw(Int2 pos)
{
	Update();
	DrawGraph(pos.x, pos.y,lpImageMng.GetAnimID(key_, state_,animframe_), true);
	return true;
}

bool Animation::state(const STATE state)
{
	if (lpImageMng.CheckAnim(key_, state))
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

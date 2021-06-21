#include "Object.h"
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../input/KeyInput.h"
#include "../input/PadInput.h"

Object::Object():speed_(2),_animCount(0),_animFrames(0),_state(STATE::DOWN)
{
}

Object::~Object()
{
}

void Object::Draw(void)
{
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	if (_animFrames < 0 || _animFrames >= _animMap[_state].size())
	{
		return;
	}

	if (_animCount >= _animMap[_state][_animFrames].second)
	{
		if (_animMap[_state][_animFrames].first >= 0)
		{
			_animFrames += 1;
		}
	}
	_animCount++;		// 1F�����Ȃ��Ȃ邩��^�񒆂ɂ���
	if (_animFrames >= _animMap[_state].size())
	{
		_animFrames = 0;
		_animCount = 0;
	}

	DrawGraph(pos_.x, pos_.y, _animMap[_state][_animFrames].first, true);
}

bool Object::state(const STATE state)
{
	if (_animMap.find(state) != _animMap.end())	//��������B
	{
		if (state != _state)// ������Ұ��݂Ÿر������ςɂȂ邩���Ұ��݂�������ꍇ0�ɂ���
		{
			_animFrames = 0;
			_animCount = 0;
		}
		_state = state;						// ���̏�Ԃ�����
		return true;
	}
	return false;
}

bool Object::SetItem(const STATE state, std::string dir)
{
	AnimVector data;
	int frame = 0;
	for (auto& item : xmlitem_.data_[dir]) {
		frame += item.second;
		data.emplace_back(lpImageMng.GetID(xmlitem_.item_["name"])[item.first],frame);
	}
	SetAnim(state, data);
	return true;
}

bool Object::SetAnim(const STATE state, AnimVector& data)
{
	return _animMap.try_emplace(state, std::move(data)).second;
}

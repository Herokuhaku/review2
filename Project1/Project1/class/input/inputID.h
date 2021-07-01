#pragma once
#include <type_traits>

enum class InputID {
	Up,
	Down,
	Left,
	Right,
	Jump,
	Btn1,
	Btn2,
	Btn3,
	Escape,
	Max
};

static InputID begin(InputID) { return InputID::Up; };
static InputID end(InputID) { return InputID::Max; };
static InputID operator++(InputID& num) { return num = InputID(std::underlying_type<InputID>::type(num) + 1); };
static InputID operator*(const InputID& state) { return state; };
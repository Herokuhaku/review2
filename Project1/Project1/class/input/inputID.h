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

static InputID Converter(const std::string str) {
	if (str == "up") { return InputID::Up; }
	else if (str == "down") { return InputID::Down; }
	else if (str == "left") { return InputID::Left; }
	else if (str == "right") { return InputID::Right;}
	else if (str == "jump") { return InputID::Jump; }
	else if (str == "btn1") { return InputID::Btn1; }
	else if (str == "btn2") { return InputID::Btn2; }
	else if (str == "btn3") { return InputID::Btn3; }
	else if (str == "escape") { return InputID::Escape; }
	return InputID::Max;
};

static InputID begin(InputID) { return InputID::Up; };
static InputID end(InputID) { return InputID::Max; };
static InputID operator++(InputID& num) { return num = InputID(std::underlying_type<InputID>::type(num) + 1); };
static InputID operator*(const InputID& state) { return state; };


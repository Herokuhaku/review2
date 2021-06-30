#pragma once
#include <memory>
#include <array>
#include "../common/Vector2.h"
class BaseScene;
using UniqueScene = std::unique_ptr<BaseScene>;

enum class Scene {
	Transition,
	Title,
	Game,
	Menu,
	Max
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	// ������
	virtual bool Init(void) = 0;
	// �X�V����
	virtual UniqueScene Update(double delta,UniqueScene own) = 0;
	// Draw
	virtual void Draw(double delta);
	// �����̃X�N���[����Draw
	virtual void DrawOwnScreen(double delta) = 0;
	// �����̃V�[����Ԃ�
	virtual Scene GetSceneID(void) = 0;
private:
protected:
	std::array<int,2> click_;
	// �X�N���[���i�[�p
	int screen_;
	// �X�N���[���̏c���T�C�Y
	Int2 screenSize_;
};


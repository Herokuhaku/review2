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
	// 初期化
	virtual bool Init(void) = 0;
	// 更新処理
	virtual UniqueScene Update(double delta,UniqueScene own) = 0;
	// Draw
	virtual void Draw(double delta);
	// 自分のスクリーンにDraw
	virtual void DrawOwnScreen(double delta) = 0;
	// 自分のシーンを返す
	virtual Scene GetSceneID(void) = 0;
private:
protected:
	std::array<int,2> click_;
	// スクリーン格納用
	int screen_;
	// スクリーンの縦横サイズ
	Int2 screenSize_;
};


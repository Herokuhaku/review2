#pragma once
#include "../BaseScene.h"

enum class Transition {
	CrossFade,
	FadeInOut,
	Max
};

class TransitionScene :
	public BaseScene
{
public:
	TransitionScene(double limit,UniqueScene befor,UniqueScene after);
	~TransitionScene();
private:

	// 初期化
	bool Init(void)override;
	// 更新
	UniqueScene Update(double delta,UniqueScene own)override;
	virtual bool UpdateTransition(double delta) = 0;
	// 描画
	//virtual void Draw(double delta)override;

	Scene GetSceneID(void)override final{ return Scene::Transition; };
	void DrawOwnScreen(double delta)override = 0;
protected:
	// limitで判定を取る
	virtual bool LimitCheck(double delta);
	// 変更前のシーン
	UniqueScene before_;
	// 変更後のシーン
	UniqueScene after_;
	// 1フレームあたりの値
	double count_;
	// 値の合計
	double drawsum_;
	// 255を最大値とする(α値の最大値)
	double drawmax_;
	// シーンの継続時間(秒)
	double limit_;
};


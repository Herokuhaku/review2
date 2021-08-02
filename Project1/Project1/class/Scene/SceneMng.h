#pragma once
#include <chrono>
#include <memory>
#include <array>
#include "BaseScene.h"
#include "../common/Vector2.h"
#include "../input/KeyInput.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng& GetInstance(void) {
		static SceneMng sInstance_;
		return sInstance_;
	}
	// メインループ
	void Run(void);
	// 更新処理
	void Update(void);
	// 描画
	void Draw(void);
	// 画面サイズを取る
	const Int2 GetScreenSize(void)const;
	// ウィンドウを消すフラグ
	void Finish(void) { finish_ = true; };
	// システムのコントローラーを取る
	std::shared_ptr<Controller> GetController(void);
private:
	SceneMng();
	~SceneMng();
	// システムの初期化
	bool SysInit(void);
	// 初期化フラグ
	bool initflag_;
	// 現在のシーン
	UniqueScene scene_;
	// deltaを求める期間 now ~ oldの時間をdeltaとする
	std::chrono::system_clock::time_point now_, old_;
	// スクリーンサイズ
	const Int2 screenSize_;
	// ゲーム終了
	bool finish_;
	int frame_;
	// システムで管理しているコントローラー
	std::shared_ptr<Controller> controller_;
};
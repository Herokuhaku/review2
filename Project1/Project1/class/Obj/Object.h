#pragma once
#include <map>
#include "../common/Vector2.h"
#include "../input/Controller.h"
#include "../../Tiled/TmxObj.h"
#include "../Animation/Animation.h"
#include "../common/Raycast.h"
#include "../common/RingInputID.h"
//#include "Move.h"
//#include "CheckKey.h"

//using AnimVector = std::vector<std::pair<int,int>>;
//
//enum class STATE
//{
//	UP,	// 通常
//	LEFT,
//	RIGHT,
//	DOWN,
//	MAX
//};
enum class PlayerType {
	RunAway,	// 逃げる人
	Ogre,		// 鬼
	Non
};

struct CheckKey;
struct Move;
struct SetAnime;
struct ColisionCheck;
struct Jump;
struct CheckCommand;
struct Command;

class Object
{
public:
	Object();
	~Object();
	// 初期化
	virtual bool Init(CntType cntType) = 0;
	// 更新
	virtual void Update(double delta) = 0;
	// 描画
	virtual void Draw(void);
	// 重力の処理(gravitybool_ が falseだと処理をしない)
	virtual void GravityUpdate(double delta);
	// プレイヤーの種類を返す
	PlayerType GetPlayerType(void);
	
	void SetAnimationState(std::string str);
	// 今流れているアニメーションの名前を取る
	std::string GetNowAnimationName(void);
	// 自分の生成番号を返す
	int GetObjectNum(void);
	// 自分の位置情報を返す
	Float2 GetPos(void);
	// 自分の位置情報を返す
	void SetPos(Float2 pos);
	// 自分のサイズを返す
	Float2 GetSize(void);
	// 捕獲状況を変える
	void SetCatch(int num);
	// 現在の捕獲状況を返す
	int GetCatch(void);

protected:
	// 生成番号(0から)
	int objectnumber_;
	// 視線
	Raycast raycast_;
	// 座標
	Float2 pos_;
	// 当たり判定の中心座標
	Float2 colpos_;
	std::map<std::string,std::list<Float2>> colvec_;
	Int2 size_;
	// Drawの倍率
	float mag_;
	// 移動スピード
	float speed_;
	// コントローラ情報(keyboard,padなど)
	std::unique_ptr<Controller>controller_;
	//  Tmxのデータ
	std::shared_ptr<TmxObj> tmx_;
	// アニメーション
	std::unique_ptr<Animation> anim_;
	// 重力
	float gravity_;
	// ジャンプ判定
	bool jump_;
	// 重力を適用するかどうか
	bool gravitybool_;
	// 現在のジャンプ力
	float jumppow_;
	// 最初の加速度
	float v1;
	// ジャンプしてどのくらいの時間たったか
	double time_;
	// コマンド再生しているか
	bool playcommand_;
	// コマンドの猶予フレーム保存用
	int grace_;				// フレーム
	double gracetime_;		// 秒
	// コマンド確認のための位置情報
	int commandcount_;

	// コマンドを記録
	RingInputID* commandhis_;
	// コマンドを記録する位置情報
	int hisnum_;
	// プレイヤーの種類
	PlayerType pltype_;

	// 0: 鬼 1 : 捕まっていない 2 : 捕まえられた 
	int catchflag_;

	friend Move;
	friend CheckKey;
	friend SetAnime;
	friend ColisionCheck;
	friend Jump;
	friend CheckCommand;
	friend Command;
};


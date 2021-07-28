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
//	UP,	// �ʏ�
//	LEFT,
//	RIGHT,
//	DOWN,
//	MAX
//};
enum class PlayerType {
	RunAway,	// ������l
	Ogre,		// �S
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
	// ������
	virtual bool Init(CntType cntType) = 0;
	// �X�V
	virtual void Update(double delta) = 0;
	// �`��
	virtual void Draw(void);
	// �d�͂̏���(gravitybool_ �� false���Ə��������Ȃ�)
	virtual void GravityUpdate(double delta);
	// �v���C���[�̎�ނ�Ԃ�
	PlayerType GetPlayerType(void);
	
	void SetAnimationState(std::string str);
	// ������Ă���A�j���[�V�����̖��O�����
	std::string GetNowAnimationName(void);
	// �����̐����ԍ���Ԃ�
	int GetObjectNum(void);
	// �����̈ʒu����Ԃ�
	Float2 GetPos(void);
	// �����̈ʒu����Ԃ�
	void SetPos(Float2 pos);
	// �����̃T�C�Y��Ԃ�
	Float2 GetSize(void);
	// �ߊl�󋵂�ς���
	void SetCatch(int num);
	// ���݂̕ߊl�󋵂�Ԃ�
	int GetCatch(void);

protected:
	// �����ԍ�(0����)
	int objectnumber_;
	// ����
	Raycast raycast_;
	// ���W
	Float2 pos_;
	// �����蔻��̒��S���W
	Float2 colpos_;
	std::map<std::string,std::list<Float2>> colvec_;
	Int2 size_;
	// Draw�̔{��
	float mag_;
	// �ړ��X�s�[�h
	float speed_;
	// �R���g���[�����(keyboard,pad�Ȃ�)
	std::unique_ptr<Controller>controller_;
	//  Tmx�̃f�[�^
	std::shared_ptr<TmxObj> tmx_;
	// �A�j���[�V����
	std::unique_ptr<Animation> anim_;
	// �d��
	float gravity_;
	// �W�����v����
	bool jump_;
	// �d�͂�K�p���邩�ǂ���
	bool gravitybool_;
	// ���݂̃W�����v��
	float jumppow_;
	// �ŏ��̉����x
	float v1;
	// �W�����v���Ăǂ̂��炢�̎��Ԃ�������
	double time_;
	// �R�}���h�Đ����Ă��邩
	bool playcommand_;
	// �R�}���h�̗P�\�t���[���ۑ��p
	int grace_;				// �t���[��
	double gracetime_;		// �b
	// �R�}���h�m�F�̂��߂̈ʒu���
	int commandcount_;

	// �R�}���h���L�^
	RingInputID* commandhis_;
	// �R�}���h���L�^����ʒu���
	int hisnum_;
	// �v���C���[�̎��
	PlayerType pltype_;

	// 0: �S 1 : �߂܂��Ă��Ȃ� 2 : �߂܂���ꂽ 
	int catchflag_;

	friend Move;
	friend CheckKey;
	friend SetAnime;
	friend ColisionCheck;
	friend Jump;
	friend CheckCommand;
	friend Command;
};


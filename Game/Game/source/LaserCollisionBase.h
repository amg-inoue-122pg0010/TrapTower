#pragma once
#include "appframe.h"
#include "ObjectBase.h"
#include <unordered_map>
#include <string>

/**
* @file LaserCollisionBase.h
* @author 井上和哉、酒井大彰
*/

class LaserCollBase : public ObjectBase {
public:
	LaserCollBase();

	virtual void Init() ;

	virtual void Process();

	virtual void Render();

	virtual void CollisionRender();

	void StopEffect();

	LaserCollBase& operator=(LaserCollBase&& las) noexcept;
	enum class Type {
		NONE,
		TRAP,
		CLEAR,
		DAMAGE
	};

	Type GetType() { return _type; };
	void SetType(Type type) { _type = type; }

	enum class Form {
		NONE,
		STRAIGHT,
		CIRCLEHORIZONTAL,
		CIRCLEVERTICAL,
		Move,
	};

	Form GetLaserForm() { return _form; }
	void SetLaserForm(Form form) { _form = form; }

	VECTOR GetstartPos() { return _startVPos; };
	void SetstartPos(VECTOR pos) { _startVPos = pos; };
	VECTOR GetendPos() { return _endVPos; };
	void SetendPos(VECTOR pos) { _endVPos = pos; };
	int Getrad() { return _r; };
	int Setnum(int num) { _num = num; return _num; }
	int GetNum() { return _num; }
	int GetKnockBackTime() { return _knockBackTime; }
	void SetMove(bool move) { _move = move; }
	void SetSwitch(bool s) { _switch = s; }
	void SetTrapNum(std::vector<int> n) { _trapNums = n; }; //どのトラップを起動させるか番号で管理
	std::vector<int> GetTrapNums() { return _trapNums; }
	int GetDamage() { return _damage; };
	void SetColor(int c) { _color = c; };//カプセルの色指定、レーザーのエフェクト出来次第消そう
	void SetStageNum(int n) { _stageNum = n; };
	void SetMovedVPos(VECTOR pos1, VECTOR pos2) {
		_movedStartVPos = pos1;
		_movedEndVPos   = pos2;
	}
	void SetSwitchVPos(VECTOR pos1, VECTOR pos2) {
		 _switchStartVPos = pos1;
		 _switchEndVPos   = pos2;
	}
	void SetSwitchMovedVPos(VECTOR pos1, VECTOR pos2) {
		_switchMovedStartVPos = pos1;
		_switchMovedEndVPos = pos2;
	}
	void SetSpd(float spd) { _spd = spd; }

	//円形レーザー用
	float GetHitRad() { return _hit_r; }
	float GetNoHitRad() { return _nohit_r; }
	float GetCircleHeight() { return _circleHeight; }
	void SetDelay(float delay) { _delay = delay; }
protected:
	int _time;
	//円形レーザー用
	float _hit_r;
	float _nohit_r;
	float _circleHeight;//レーザーの厚さ
	float _circleThick;//レーザーの太さ
	float _delay;	  //ステージスタートから起動するまでの時間
	float _enlarge; //エフェクトの拡縮率
	float _spd;//エフェクトの拡縮、移動の速さ
	int _effectTime; //エフェクトの総再生時間
	int _effectTimeMax;//エフェクトを再生した時間

	//レーザー出力装置のモデル
	int _outputDevice;

	//エフェクト
	int _laserEffectHandle;// エフェクトファイルをロードするハンドル
	int _playingLaserEffectHandle;// ロードしたエフェクトファイルから、エフェクトを生成したもの
	
	VECTOR _startVPos;//当たり判定に使用するカプセルの座標
	VECTOR _endVPos;  //↑
	Form _form;//レーザーの形
	Type _type;//レーザーの種類（ダメージ、トラップ等）
	int _num;
	int _color;//カプセル描画のための色、エフェクト出来次第消そう
	std::vector<int> _trapNums;//起動するトラップの番号
	int _damage;//黄色レーザーの与えるダメージ
	int _knockBackTime;//プレイヤーを吹き飛ばす（プレイヤーが無敵になる）時間
	int _stageNum;//自分が存在するステージ番号
	//動いた後の座標
	bool _move;
	VECTOR _movedStartVPos;
	VECTOR _movedEndVPos;
	//スイッチされた後の座標
	bool _switch;
	VECTOR _switchStartVPos;
	VECTOR _switchEndVPos;
	VECTOR _switchMovedStartVPos;
	VECTOR _switchMovedEndVPos;

	VECTOR _startvPosMoveSpd, _endvPosMoveSpd;//レーザーが移動する速度、カプセルの両端分
	int _moveTime;//移動した時間
	float _turnTime;//直線レーザーが折り返し地点まで移動する時間

	int _red;
	int _blue;
	int _yellow;
	
};

class StraightLaser : public LaserCollBase {
	typedef LaserCollBase base;
public:

	StraightLaser() {
		base::Init();
	};

protected:

};

class CircleLaserHorizontal : public LaserCollBase {
	typedef LaserCollBase base;
public:

	CircleLaserHorizontal();

	void Init();
	void Process();
	void Render();
	void CollisionRender();

protected:
	int _redrin;
	int _bluerin;
	int _yellowrin;
	float _hit_rDifference;//円形レーザーの当たり判定が動く速さ
};

class CircleLaserVertical : public CircleLaserHorizontal {
	typedef CircleLaserHorizontal base;
public:

	CircleLaserVertical();

	void Process();

protected:

};



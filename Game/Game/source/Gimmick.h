#pragma once
#include "ObjectBase.h"
class ModeGame;

/**
* @file Gimmick.h
* @author 井上和哉
*/

class GimmickBase : public ObjectBase {
public:

	GimmickBase(ModeGame& modegame);
	virtual void Init();
	virtual bool Process();
	virtual void HitAction();
	virtual void Render();

	int GetCollBoard();//当たり判定用のモデルを返す

	enum GimmickType {
		FALLROCK,
		APPROACHINGWALL,
		APPROACHINGFLOOR,
		PITFALL,
		MOVINGFLOOR,
		GRAVITYFLOOR,
		SWITCH,
		HAMMER,

	};
	GimmickType _gimmickType;
	GimmickType GetGimmickType() { return _gimmickType; }

	int GetCollFloor() { return _collHandleFloor; }
	int GetCollDamege() { return _collHandleDamage; }
	void SetSpd(float spd) { _spd = spd; }
	std::vector<int> GetCollisions() { return _collisions; }
	void SetNum(int n) { _num = n; }
	int GetNum() { return _num; }
	void SetActivate(bool act) { _activate = act;  }
	bool GetActivate() { return _activate; }
	void SetMovedVPos(VECTOR v) { _movedVPos = v; }
	VECTOR GetVSpd() { return _vSpd; }
	VECTOR GetSphereVPos() { return _sphereVPos; }
	void SetSwitchLaserNum(std::vector<int> nums) { _switchLaserNum = nums; }

protected:
	int _num;
	//当たり判定用のモデル
	int _collHandle;
	int _collHandle_2;
	int _collHandle_3;
	int _collHandle_4;
	int _collHandleFloor;
	int _collHandleDamage;
	//床部分とダメージ部分以外の当たり判定モデルをまとめた配列
	std::vector<int> _collisions;
	bool _activate;//ギミックの動くか否か
	float _spd;//ギミックの動く速度

	VECTOR _movedVPos;//移動後の座標
	VECTOR _vSpd;//床の動く速度
	VECTOR _sphereVPos;//スフィアで当たり判定すると気に使う
	int _effect;
	int _playingEffect;
	std::vector<int> _switchLaserNum;
	ModeGame& _modeGame;
};


//落石
class FallRock : public GimmickBase {
	typedef GimmickBase base;
public:
	FallRock(ModeGame& modeGame);

	void Init();
	bool Process();
	void Render();

protected:

};


//迫る壁
class ApproachingWall : public GimmickBase {
	typedef GimmickBase base;
public:
	ApproachingWall(ModeGame& modeGame);

	void Init();
	bool Process();
	void Render();

protected:
	int _collHandleFloorSecond;

};


//迫る床
class ApproachingFloor : public GimmickBase {
	typedef GimmickBase base;
public:
	ApproachingFloor(ModeGame& modeGame);

	void Init();
	bool Process();
	void Render();

protected:

};


//落とし穴
class Pitfall : public GimmickBase {
	typedef GimmickBase base;
public:

	Pitfall(ModeGame& modeGame);
	void Init();
	bool Process();
	void HitAction();
	void Render();

protected:
	int _activeCnt;//落とし穴が起動するまでの時間計測
	int _activeCntMax;//落とし穴が起動するまでの時間

};


//移動する床
class MovingFloor : public GimmickBase {
	typedef GimmickBase base;
public:

	MovingFloor(ModeGame& modeGame);
	void Init();
	bool Process();
	void HitAction();
	void Render();

protected:
	
};


//重力床
class GravityFloor : public GimmickBase {
	typedef GimmickBase base;
public:

	GravityFloor(ModeGame& modeGame);
	void Init();
	bool Process();
	void HitAction();
	void Render();

protected:

};


//スイッチ
class Switch : public GimmickBase {
	typedef GimmickBase base;
public:

	Switch(ModeGame& modeGame);
	void Init();
	bool Process();
	void HitAction();
	void Render();

protected:
	int _onHandle;//スイッチがオンになった時のモデル
	bool _switch;
	int _alpha;
	int _addAlpha;
};


//振り子ハンマー
class Hammer : public GimmickBase {
	typedef GimmickBase base;
public:

	Hammer(ModeGame& modeGame);
	void Init();
	bool Process();
	void Render();


protected:
	float _handleLength;//柄の長さ
	//振り子の動きの計算用
	float m_Angle;
	float m_Spd;

};
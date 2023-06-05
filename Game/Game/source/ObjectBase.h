#pragma once
#include "appframe.h"
#include "ApplicationMain.h"
#include "../../../AppFrame/Easing.h"

/**
* @file ObjectBase.h
* @brief ゲーム内オブジェクトに共通する変数や関数
* @author 井上和哉
*/

class ObjectBase {
public:
	ObjectBase() {};

	virtual void Init() {
		_r = 25;
		_vPos = VGet(0, 0, 0);
		_life = 3;
		
		_del = false;
		_g = 0;
	};

	VECTOR VMulti(VECTOR a, float b) {
		VECTOR c = a;
		c.x *= b;
		c.y *= b;
		c.z *= b;
		return c;
	};
	
	VECTOR GetvPos() { return _vPos; };
	void SetvPos(VECTOR pos) { _vPos = pos; }
	int Getrad() { return _r; };
	int Getlife() { return _life; };
	void Setlife(int life) {_life = life; };
	int Getspd() { return _spd; }
	void SetSpd(int spd) { _spd = spd; }
	VECTOR SetvDir(VECTOR dir) {
		_vDir = dir;
		return _vDir;
	}
	VECTOR GetvDir() { return _vDir; }

	bool GetDel() { return _del; }
	

	enum class Otype {
		none,
		enemy,
		sphere,
		gate,
	};
	Otype _otype;
	bool Checkotype(Otype type) {
		if (_otype == type) {
			return true;
		}
		return false;
	}
	int _handle;
	
	bool Getinput() { return _input; }
	int GetG() { return _g; }

protected:
	int _life;
	int _r;//円や球の当たり判定に使う半径
	VECTOR _vPos;
	float _spd;
	VECTOR _vDir;
	bool _input; 
	int _g;//重力
	bool _del;//オブジェクトを削除するかどうか
	int _cnt;//カウント
};


#pragma once
#include "ObjectBase.h"
class ModeGame;

/**
* @file Gimmick.h
* @author ���a��
*/

class GimmickBase : public ObjectBase {
public:

	GimmickBase(ModeGame& modegame);
	virtual void Init();
	virtual bool Process();
	virtual void HitAction();
	virtual void Render();

	int GetCollBoard();//�����蔻��p�̃��f����Ԃ�

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
	//�����蔻��p�̃��f��
	int _collHandle;
	int _collHandle_2;
	int _collHandle_3;
	int _collHandle_4;
	int _collHandleFloor;
	int _collHandleDamage;
	//�������ƃ_���[�W�����ȊO�̓����蔻�胂�f�����܂Ƃ߂��z��
	std::vector<int> _collisions;
	bool _activate;//�M�~�b�N�̓������ۂ�
	float _spd;//�M�~�b�N�̓������x

	VECTOR _movedVPos;//�ړ���̍��W
	VECTOR _vSpd;//���̓������x
	VECTOR _sphereVPos;//�X�t�B�A�œ����蔻�肷��ƋC�Ɏg��
	int _effect;
	int _playingEffect;
	std::vector<int> _switchLaserNum;
	ModeGame& _modeGame;
};


//����
class FallRock : public GimmickBase {
	typedef GimmickBase base;
public:
	FallRock(ModeGame& modeGame);

	void Init();
	bool Process();
	void Render();

protected:

};


//�����
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


//���鏰
class ApproachingFloor : public GimmickBase {
	typedef GimmickBase base;
public:
	ApproachingFloor(ModeGame& modeGame);

	void Init();
	bool Process();
	void Render();

protected:

};


//���Ƃ���
class Pitfall : public GimmickBase {
	typedef GimmickBase base;
public:

	Pitfall(ModeGame& modeGame);
	void Init();
	bool Process();
	void HitAction();
	void Render();

protected:
	int _activeCnt;//���Ƃ������N������܂ł̎��Ԍv��
	int _activeCntMax;//���Ƃ������N������܂ł̎���

};


//�ړ����鏰
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


//�d�͏�
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


//�X�C�b�`
class Switch : public GimmickBase {
	typedef GimmickBase base;
public:

	Switch(ModeGame& modeGame);
	void Init();
	bool Process();
	void HitAction();
	void Render();

protected:
	int _onHandle;//�X�C�b�`���I���ɂȂ������̃��f��
	bool _switch;
	int _alpha;
	int _addAlpha;
};


//�U��q�n���}�[
class Hammer : public GimmickBase {
	typedef GimmickBase base;
public:

	Hammer(ModeGame& modeGame);
	void Init();
	bool Process();
	void Render();


protected:
	float _handleLength;//���̒���
	//�U��q�̓����̌v�Z�p
	float m_Angle;
	float m_Spd;

};
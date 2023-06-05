#pragma once
#include "appframe.h"
#include "ObjectBase.h"
#include <unordered_map>
#include <string>

/**
* @file LaserCollisionBase.h
* @author ���a�ƁA����史
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
	void SetTrapNum(std::vector<int> n) { _trapNums = n; }; //�ǂ̃g���b�v���N�������邩�ԍ��ŊǗ�
	std::vector<int> GetTrapNums() { return _trapNums; }
	int GetDamage() { return _damage; };
	void SetColor(int c) { _color = c; };//�J�v�Z���̐F�w��A���[�U�[�̃G�t�F�N�g�o�����������
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

	//�~�`���[�U�[�p
	float GetHitRad() { return _hit_r; }
	float GetNoHitRad() { return _nohit_r; }
	float GetCircleHeight() { return _circleHeight; }
	void SetDelay(float delay) { _delay = delay; }
protected:
	int _time;
	//�~�`���[�U�[�p
	float _hit_r;
	float _nohit_r;
	float _circleHeight;//���[�U�[�̌���
	float _circleThick;//���[�U�[�̑���
	float _delay;	  //�X�e�[�W�X�^�[�g����N������܂ł̎���
	float _enlarge; //�G�t�F�N�g�̊g�k��
	float _spd;//�G�t�F�N�g�̊g�k�A�ړ��̑���
	int _effectTime; //�G�t�F�N�g�̑��Đ�����
	int _effectTimeMax;//�G�t�F�N�g���Đ���������

	//���[�U�[�o�͑��u�̃��f��
	int _outputDevice;

	//�G�t�F�N�g
	int _laserEffectHandle;// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int _playingLaserEffectHandle;// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	
	VECTOR _startVPos;//�����蔻��Ɏg�p����J�v�Z���̍��W
	VECTOR _endVPos;  //��
	Form _form;//���[�U�[�̌`
	Type _type;//���[�U�[�̎�ށi�_���[�W�A�g���b�v���j
	int _num;
	int _color;//�J�v�Z���`��̂��߂̐F�A�G�t�F�N�g�o�����������
	std::vector<int> _trapNums;//�N������g���b�v�̔ԍ�
	int _damage;//���F���[�U�[�̗^����_���[�W
	int _knockBackTime;//�v���C���[�𐁂���΂��i�v���C���[�����G�ɂȂ�j����
	int _stageNum;//���������݂���X�e�[�W�ԍ�
	//��������̍��W
	bool _move;
	VECTOR _movedStartVPos;
	VECTOR _movedEndVPos;
	//�X�C�b�`���ꂽ��̍��W
	bool _switch;
	VECTOR _switchStartVPos;
	VECTOR _switchEndVPos;
	VECTOR _switchMovedStartVPos;
	VECTOR _switchMovedEndVPos;

	VECTOR _startvPosMoveSpd, _endvPosMoveSpd;//���[�U�[���ړ����鑬�x�A�J�v�Z���̗��[��
	int _moveTime;//�ړ���������
	float _turnTime;//�������[�U�[���܂�Ԃ��n�_�܂ňړ����鎞��

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
	float _hit_rDifference;//�~�`���[�U�[�̓����蔻�肪��������
};

class CircleLaserVertical : public CircleLaserHorizontal {
	typedef CircleLaserHorizontal base;
public:

	CircleLaserVertical();

	void Process();

protected:

};



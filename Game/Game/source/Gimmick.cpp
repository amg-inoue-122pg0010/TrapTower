#include "Gimmick.h"
#include <stdlib.h>
#include "ModeGame.h"

/**
* @file Gimmick.cpp
* @brief �X�e�[�W�M�~�b�N�̓����蔻��⓮��
* @author ���a��
*/

GimmickBase::GimmickBase(ModeGame& modeGame)
	:_modeGame(modeGame)
{

}

void GimmickBase::Init() {
	_g = 0;
	_activate = false;
	_spd = 0;
	_movedVPos = VGet(0, 0, 0);
	_cnt = 0;
	_collHandleDamage = -1;

	_playingEffect = -1;
}

bool GimmickBase::Process() {

	// �Đ����̃G�t�F�N�g���ړ�����B
	SetPosPlayingEffekseer3DEffect(_playingEffect, _vPos.x, _vPos.y, _vPos.z);

	++_cnt;
	//���f��
	MV1SetPosition(_handle, _vPos);
	return true;
}

void GimmickBase::HitAction() {
}


void GimmickBase::Render() {
	MV1DrawModel(_handle);
}

int GimmickBase::GetCollBoard() {
	 return MV1DuplicateModel(ResourceServer::GetHandles("CollBoard"));
}

//����
FallRock::FallRock(ModeGame& modeGame)
	: base(modeGame) 
{
	
	Init();
}

void FallRock::Init() {

	base::Init();

	_collHandle = base::GetCollBoard();
	_collHandle_2 = MV1DuplicateModel(_collHandle);
	_collHandle_3 = MV1DuplicateModel(_collHandle);
	_collHandle_4 = MV1DuplicateModel(_collHandle);
	_collHandleFloor = MV1DuplicateModel(_collHandle);
	_collHandleDamage = MV1DuplicateModel(_collHandle);

	_handle = ResourceServer::GetHandles("FallRock");
	_gimmickType = GimmickType::FALLROCK;
	//��
	MV1SetScale(_collHandle, VGet(170, 0, 20));
	MV1SetScale(_collHandle_2, VGet(170, 0, 20));
	MV1SetScale(_collHandle_3, VGet(170, 0, 20));
	MV1SetScale(_collHandle_4, VGet(170, 0, 20));

	auto angle = -Math::ToRadians(90);
	MV1SetRotationXYZ(_collHandle, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_2, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_3, VGet(0, 0, angle));
	MV1SetRotationXYZ(_collHandle_4, VGet(0, 0, angle));

	_collisions.push_back(_collHandle);
	_collisions.push_back(_collHandle_2);
	_collisions.push_back(_collHandle_3);
	_collisions.push_back(_collHandle_4);

	//���΂̏�ʂƉ���
	MV1SetScale(_collHandleFloor, VGet(170, 150, 20));
	MV1SetScale(_collHandleDamage, VGet(170, 150, 20));

}

bool FallRock::Process(){
	base::Process();

	if (_activate == true && _vPos.y > -50) {//�t���O��true�������؂��Ă��Ȃ�������
		++_g;
		_vPos.y -= _g;
	}


	//�����蔻��̔�
	
	MV1SetPosition(_collisions[0], VGet(_vPos.x, _vPos.y + 120, _vPos.z - 100));
	MV1SetPosition(_collisions[1], VGet(_vPos.x, _vPos.y + 120, _vPos.z + 100));
	MV1SetPosition(_collisions[2], VGet(_vPos.x - 100 , _vPos.y + 120, _vPos.z));
	MV1SetPosition(_collisions[3], VGet(_vPos.x + 100 , _vPos.y + 120, _vPos.z));
	
	MV1SetPosition(_collHandleFloor, VGet(_vPos.x, _vPos.y + 220, _vPos.z));
	MV1SetPosition(_collHandleDamage, _vPos);

	for (auto e : _collisions) {
		MV1RefreshCollInfo(e, 0);
	}
	MV1RefreshCollInfo(_collHandleFloor, 0);
	MV1RefreshCollInfo(_collHandleDamage, 0);
	return true;
}

void FallRock::Render() {
	base::Render();

}


//�����
ApproachingWall::ApproachingWall(ModeGame& modeGame)
	: base(modeGame)
{
	Init();
}

void ApproachingWall::Init() {

	base::Init();
	_r = 150;
	auto angle = -Math::ToRadians(90);
	_collHandle = base::GetCollBoard();
	_collHandle_2 = MV1DuplicateModel(_collHandle);
	_collHandle_3 = MV1DuplicateModel(_collHandle);
	_collHandleFloor = MV1DuplicateModel(_collHandle);
	_collHandleFloorSecond = MV1DuplicateModel(_collHandle);

	_gimmickType = GimmickType::APPROACHINGWALL;
	_handle = ResourceServer::GetHandles("ApproachingWall");
	MV1SetScale(_handle, VGet(0.5, 0.5, 0.5));
	MV1SetRotationXYZ(_handle, VGet(0, 0, -angle));
	//��
	MV1SetScale(_collHandle,   VGet(210, 0, 31));
	MV1SetScale(_collHandle_2, VGet(210, 0, 31));
	MV1SetScale(_collHandle_3, VGet(210, 0, 31));

	MV1SetRotationXYZ(_collHandle, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_2, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_3, VGet(0, 0, angle));

	_collisions.push_back(_collHandle);
	_collisions.push_back(_collHandle_2);
	_collisions.push_back(_collHandle_3);

	//���΂̏�ʂƉ���
	MV1SetScale(_collHandleFloor, VGet(210, 0, 31));
	MV1SetScale(_collHandleFloorSecond, VGet(210, 0, 31));
	_collisions.push_back(_collHandleFloorSecond);

}

bool ApproachingWall::Process() {
	base::Process();
	
	
	if (_vPos.x < 500 && _activate == true) {
		_vPos.x += _spd;
	}
	_sphereVPos = _vPos;
	_sphereVPos.x += 170;

	//�����蔻��̔�
	MV1SetPosition(_collisions[0], VGet(_vPos.x, _vPos.y + 25, _vPos.z - 160));
	MV1SetPosition(_collisions[1], VGet(_vPos.x, _vPos.y + 25, _vPos.z + 160));
	MV1SetPosition(_collisions[2], VGet(_vPos.x - 160, _vPos.y + 25, _vPos.z));
	
	MV1SetPosition(_collHandleFloor, VGet(_vPos.x, _vPos.y + 130, _vPos.z));

	for (auto e : _collisions) {
		MV1RefreshCollInfo(e, 0);
	}
	MV1RefreshCollInfo(_collHandleFloor, 0);

	return true;
}

void ApproachingWall::Render() {
	base::Render();
	for (auto e : _collisions) {
		MV1DrawModel(e);
	}
	MV1DrawModel(_collHandleFloor);
}


//����V��
ApproachingFloor::ApproachingFloor(ModeGame& modeGame)
	: base(modeGame)
{
	Init();
}

void ApproachingFloor::Init() {

	base::Init();
	_r = 150;
	auto angle = -Math::ToRadians(90);
	_collHandle = base::GetCollBoard();
	_collHandle_2 = MV1DuplicateModel(_collHandle);
	_collHandle_3 = MV1DuplicateModel(_collHandle);
	_collHandleFloor = MV1DuplicateModel(_collHandle);
	auto _collHandle_4 = MV1DuplicateModel(_collHandle);
	
	_gimmickType = GimmickType::APPROACHINGFLOOR;
	_handle = ResourceServer::GetHandles("ApproachingWall");
	MV1SetScale(_handle, VGet(0.5, 0.5, 0.5));
	//��
	MV1SetScale(_collHandle, VGet(210, 0, 31));
	MV1SetScale(_collHandle_2, VGet(210, 0, 31));
	MV1SetScale(_collHandle_3, VGet(210, 0, 31));
	MV1SetScale(_collHandle_4, VGet(210, 0, 31));

	MV1SetRotationXYZ(_collHandle, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_2, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_3, VGet(0, 0, angle));
	MV1SetRotationXYZ(_collHandle_4, VGet(0, 0, angle));

	_collisions.push_back(_collHandle);
	_collisions.push_back(_collHandle_2);
	_collisions.push_back(_collHandle_3);
	_collisions.push_back(_collHandle_4);

	//���΂̏�ʂƉ���
	MV1SetScale(_collHandleFloor, VGet(240, 0, 31));
}

bool ApproachingFloor::Process() {
	base::Process();

	if (_vPos.y > 50 && _activate == true) {
		_vPos.x += _spd;
	}
	_sphereVPos = _vPos;
	_sphereVPos.y -= 170;
	
	//�����蔻��̔�
	MV1SetPosition(_collisions[0], VGet(_vPos.x, _vPos.y + 25, _vPos.z - 160));
	MV1SetPosition(_collisions[1], VGet(_vPos.x, _vPos.y + 25, _vPos.z + 160));
	MV1SetPosition(_collisions[2], VGet(_vPos.x - 160, _vPos.y + 25, _vPos.z));
	MV1SetPosition(_collisions[3], VGet(_vPos.x + 160, _vPos.y + 25, _vPos.z));

	MV1SetPosition(_collHandleFloor, VGet(_vPos.x, _vPos.y + 130, _vPos.z));

	for (auto e : _collisions) {
		MV1RefreshCollInfo(e, 0);
	}
	MV1RefreshCollInfo(_collHandleFloor, 0);

	return true;
}

void ApproachingFloor::Render() {
	base::Render();

}


//���Ƃ���
Pitfall::Pitfall(ModeGame& modeGame)
	: base(modeGame)
{
	Init();
}

void Pitfall::Init() {

	base::Init();
	_gimmickType = GimmickType::PITFALL;
	_activeCnt = 0;
	_collHandleFloor = base::GetCollBoard();
	MV1SetScale(_collHandleFloor, VGet(300, 0, 30));
	_activeCntMax = 120;

	_effect = LoadEffekseerEffect("res/Effect/PlayerEffect/ef_pitfall/ef_pitfall.efkefc", 50.0f);

}

bool Pitfall::Process() {
	base::Process();

	if (_activate == true) {
		++_activeCnt;

		if (_playingEffect == -1) {
			_playingEffect = PlayEffekseer3DEffect(_effect);
		}

		if (_activeCnt > _activeCntMax) {
			_collHandleFloor = -1;
		}
	}

	MV1SetPosition(_collHandleFloor, _vPos);
	return true;
}

void Pitfall::HitAction() {
	_activate = true;
}

void Pitfall::Render() {
	MV1DrawModel(_collHandleFloor);
}


//�ړ����鏰
MovingFloor::MovingFloor(ModeGame& modeGame)
	: base(modeGame)
{
	Init();
}

void MovingFloor::Init() {

	base::Init();
	_handle = ResourceServer::GetHandles("MovingFloor");
	_collHandleFloor = base::GetCollBoard();
	MV1SetScale(_collHandleFloor, VGet(300, 0, 30));
	_gimmickType = GimmickType::MOVINGFLOOR;
	_vSpd = VGet(0, 0, 0);

}

bool MovingFloor::Process() {
	base::Process();

	float mtime = 300.f;//�܂�Ԃ��n�_�܂ł̎���
	//�ړ����x��0�Ȃ�
	if (VSize(VSub(_vSpd, VGet(0, 0, 0))) == 0) {
		//�ړ��O����ړ���܂ł̋���
		VECTOR a = VSub(_movedVPos, _vPos);
		//���xfloat
		float b = VSize(a) / mtime;
		//���xvector
		_vSpd = VMulti(VNorm(a), b);
	}

	_vPos = VAdd(_vPos, _vSpd);
	if (_cnt % (int)mtime == 0) {
		_vSpd = VMulti(_vSpd, -1);
	}
	MV1SetPosition(_collHandleFloor, _vPos);
	MV1RefreshCollInfo(_collHandleFloor, 0);
	return true;
}

void MovingFloor::HitAction() {
	_modeGame._player.SetvPos(VAdd(_modeGame._player.GetvPos(), _vSpd));
}

void MovingFloor::Render() {
	base::Render();

}


//�d�͏�
GravityFloor::GravityFloor(ModeGame& modeGame)
	: base(modeGame)
{
	Init();
}

void GravityFloor::Init() {

	base::Init();
	_handle = ResourceServer::GetHandles("GravityFloor");
	_collHandleFloor = base::GetCollBoard();
	auto angle = -Math::ToRadians(90);
	MV1SetScale(_collHandleFloor, VGet(300, 0, 30));
	_gimmickType = GimmickType::GRAVITYFLOOR;
}

bool GravityFloor::Process() {
	base::Process();

	MV1SetPosition(_collHandleFloor, _vPos);
	return true;
}

void GravityFloor::HitAction(){
	_modeGame._player.SetvPos(VSub(_modeGame._player.GetvPos(), 
		VMulti(_modeGame._player.GetMovement(), 0.5)));
}

void GravityFloor::Render() {
	base::Render();

}


//�X�C�b�`
Switch::Switch(ModeGame& modeGame)
	: base(modeGame)

{
	Init();
}

void Switch::Init() {

	base::Init();
	_handle = ResourceServer::GetHandles("Switch");
	_onHandle = ResourceServer::GetHandles("SwitchOn");

	_collHandleFloor = base::GetCollBoard();
	MV1SetScale(_collHandleFloor, VGet(300, 0, 30));
	_gimmickType = GimmickType::SWITCH;
	_switch = false;
	_alpha = 0;
	_addAlpha = 3;
}

bool Switch::Process() {
	base::Process();

	if (_activate) {
		_alpha += _addAlpha;
		if (_alpha > 250) {
			_switch = true;
			_addAlpha *= -1;
		}
	}

	if (_switch) {
		int num = _switchLaserNum[0];
		for (auto e : _modeGame.lasers) {
			if (e->GetNum() == num) {
				e->SetSwitch(true);
				++num;
			}
		}
		_switch = false;
	}

	MV1SetPosition(_onHandle, _vPos);
	MV1SetPosition(_collHandleFloor, _vPos);
	return true;
}

void Switch::HitAction() {
	_activate = true;
}

void Switch::Render() {
	switch (_activate)
	{
	case true:
		MV1DrawModel(_onHandle);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawBox(0, 0, 1920, 1080,
			GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case false:
		base::Render();
		break;
	default:
		break;
	}
	
}



//�U��q�n���}�[
Hammer::Hammer(ModeGame& modeGame)
	: base(modeGame)
{
	Init();
}

void Hammer::Init() {

	base::Init();
	_handle = ResourceServer::GetHandles("Hammer");
	MV1SetScale(_handle, VGet(0.5, 0.5, 0.5));
	MV1SetRotationXYZ(_handle, VGet(0, 0, Math::ToRadians(-90)));
	_gimmickType = GimmickType::HAMMER;
	_r = 180; 
	_handleLength = 550;
	_sphereVPos = VGet(0, 0, 0);
	m_Angle = -180;
	m_Spd = 0;
}

bool Hammer::Process() {
	base::Process();
	_sphereVPos = _vPos;
	if (_activate) {
		
		//�ɍ��W�Ɏg���p�x�̍X�V
		float add_spd = 0.01;
		if (m_Angle > -90) {
			m_Spd -= add_spd;
		}
		else {
			m_Spd += add_spd;
		}
		m_Angle += m_Spd;
		auto dir = VGet(0, 0, 0);
		dir.z += Math::ToRadians(m_Angle + 90);
		MV1SetRotationXYZ(_handle, dir);
	}

	//�ɍ��W�Ŕ��~�ł̈ʒu�����߂�
	float m_Length = _handleLength;	// ���a�̒���
	float m_CenterX = _vPos.x;	// ���S���WX
	float m_CenterY = _vPos.y;	// ���S���WY
	// ���S���W�Ɋp�x�ƒ������g�p�����~�̈ʒu�����Z����
	// �x���@�̊p�x���ʓx�@�ɕϊ�
	float radius = m_Angle * 3.14f / 180.0f;

	// �O�p�֐����g�p���A�~�̈ʒu������o���B
	float add_x = cos(radius) * m_Length;
	float add_y = sin(radius) * m_Length;

	// ���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
	_sphereVPos.x = m_CenterX + add_x;
	_sphereVPos.y = m_CenterY + add_y;

	return true;
}

void Hammer::Render() {
	base::Render();

}



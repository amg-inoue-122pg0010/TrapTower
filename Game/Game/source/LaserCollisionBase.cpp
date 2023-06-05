#include "LaserCollisionBase.h"
#include "AppFrame.h"

/**
* @file LaserCollisionBase.cpp
* @brief レーザーの当たり判定や動き
* @author 井上和哉、酒井大彰
*/

LaserCollBase::LaserCollBase() {
	Init();
}

void LaserCollBase::Init() {
	_startVPos = VGet(0, 0, 0);
	_endVPos = VGet(0, 0, 0);
	_num = 0;
	_r = 3;
	_damage = 1;
	_knockBackTime = 60;
	_move = false;
	_switch = false;
	_laserEffectHandle = -1;
	_playingLaserEffectHandle = -1;
	_moveTime = 0;
	_time = 0;
	_outputDevice = ResourceServer::GetHandles("OutputDeviceStraight");

	_red = LoadEffekseerEffect("res/Effect/ef_st_laser_red/ef_st_laser_red.efkefc", 50.0f);
	_blue = LoadEffekseerEffect("res/Effect/ef_st_laser_blue/ef_st_laser_blue.efkefc", 50.0f);
	_yellow = LoadEffekseerEffect("res/Effect/ef_st_laser_yellow/ef_st_laser_yellow.efkefc", 50.0f);
}

void LaserCollBase::Process() {
	++_time;

	if (_laserEffectHandle == -1) {
		switch (_type)
		{
		case LaserCollBase::Type::TRAP:
			_laserEffectHandle = _red;
			break;
		case LaserCollBase::Type::CLEAR:
			_laserEffectHandle = _blue;
			break;
		case LaserCollBase::Type::DAMAGE:
			_laserEffectHandle = _yellow;
			break;
		default:
			break;
		}
		SetScalePlayingEffekseer3DEffect(_laserEffectHandle, 2, 1, 1);
	}
	if (_switch) {
		_startVPos = _switchStartVPos;
		_endVPos = _switchEndVPos;
		_movedStartVPos = _switchMovedStartVPos;
		_movedEndVPos = _switchMovedEndVPos;
		_time = 1;
		//速度を設定しなおす
		auto a = VSub(_movedStartVPos, _startVPos);
		float b = VSize(a) / _turnTime;
		_startvPosMoveSpd = VMulti(VNorm(a), b);
		a = VSub(_movedEndVPos, _endVPos);
		b = VSize(a) / _turnTime;
		_endvPosMoveSpd = VMulti(VNorm(a), b);
		_switch = false;
	}

	if (_time == 1) {
		_turnTime = 100.f / _spd;
		//カプセルの両端の座標が動く速さを計算する
		//折り返し地点までの距離
		auto a = VSub(_movedStartVPos, _startVPos);
		//速度float
		float b = VSize(a) / _turnTime;
		//速度vector
		_startvPosMoveSpd = VMulti(VNorm(a), b);

		a = VSub(_movedEndVPos, _endVPos);
		b = VSize(a) / _turnTime;
		_endvPosMoveSpd = VMulti(VNorm(a), b);
	}
	

	
	if (_delay != 0) {
		--_delay;
	}
	else {
		if (_moveTime == (int)_turnTime) {//時間になったら折り返す
			_startvPosMoveSpd = VMulti(_startvPosMoveSpd, -1);
			_endvPosMoveSpd = VMulti(_endvPosMoveSpd, -1);
			_moveTime = 0;
		}
		if (_move == true) {
			_startVPos = VAdd(_startVPos, _startvPosMoveSpd);
			_endVPos = VAdd(_endVPos, _endvPosMoveSpd);
			++_moveTime;
		}
	}

	//エフェクトの再生時間終了（101f）と同時にもう一度再生
	if (_time % 101 == 0 || _time == 1) {
		_playingLaserEffectHandle = PlayEffekseer3DEffect(_laserEffectHandle);
		SetScalePlayingEffekseer3DEffect(_playingLaserEffectHandle, 1, 1, 3);
	}
	SetPosPlayingEffekseer3DEffect(_playingLaserEffectHandle, _startVPos.x, _startVPos.y, _startVPos.z);
	
	//Y軸(xz)とZ軸(xy)それぞれ内積でエフェクトを回転させる角度を割り出す
	VECTOR dir = VSub(_startVPos, _endVPos);
	VECTOR vx, vz;
	vx = VGet(dir.x, dir.y, dir.z);//dir;
	vz = VGet(0, 0, 1);
	float rady = acos(VDot(vx, vz) / (VSize(vx) * VSize(vz)));
	
	VECTOR vy = VGet(0, 1, 0);
	float radz = acos(VDot(vx, vy) / (VSize(vx) * VSize(vy)));

	auto k = VDot(vx, vy) / (VSize(vx) * VSize(vy));

	radz -= Math::ToRadians(90);
	

	SetRotationPlayingEffekseer3DEffect(_playingLaserEffectHandle, radz, -rady, 0);

	MV1SetPosition(_outputDevice, _startVPos);
	float xdif = (_endVPos.x - _startVPos.x) / 2;
	VECTOR vpos = VGet(_startVPos.x + xdif, _startVPos.y, _startVPos.z);

	MV1RefreshCollInfo(_outputDevice, 0);

}

void LaserCollBase::Render() {
	MV1DrawModel(_outputDevice);

	//レーザーの下に影っぽくカプセルを描画

	SetDrawBlendMode(DX_BLENDMODE_ADD, 50);
	float y = -5;
	DrawCapsule3D(VGet(_startVPos.x, y, _startVPos.z), 
		VGet(_endVPos.x, y, _endVPos.z), 10, 16, _color, _color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
}

void LaserCollBase::CollisionRender() {
	DrawCapsule3D(_startVPos, _endVPos, _r, 16, _color, _color, TRUE);
}

void LaserCollBase::StopEffect() {
	StopEffekseer3DEffect(_playingLaserEffectHandle);
}




CircleLaserHorizontal::CircleLaserHorizontal() {
	Init();
}

void CircleLaserHorizontal::Init() {
	base::Init();
	_enlarge = 1.0f;
	_effectTimeMax = 0;
	_hit_rDifference = 10;
	_circleThick = 20;
	_hit_r = 0;
	_nohit_r = 0;
	_circleHeight = 3;
	_outputDevice = ResourceServer::GetHandles("OutputDeviceCircle");
	_redrin = LoadEffekseerEffect("res/Effect/ef_rin_laser_red/ef_laser_ring_red.efkefc", 50.0f);
	_bluerin = LoadEffekseerEffect("res/Effect/ef_rin_laser_blue/ef_laser_ring_blue.efkefc", 50.0f);
	_yellowrin = LoadEffekseerEffect("res/Effect/ef_rin_laser_yellow/ef_laser_ring_yellow.efkefc", 50.0f);
}

void CircleLaserHorizontal::Process() {
	if (_delay != 0) {
		--_delay;
		return;
	}
	++_time;
	++_effectTime;
	_effectTimeMax = 101 / _spd;//エフェクトの再生時間が101f
	_nohit_r = _hit_r - _circleThick;
	if (_laserEffectHandle == -1) {
		switch (_type)
		{
		case LaserCollBase::Type::TRAP:
			_laserEffectHandle = _redrin;
			break;
		case LaserCollBase::Type::CLEAR:
			_laserEffectHandle = _bluerin;
			break;
		case LaserCollBase::Type::DAMAGE:
			_laserEffectHandle = _yellowrin;
			break;
		default:
			break;
		}
	}

	//円が縮小しきったら、再生していたエフェクトを停止して新しく再生する
	if (_playingLaserEffectHandle == -1 || _hit_r < 0) {
		StopEffekseer3DEffect(_playingLaserEffectHandle);
		_playingLaserEffectHandle = PlayEffekseer3DEffect(_laserEffectHandle);
		SetSpeedPlayingEffekseer3DEffect(_playingLaserEffectHandle, _spd);
		_effectTime = 0;
		_enlarge = 1.0f;
	}

	//エフェクトの再生速度を下げ、拡大率を下げることで小さくなっているように見せる
	if (_effectTime > _effectTimeMax / 2) {
		SetSpeedPlayingEffekseer3DEffect(_playingLaserEffectHandle, 0.0000001);
		SetScalePlayingEffekseer3DEffect(_playingLaserEffectHandle, _enlarge, 1, _enlarge);
		_enlarge -= 0.02f * _spd;
		_hit_r -= _hit_rDifference * _spd;
	}
	else {
		_hit_r += _hit_rDifference * _spd;
	}


	SetPosPlayingEffekseer3DEffect(_playingLaserEffectHandle, _vPos.x, _vPos.y, _vPos.z);

	MV1SetPosition(_outputDevice, _vPos);
	MV1RefreshCollInfo(_outputDevice, 0);
}

void CircleLaserHorizontal::Render() {

	MV1DrawModel(_outputDevice);

}

void CircleLaserHorizontal::CollisionRender() {

	DrawSphere3D(_vPos, _hit_r, 16, _color, _color, false);//ダメージ円
	DrawSphere3D(_vPos, _nohit_r, 16, _color, _color, false);//回避円
	DrawLine3D(_vPos, VGet(_vPos.x, _vPos.y + _circleHeight, _vPos.z), _color);
}



CircleLaserVertical::CircleLaserVertical() {
	base::Init();
}


void CircleLaserVertical::Process() {
	if (_delay != 0) {
		--_delay;
		return;
	}
	++_time;
	++_effectTime;
	_effectTimeMax = 101 / _spd;//エフェクトの再生時間が101f
	_nohit_r = _hit_r - _circleThick;
	if (_laserEffectHandle == -1) {
		switch (_type)
		{
		case LaserCollBase::Type::TRAP:
			_laserEffectHandle = _redrin;
			break;
		case LaserCollBase::Type::CLEAR:
			_laserEffectHandle = _bluerin;
			break;
		case LaserCollBase::Type::DAMAGE:
			_laserEffectHandle = _yellowrin;
			break;
		default:
			break;
		}
	}
	
	//円が縮小しきったら、再生していたエフェクトを停止して新しく再生する
	if (_playingLaserEffectHandle == -1 || _hit_r < 0) {
		StopEffekseer3DEffect(_playingLaserEffectHandle);
		_playingLaserEffectHandle = PlayEffekseer3DEffect(_laserEffectHandle);

		SetRotationPlayingEffekseer3DEffect(_playingLaserEffectHandle, Math::ToRadians(90), 0, 0);

		SetSpeedPlayingEffekseer3DEffect(_playingLaserEffectHandle, _spd);
		_effectTime = 0;
		_enlarge = 1.0f;
	}

	//エフェクトの再生速度を下げ、拡大率を下げることで小さくなっているように見せる
	if (_effectTime > _effectTimeMax / 2) {
		SetSpeedPlayingEffekseer3DEffect(_playingLaserEffectHandle, 0.0000001);
		SetScalePlayingEffekseer3DEffect(_playingLaserEffectHandle, _enlarge, 1, _enlarge);
		_enlarge -= 0.02f * _spd;
		_hit_r -= _hit_rDifference * _spd;
	}
	else {
		_hit_r += _hit_rDifference * _spd;
	}


	SetPosPlayingEffekseer3DEffect(_playingLaserEffectHandle, _vPos.x, _vPos.y, _vPos.z);

	MV1SetPosition(_outputDevice, _vPos);
	MV1RefreshCollInfo(_outputDevice, 0);
}





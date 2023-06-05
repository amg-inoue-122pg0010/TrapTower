#include "Gimmick.h"
#include <stdlib.h>
#include "ModeGame.h"

/**
* @file Gimmick.cpp
* @brief ステージギミックの当たり判定や動き
* @author 井上和哉
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

	// 再生中のエフェクトを移動する。
	SetPosPlayingEffekseer3DEffect(_playingEffect, _vPos.x, _vPos.y, _vPos.z);

	++_cnt;
	//モデル
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

//落石
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
	//壁
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

	//落石の上面と下面
	MV1SetScale(_collHandleFloor, VGet(170, 150, 20));
	MV1SetScale(_collHandleDamage, VGet(170, 150, 20));

}

bool FallRock::Process(){
	base::Process();

	if (_activate == true && _vPos.y > -50) {//フラグがtrueかつ落ち切っていなかったら
		++_g;
		_vPos.y -= _g;
	}


	//当たり判定の板
	
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


//迫る壁
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
	//壁
	MV1SetScale(_collHandle,   VGet(210, 0, 31));
	MV1SetScale(_collHandle_2, VGet(210, 0, 31));
	MV1SetScale(_collHandle_3, VGet(210, 0, 31));

	MV1SetRotationXYZ(_collHandle, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_2, VGet(angle, 0, angle));
	MV1SetRotationXYZ(_collHandle_3, VGet(0, 0, angle));

	_collisions.push_back(_collHandle);
	_collisions.push_back(_collHandle_2);
	_collisions.push_back(_collHandle_3);

	//落石の上面と下面
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

	//当たり判定の板
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


//迫る天井
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
	//壁
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

	//落石の上面と下面
	MV1SetScale(_collHandleFloor, VGet(240, 0, 31));
}

bool ApproachingFloor::Process() {
	base::Process();

	if (_vPos.y > 50 && _activate == true) {
		_vPos.x += _spd;
	}
	_sphereVPos = _vPos;
	_sphereVPos.y -= 170;
	
	//当たり判定の板
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


//落とし穴
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


//移動する床
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

	float mtime = 300.f;//折り返し地点までの時間
	//移動速度が0なら
	if (VSize(VSub(_vSpd, VGet(0, 0, 0))) == 0) {
		//移動前から移動後までの距離
		VECTOR a = VSub(_movedVPos, _vPos);
		//速度float
		float b = VSize(a) / mtime;
		//速度vector
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


//重力床
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


//スイッチ
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



//振り子ハンマー
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
		
		//極座標に使う角度の更新
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

	//極座標で半円での位置を求める
	float m_Length = _handleLength;	// 半径の長さ
	float m_CenterX = _vPos.x;	// 中心座標X
	float m_CenterY = _vPos.y;	// 中心座標Y
	// 中心座標に角度と長さを使用した円の位置を加算する
	// 度数法の角度を弧度法に変換
	float radius = m_Angle * 3.14f / 180.0f;

	// 三角関数を使用し、円の位置を割り出す。
	float add_x = cos(radius) * m_Length;
	float add_y = sin(radius) * m_Length;

	// 結果ででた位置を中心位置に加算し、それを描画位置とする
	_sphereVPos.x = m_CenterX + add_x;
	_sphereVPos.y = m_CenterY + add_y;

	return true;
}

void Hammer::Render() {
	base::Render();

}



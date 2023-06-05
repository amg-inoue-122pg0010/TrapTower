
/**
* @file doxygen_sample.cxx
* @brief ファイルの説明
* @author 作成者名
* @date 作成日
*
* @details 詳細説明
* @note 補足説明とかメモ
*/

/**
* @file ModeGame.cpp
* @brief インゲームの管理、オブジェクトの管理やUIの表示、ステージの切り替え等している
* @author 井上和哉、石塚泉、酒井大彰
*
* @note 大半は井上が担当し、他二人に一部サポートしてもらいました
*/
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeGameClear.h"
#include <memory>
#include "../../../AppFrame/Easing.h"
#include "../../../AppFrame/Math.h"
#include"ObjectBase.h"
#include "ModePause.h"
#include "ApplicationGlobal.h"



// メニュー項目
class MenuItemViewCollision : public MenuItemBase {
public:
	MenuItemViewCollision(void* param, std::string text) : MenuItemBase(param, text) {}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		ModeGame *mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugViewColloion(!mdGame->GetDebugViewColloion());
		return 1;
	}
};

class MenuItemUseCollision : public MenuItemBase {
public:
	MenuItemUseCollision(void* param, std::string text) : MenuItemBase(param, text) {}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugUseColloion(!mdGame->GetDebugUseColloion());
		return 1;
	}
};

class MenuItemViewCameraInfo : public MenuItemBase {
public:
	MenuItemViewCameraInfo(void* param, std::string text) : MenuItemBase(param, text) {}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugViewCameraInfo(!mdGame->GetDebugViewCameraInfo());
		return 0;
	}
};

class MenuItemLaunchStageJump : public MenuItemBase {
public:
	MenuItemLaunchStageJump(void* param, std::string text) : MenuItemBase(param, text) {}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugStageJump(!mdGame->GetDebugStageJump());
		return 0;
	}
};

class MenuItemLaunchReStage : public MenuItemBase {
public:
	MenuItemLaunchReStage(void* param, std::string text) : MenuItemBase(param, text) {}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugReStage(!mdGame->GetDebugReStage());
		return 0;
	}
};

const ResourceServer::MV1ModelMap models{
  {"CollBoard", {"res/TT_COR.mv1"}},
  {"FallRock", {"res/Gimmick/rakuseki(texture,mv1)/rakuseki0221.mv1"}},
  {"ApproachingWall", {"res/Gimmick/ApproachingWall/Trap.mv1"}},
  {"MovingFloor", {"res/Gimmick/idouyuka(texture,mv1)/idouyuka0208_1.mv1"}},
  {"GravityFloor", {"res/Gimmick/juuryoku(tex,mv1)/juuryoku_yuka1.mv1"}},
  {"Switch", {"res/Gimmick/switch(tex,mv1)/switch_yuka_off1.mv1"}},
  {"SwitchOn", {"res/Gimmick/switch(tex,mv1)/switch_yuka_on1.mv1"}},
  {"Hammer", {"res/Gimmick/hammer_0315(tex,mv1)/hammer0315_j2.mv1"}},
  {"OutputDeviceStraight", {"res/OutputDevice/straight/straight.mv1"}},
  {"OutputDeviceCircle", {"res/OutputDevice/circle/beam_output_circle.mv1"}},

};

ModeGame::ModeGame(int stn,int conte)
	:_player(*this)
{
	_stn = stn;
	_conte = conte;
	_time = gGlobal._time;
	//jsonファイル読み込み
	LoadJsonfile();

	//モデルの非同期一括読み込み
	SetUseASyncLoadFlag(true);
	ResourceServer::LoadModels(models);
	SetUseASyncLoadFlag(false);
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	//UIクラス
	//HP
	auto i = ResourceServer::LoadGraph("res/title/4.png");
	_hp.push_back(i);
	i = ResourceServer::LoadGraph("res/title/3.png");
	_hp.push_back(i);
	i = ResourceServer::LoadGraph("res/title/2.png");
	_hp.push_back(i);
	i = ResourceServer::LoadGraph("res/title/1.png");
	_hp.push_back(i);
	//数字
	_displayTimes[0] = ResourceServer::LoadGraph("res/title/time/0.png");
	_displayTimes[1] = ResourceServer::LoadGraph("res/title/time/1.png");
	_displayTimes[2] = ResourceServer::LoadGraph("res/title/time/2.png");
	_displayTimes[3] = ResourceServer::LoadGraph("res/title/time/3.png");
	_displayTimes[4] = ResourceServer::LoadGraph("res/title/time/4.png");
	_displayTimes[5] = ResourceServer::LoadGraph("res/title/time/5.png");
	_displayTimes[6] = ResourceServer::LoadGraph("res/title/time/6.png");
	_displayTimes[7] = ResourceServer::LoadGraph("res/title/time/7.png");
	_displayTimes[8] = ResourceServer::LoadGraph("res/title/time/8.png");
	_displayTimes[9] = ResourceServer::LoadGraph("res/title/time/9.png");
	_displayTimes[10] = ResourceServer::LoadGraph("res/title/time/，，.png");
	_displayTimes[11] = ResourceServer::LoadGraph("res/title/time/，.png");
	_displayTimes[12] = ResourceServer::LoadGraph("res/title/time/frame.png");
	_displayTimes[13] = ResourceServer::LoadGraph("res/title/time/×.png");
	//残機数
	_remain[0] = ResourceServer::LoadGraph("res/title/remain/0.png");
	_remain[1] = ResourceServer::LoadGraph("res/title/remain/1.png");
	_remain[2] = ResourceServer::LoadGraph("res/title/remain/2.png");
	_remain[3] = ResourceServer::LoadGraph("res/title/remain/3.png");
	_remain[99] = ResourceServer::LoadGraph("res/title/remain/×.png");

	//BGMとSE
	PlaySoundMem(gGlobal._bgm["bgm001"], DX_PLAYTYPE_LOOP, true);
	PlaySoundMem(gGlobal._sv["sysvc_start"], DX_PLAYTYPE_BACK, true);
	PlaySoundMem(gGlobal._pv["start"], DX_PLAYTYPE_BACK, true);

	_goalModel = MV1LoadModel("res/Gimmick/goal/Warp_Gray/Warp_Gray.mv1");
	_goalEffect = LoadEffekseerEffect("res/Effect/PlayerEffect/teleport/teleport.efkefc", 50.0f);
	// シャドウマップの生成
	_handleShadowMap = MakeShadowMap(4096, 4096);
	_handleShadowMap_2 = MakeShadowMap(4096, 4096);

	//jsonの情報通りにレーザーを配置
	for (int i = 0; i < _laserData.size(); ++i) {

		//ステージ番号を見る
		if (_laserData[i]._stageNum == _stn) {
			//レーザーの形を見る
			switch (_laserData[i]._form) {
			case 0:
			{
				//直線
				auto laser = std::make_shared<LaserCollBase>();
				laser->SetstartPos(_laserData[i]._vPoses[0]);
				laser->SetendPos(_laserData[i]._vPoses[1]);
				laser->Setnum(i);
				laser->SetTrapNum(_laserData[i]._trapNums);
				laser->SetLaserForm(LaserCollBase::Form::STRAIGHT);
				laser->SetDelay(_laserData[i]._delay);
				laser->SetMove(_laserData[i]._move);
				laser->SetSpd(_laserData[i]._spd);
				if (_laserData[i]._move) {
					laser->SetMovedVPos(_laserData[i]._movedVPoses[0],
						                _laserData[i]._movedVPoses[1]);
				}
				if (_laserData[i]._switch) {
					laser->SetSwitchVPos(_laserData[i]._switchVPoses[0], 
					                     _laserData[i]._switchVPoses[1]);
				}
				if (_laserData[i]._move&& _laserData[i]._switch) {
					laser->SetSwitchMovedVPos(_laserData[i]._switchMovedVPoses[0],
						                      _laserData[i]._switchMovedVPoses[1]);
				}

				switch (_laserData[i]._type) {
					//レーザーの種類を見る
				case 0:
					//ダメージ
					//座標設定、番号設定、レーザーをvector配列にまとめる
					laser->SetColor(GetColor(255, 255, 0));
					laser->SetType(LaserCollBase::Type::DAMAGE);
					lasers.push_back(laser);
					break;

				case 1:
					//ゴール
					laser->SetColor(GetColor(0, 0, 255));
					laser->SetType(LaserCollBase::Type::CLEAR);
					lasers.push_back(laser);
					break;

				case 2:
					//トラップ
					laser->SetColor(GetColor(255, 0, 0));
					laser->SetType(LaserCollBase::Type::TRAP);
					lasers.push_back(laser);

					break;

				default:
					break;
				}
				break;
			}

			case 1:
			{
				//横に広がる円形
				auto laser = std::make_shared<CircleLaserHorizontal>();
				laser->SetLaserForm(LaserCollBase::Form::CIRCLEHORIZONTAL);
				laser->SetvPos(_laserData[i]._vPoses[0]);
				laser->Setnum(i);
				laser->SetTrapNum(_laserData[i]._trapNums);
				laser->SetDelay(_laserData[i]._delay);
				laser->SetSpd(_laserData[i]._spd);
				
				switch (_laserData[i]._type) {
					//レーザーの種類を見る
				case 0:
					//ダメージ
					//座標設定、番号設定、レーザーをvector配列にまとめる
					laser->SetColor(GetColor(255, 255, 0));
					laser->SetType(LaserCollBase::Type::DAMAGE);
					lasers.push_back(laser);
					break;

				case 1:
					//ゴール
					laser->SetColor(GetColor(0, 0, 255));
					laser->SetType(LaserCollBase::Type::CLEAR);
					lasers.push_back(laser);
					break;

				case 2:
					//トラップ
					laser->SetColor(GetColor(255, 0, 0));
					laser->SetType(LaserCollBase::Type::TRAP);
					lasers.push_back(laser);
					break;

				default:
					break;
				}
				break;
			}

			case 2:
			{
				//縦に広がる円形
				auto laser = std::make_shared<CircleLaserVertical>();
				laser->SetLaserForm(LaserCollBase::Form::CIRCLEVERTICAL);
				laser->SetvPos(_laserData[i]._vPoses[0]);
				laser->Setnum(i);
				laser->SetTrapNum(_laserData[i]._trapNums);
				laser->SetDelay(_laserData[i]._delay);
				laser->SetSpd(_laserData[i]._spd);

				switch (_laserData[i]._type) {
					//レーザーの種類を見る
				case 0:
					//ダメージ
					//座標設定、番号設定、レーザーをvector配列にまとめる
					laser->SetColor(GetColor(255, 255, 0));
					laser->SetType(LaserCollBase::Type::DAMAGE);
					lasers.push_back(laser);
					break;

				case 1:
					//ゴール
					laser->SetColor(GetColor(0, 0, 255));
					laser->SetType(LaserCollBase::Type::CLEAR);
					lasers.push_back(laser);
					break;

				case 2:
					//トラップ
					laser->SetColor(GetColor(255, 0, 0));
					laser->SetType(LaserCollBase::Type::TRAP);
					lasers.push_back(laser);
					break;

				default:
					break;
				}
				break;
			}

			default:
				break;
			}
		}
	}

	//jsonの情報通りにギミックを配置
	for (int i = 1; i < _trapData.size(); ++i) {

		//ステージ番号を見る
		if (_trapData[i]._stageNum == _stn) {
			//ギミックの種類を見る
			switch (_trapData[i]._type) {
			case 1:
			{
				//移動床
				auto movingFloor = std::make_shared<MovingFloor>(*this);
				movingFloor->SetNum(i);
				movingFloor->SetvPos(_trapData[i]._vPos);
				movingFloor->SetMovedVPos(_trapData[i]._movedVPos);
				_gimmicks.push_back(movingFloor);
				break;
			}
			case 2:
			{
				//落石
				auto fallrock = std::make_shared<FallRock>(*this);
				fallrock->SetNum(i);
				fallrock->SetvPos(_trapData[i]._vPos);
				_gimmicks.push_back(fallrock);
				break;
			}
			case 3:
			{
				//振り子ハンマー
				auto hammer = std::make_shared<Hammer>(*this);
				hammer->SetNum(i);
				hammer->SetvPos(_trapData[i]._vPos);
				_gimmicks.push_back(hammer);
				break;
			}
			case 4:
			{
				//スイッチ
				auto _switch = std::make_shared<Switch>(*this);
				_switch->SetNum(i);
				_switch->SetSwitchLaserNum(_trapData[i]._switchLaserNum);
				_switch->SetvPos(_trapData[i]._vPos);
				_gimmicks.push_back(_switch);
				break;
			}
			case 5:
			{
				//重力床
				auto gravityfloor = std::make_shared<GravityFloor>(*this);
				gravityfloor->SetNum(i);
				gravityfloor->SetvPos(_trapData[i]._vPos);
				_gimmicks.push_back(gravityfloor);
				break;
			}
			case 6:
			{
				//落とし穴
				auto pitfall = std::make_shared<Pitfall>(*this);
				pitfall->SetNum(i);
				pitfall->SetvPos(_trapData[i]._vPos);
				_gimmicks.push_back(pitfall);
				break;
			}
			case 7:
			{
				//迫る天井
				auto floor = std::make_shared<ApproachingFloor>(*this);
				floor->SetNum(i);
				floor->SetvPos(_trapData[i]._vPos);
				floor->SetSpd(_trapData[i]._spd);
				_gimmicks.push_back(floor);
				break;
			}
			case 8:
			{
				//迫る壁
				auto wall = std::make_shared<ApproachingWall>(*this);
				wall->SetNum(i);
				wall->SetvPos(_trapData[i]._vPos);
				wall->SetSpd(_trapData[i]._spd);
				_gimmicks.push_back(wall);
				break;
			}

			default:
				break;
			}
		}
	}

	//プレイヤーにjsonの情報を与える
	_player.SetStatus(_playerData);
#if 1
	_stageCollisionFloor = MV1LoadModel("res/TT_COR_0326.mv1");
	MV1SetPosition(_stageCollisionFloor, VGet(0, -30, 0));
	MV1SetScale(_stageCollisionFloor, VGet(1200, 2, 300));
	//右壁
	auto stageCollisionWallL = MV1DuplicateModel(_stageCollisionFloor);
	MV1SetPosition(stageCollisionWallL, VGet(600, 200, 4500));
	MV1SetScale(stageCollisionWallL, VGet(2000, 0, 1000));
	MV1SetRotationXYZ(stageCollisionWallL, VGet(0, 0, Math::ToRadians(90)));
	//左壁
	auto stageCollisionWallR = MV1DuplicateModel(_stageCollisionFloor);
	MV1SetPosition(stageCollisionWallR, VGet(-600, 200, 4500));
	MV1SetScale(stageCollisionWallR, MV1GetScale(stageCollisionWallL));
	MV1SetRotationXYZ(stageCollisionWallR, VGet(0, 0, Math::ToRadians(90)));
	//手前壁
	auto stageCollisionFront = MV1DuplicateModel(_stageCollisionFloor);
	MV1SetPosition(stageCollisionFront, VGet(0, 0, -250));
	MV1SetScale(stageCollisionFront, VGet(2000, 3, 150));
	MV1SetRotationXYZ(stageCollisionFront, VGet(Math::ToRadians(90), 0, Math::ToRadians(90)));
	//奥壁
	auto stageCollisionBack = MV1DuplicateModel(_stageCollisionFloor);
	MV1SetPosition(stageCollisionBack, VGet(0, 0, 9000));
	MV1SetScale(stageCollisionBack, MV1GetScale(stageCollisionFront));
	MV1SetRotationXYZ(stageCollisionBack, VGet(Math::ToRadians(90), 0, Math::ToRadians(90)));

	_stageWallCollisions.push_back(stageCollisionWallR);
	_stageWallCollisions.push_back(stageCollisionWallL);
	_stageWallCollisions.push_back(stageCollisionFront);
	_stageWallCollisions.push_back(stageCollisionBack);
	//デバッグ用
	if (_stn == -1) {
		//落石かっこかり
		auto fallrock = std::make_shared<FallRock>(*this);
		fallrock->SetvPos(VGet(-300, 500, 700));
		_gimmicks.push_back(fallrock);
		//迫る壁
		for (int i = 0; i < 1; ++i) {
			auto wall = std::make_shared<ApproachingWall>(*this);
			wall->SetvPos(VGet(-500, 100, 1800 + (i * 200)));
			_gimmicks.push_back(wall);
		}
		//迫る天井
		auto floor = std::make_shared<ApproachingFloor>(*this);
		floor->SetvPos(VGet(0, 400, 600));
		_gimmicks.push_back(floor);
		//落とし穴
		auto pitfall = std::make_shared<Pitfall>(*this);
		pitfall->SetvPos(VGet(500, 200, 0));
		_gimmicks.push_back(pitfall);
		//移動床
		auto movingfloor = std::make_shared<MovingFloor>(*this);
		movingfloor->SetvPos(VGet(400, 200, 0));
		movingfloor->SetMovedVPos(VGet(400, 200, 2000));
		_gimmicks.push_back(movingfloor);
		//重力床
		auto gravityfloor = std::make_shared<GravityFloor>(*this);
		gravityfloor->SetvPos(VGet(0, 200, 800));
		_gimmicks.push_back(gravityfloor);
		//スイッチ
		auto _switch = std::make_shared<Switch>(*this);
		std::vector<int> nums;
		nums.push_back(6);
		_switch->SetSwitchLaserNum(nums);
		_switch->SetvPos(VGet(0, 200, 1400));
		_gimmicks.push_back(_switch);
		//振り子ハンマー
		auto hammer = std::make_shared<Hammer>(*this);
		hammer->SetvPos(VGet(0, 900, 3000));
		_gimmicks.push_back(hammer);
	}

	// ステージ
	_handleMap = MV1LoadModel("res/stage/stagecube_0315(tex,mv1)/Stagecube1_0315.mv1");
	MV1SetRotationXYZ(_handleMap, VGet(0, Math::ToRadians(90), 0));
	MV1SetPosition(_handleMap, VGet(0, 0, 0));

	MV1SetMeshBackCulling(_handleMap,0,  true);
	
	//光源
	_light = CreateDirLightHandle(VGet(-1, 1, -1));
#else
	// フィールド
	_handleMap = MV1LoadModel("res/Ground/Ground.mv1");
	_frameMapCollision = MV1SearchFrame(_handleMap, "ground_navmesh");
#endif
	MV1SetupCollInfo(_stageCollisionFloor, _frameMapCollision, 16, 16, 16);
	// コリジョンのフレームを描画しない設定
	MV1SetFrameVisible(_handleMap, _frameMapCollision, FALSE);

	_player.SetvPos(VGet(0,100,0));
#if 1
	_cam._vPos = VGet(175.f, 150.f, -270.f);
	_cam._vTarget = VGet(20, 160, 0);

	_cam._clipNear = 2.f;
	_cam._clipFar = 10000.f;
	_camChenge = false;
#else

#endif
	// その他初期化
	_bViewCollision = false;
	_bUseCollision = TRUE;
	_bViewCameraInfo = false;

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	DeleteLightHandle(_light);
	StopSoundMem(gGlobal._bgm["bgm001"]);
	for (auto e : lasers) {
		e->StopEffect();
	}
	_player.StopEffect();
	return true;
}



bool ModeGame::Process() {
	base::Process();		
	
	if (_stageJump) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(++_stn, _conte), 1, "game");
		
		return false;
	}

	if (_reStage) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(_stn, _conte), 1, "game");
		
		return false;
	}

	VECTOR oldplayervpos = _player.GetvPos();

	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	int rel = ApplicationMain::GetInstance()->GetRel();

	//ゴールに当たったか
	if (HitCheck_Capsule_Capsule(_player._senterpos, _player._capsulepos_end,
		_player.Getrad(), _gspos, _gepos, _gr)) {

		int clearserand = GetRand(1);
		if (_stn == _stageMax) {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeGameClear(), 1, "gameclear");
		}
		else {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeGame(++_stn, _conte), 1, "gameover");
			PlaySoundMem(gGlobal._sv["stageclear"], DX_PLAYTYPE_BACK, true);
			if (clearserand == 0) {
				PlaySoundMem(gGlobal._pv["stageclear1"], DX_PLAYTYPE_BACK, true);
			}
			if (clearserand == 1) {
				PlaySoundMem(gGlobal._pv["stageclear2"], DX_PLAYTYPE_BACK, true);
			}
		}

		StopSoundMem(gGlobal._bgm["bgm001"]);
	}

	//ゴール地点にエフェクトを出す
	_playingGoalEffect = PlayEffekseer3DEffect(_goalEffect);
	SetPosPlayingEffekseer3DEffect(_playingGoalEffect, _gepos.x, _gepos.y, _gepos.z);

	++_time;

	// 処理前のステータスを保存しておく
	// アナログスティック対応
	DINPUT_JOYSTATE di;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &di);
	float lx, ly, rx, ry;	// 左右アナログスティックの座標
	float analogMin = 0.3f;	// アナログ閾値
	// Logicoolパッドの場合
	lx = (float)di.X / 1000.f; ly = (float)di.Y / 1000.f;
	rx = (float)di.Rx / 1000.f; ry = (float)di.Ry / 1000.f;
	
	//カメラの動き
	float sx = _cam._vPos.x -_cam._vTarget.x;
	float sz = _cam._vPos.z -_cam._vTarget.z;
	float rad = atan2(sz, sx);
	float length = sqrt(sz * sz + sx * sx);
	
	_cam._vPos.x = _cam._vTarget.x + cos(rad) * length;
	_cam._vPos.z = _cam._vTarget.z + sin(rad) * length;

	//石塚、カメラの切り替え
	float Rmax = 359.f;
	if (key & PAD_INPUT_5)
	{
		_cam._vPos.z = _player.GetvPos().z + 30.f;
		_cam._vPos.y = 170.f;
		_cam._vTarget.x = Rmax + 40.f;
		_cam._vTarget.y = 180;
		_cam._vTarget.z = _player.GetvPos().z + 30.f;
		_camChenge = true;
		for (auto e : lasers) {
			e->SetDelay(1.0f);
		}
	}
	else
	{
		_cam._vPos.z = _player.GetvPos().z - 270.f;
		_cam._vPos.y = 130.f;
		_cam._vTarget.x = _player.GetvPos().x + 40.f;
		_cam._vTarget.y = 140;
		_cam._vTarget.z = _player.GetvPos().z;
		_camChenge = false;
	}
{
		// カメラの向いている角度を取得
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float camrad = atan2(sz, sx);
		
		//レーザーとギミックのprocessを呼ぶ
		for (auto l : lasers) {
			l->Process();
		}
		for (auto e : _gimmicks) {
			e->Process();
		}

		auto oldppos = _player.GetvPos();
		if (!_camChenge) {
		_player.Process();

		}

		if (trg & PAD_INPUT_3) {//Ⅽキーでしゃがむプレイヤーに合わせてカメラを少し下げる
			_cam._vPos.y -= 5.0f;
			_cam._vTarget.y -= 5.0f;
		}
		if (rel & PAD_INPUT_3) {
			_cam._vPos.y += 5.0f;
			_cam._vTarget.y += 5.0f;
		}
		//プレイヤーが動いた分だけ動かす
		//石塚、カメラのXY追従
		if ((key & PAD_INPUT_5) == 0)
		{
			_cam._vPos.y = _player.GetvPos().y + 130.f;
			_cam._vTarget.y = _player.GetvPos().y + 140.f;
		}
		auto d = VAdd(_cam._vPos, VSub(_player.GetvPos(), oldppos));
		_cam._vPos.z = d.z;
		if (_player.GetvPos().x < Rmax)
		{ 
			_cam._vPos.x = d.x;
		}

		d = VAdd(_cam._vTarget, VSub(_player.GetvPos(), oldppos));
		if (_player.GetvPos().x <= Rmax)
		{
			_cam._vPos.x = d.x + 59.f;
		}
		_cam._vTarget.x = d.x;
		_cam._vTarget.z = d.z;

		if (trg & PAD_INPUT_8 || trg & PAD_INPUT_12) {
			// ESCキーでポーズ画面を開く
			ModePause* modePause = new ModePause(this);
			ModeServer::GetInstance()->Add(modePause, 99, "pause");
			PlaySoundMem(gGlobal._se["Pause"], DX_PLAYTYPE_BACK, true);
		}

		// デバッグ機能
		if (_bViewCollision) {
			MV1SetFrameVisible(_handleMap, _frameMapCollision, TRUE);
		}
		else {
			MV1SetFrameVisible(_handleMap, _frameMapCollision, FALSE);
		}
	}

	//チートが有効か無効か
	if (_bUseCollision && _player.Getnohittime() == 0) {

		//レーザーの削除リスト、レーザーの番号で管理
		std::list<int> _del;

		//直線レーザーとの当たり判定
		for (auto e : lasers) {
			if (HitCheck_Capsule_Capsule(_player._senterpos, _player._capsulepos_end,
				_player.Getrad(), e->GetstartPos(), e->GetendPos(), e->Getrad()) == true &&
				_player.Getnohittime() == 0) {

				switch (e->GetType())
				{
				case LaserCollBase::Type::DAMAGE:
				{
					//プレイヤーの被ダメ処理
					_player.Damage(e->GetKnockBackTime(), e->GetDamage());
				}
				break;
				
				case LaserCollBase::Type::TRAP:
				{
					int num = e->GetTrapNums().front();
					int endnum = e->GetTrapNums().back();
					for (auto ee : _gimmicks) {
						if (ee->GetNum() == num && num <= endnum) {
							ee->SetActivate(true);
							num++;
						}
					}
					_del.push_back(e->GetNum());
					PlaySoundMem(gGlobal._se["Alert"], DX_PLAYTYPE_BACK, true);
				}
					break;

				case LaserCollBase::Type::CLEAR:

					_player.SetDashSpd(_player.GetDashSpd() + 2);
					break;

				default:
					break;
				}
			}
		}

		//削除リストにあるレーザーを削除
		for (int i = 0; i < lasers.size() - 1; ++i) {
			for (auto d : _del) {
				if (lasers[i]->GetNum() == d) {
					lasers.erase(lasers.begin() + i);
				}
			}
		}

		//円形レーザーとの当たり判定
		CheckHitRoundCircleHorizontal();
		CheckHitRoundCircleVertical();
	}

	gGlobal._time = _time;
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
	return true;
}

bool ModeGame::CheckHitRoundCircleHorizontal() {

	//座標のx,z(円)とy(高さ)を別々に判定する
	// 2つの円の中心点の距離を求める
	// ピタゴラスの定理（三平方の定理）で求めることができる
	VECTOR v = _player.GetvPos();
	int r = _player.Getrad();
	int hieght = _player.Getheight();

	for (auto e : lasers) {
		if (e->GetLaserForm() == LaserCollBase::Form::CIRCLEHORIZONTAL) {
			int w, h, le;
			w = v.x - e->GetvPos().x;
			h = v.z - e->GetvPos().z;
			le = (int)sqrt((float)(w * w + h * h));

			if (le <= r + e->GetHitRad()) {  //ダメージ円の中か

				if (v.y + hieght < e->GetvPos().y) {  //高さの判定、頭がレーザーより下か
					return false;
				}
				if (v.y > e->GetvPos().y + e->GetCircleHeight()) {  //高さの判定、足元がレーザーより上か
					return	false;
				}
				if (le + r <= e->GetNoHitRad()) {  //回避円の中に全身入っていれば回避
					return false;
				}
				//プレイヤーの被ダメ処理
				_player.Damage(e->GetKnockBackTime(), e->GetDamage());
				return true;
			}
		}
	}

	return false;
}

bool ModeGame::CheckHitRoundCircleVertical() {

	//座標のx,y(円)とz(幅)を別々に判定する
	VECTOR v = _player.GetvPos();
	int r = _player.Getrad();
	int hieght = _player.Getheight();

	for (auto e : lasers) {
		if (e->GetLaserForm() == LaserCollBase::Form::CIRCLEVERTICAL) {
			int w, h, le;
			w = v.x - e->GetvPos().x;
			h = v.y - e->GetvPos().y;
			le = (int)sqrt((float)(w * w + h * h));

			if (le <= r + e->GetHitRad()) {  //xy軸平面の円の判定、プレイヤーの当たり判定円がダメージ円の中か

				if (v.z + r < e->GetvPos().z) {  //幅の判定、つま先がレーザーより後ろか
					return false;
				}
				if (v.z - r > e->GetvPos().z + e->GetCircleHeight()) {  //幅の判定、かかとがレーザーより前か
					return	false;
				}
				if (le + hieght / 2 <= e->GetNoHitRad()) {  //xy軸平面の円の判定、回避円の中に全身入っていれば回避
					return false;
				}
				//プレイヤーの被ダメ処理
				_player.Damage(e->GetKnockBackTime(), e->GetDamage());
				return true;
			}
		}
	}

	return false;
}

bool ModeGame::Render() {

	base::Render();

	auto color = GetColor(rand() % 255, rand() % 255, rand() % 255);
	//ゴール
	if (_bViewCollision) {
	DrawCapsule3D(_gspos, _gepos, _gr, 16, color, color, FALSE);
	}
	MV1SetPosition(_goalModel, _gepos);
	MV1DrawModel(_goalModel);
	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// ライト設定
	SetUseLighting(true);
#if 1	// 平行ライト
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(VGet(-1, -1, 0));
#endif
#if 0	// ポイントライト
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_vPos,VGet(0,50.f,0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	// カメラ設定更新
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

	//石塚、影
	// シャドウマップが想定するライトの方向もセット
	SetShadowMapLightDirection(_handleShadowMap, VGet(-1, -0.1f, 0));
	SetShadowMapLightDirection(_handleShadowMap_2, VGet(0, -1, 0));
	// シャドウマップに描画する範囲を設定
	SetShadowMapDrawArea(_handleShadowMap, VGet(-800.f, _player.GetvPos().y - 200.f, _player.GetvPos().z - 40.f),
		VGet(_player.GetvPos().x + 200.f, _player.GetvPos().y + 200.f, _player.GetvPos().z + 40.0f));
	SetShadowMapDrawArea(_handleShadowMap_2, VGet(-800.f, _player.GetvPos().y - 200.f, _player.GetvPos().z - 40.f),
		VGet(_player.GetvPos().x + 200.f, _player.GetvPos().y + 200.f, _player.GetvPos().z + 40.0f));
	// 2回まわして、path=0:シャドウマップへの描画, path=1:モデルの描画
	for (int path = 0; path < 4; path++) {
		if (path == 0) {
			// シャドウマップへの描画の準備
			ShadowMap_DrawSetup(_handleShadowMap);

		}
		else if (path == 1) {
			// シャドウマップへの描画を終了
			ShadowMap_DrawEnd();
			// 描画に使用するシャドウマップを設定
			SetUseShadowMap(0, _handleShadowMap);
		}
		if (path == 2) {
			ShadowMap_DrawSetup(_handleShadowMap_2);
		}

		else if (path == 3) {
			// シャドウマップへの描画を終了
			ShadowMap_DrawEnd();
			// 描画に使用するシャドウマップを設定
			SetUseShadowMap(1, _handleShadowMap_2);
		}
		// プレイヤー描画
		
		if (path == 1 || path == 3) {
			SetUseShadowMap(0, -1);
			SetUseShadowMap(1, -1);
			_player.Render();
			SetUseShadowMap(0, _handleShadowMap);
			SetUseShadowMap(1, _handleShadowMap_2);
		}
		else {
		_player.Render();
		}
		
		if (path == 1 || path == 3) {
			// マップモデルを描画する
			MV1DrawModel(_handleMap);
			if (_bViewCollision) {
				for (auto e : _stageWallCollisions) {
					MV1DrawModel(e);
				}
				MV1DrawModel(_stageCollisionFloor);
			}
		}

		// モデルを描画する
		if (path == 1 || path == 3) {
			VECTOR vRot = { 0,0,0 };
			// レーザーの描画
			for (auto l : lasers) {
				l->Render();
				if (_bViewCollision) {
					l->CollisionRender();
				}
			}
			//ギミックの描画
			for (auto e : _gimmicks) {
				e->Render();
			}
		}
	}
	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);
	SetUseShadowMap(1, -1);


	// カメラ情報表示
	if (_bViewCameraInfo) {
		int x = 0, y = 0, size = 16;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam._vTarget.x, _cam._vTarget.y, _cam._vTarget.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _cam._vPos.x, _cam._vPos.y, _cam._vPos.z); y += size;
		DrawFormatString(x, y + 150, GetColor(255, 0, 0), "SCORE = TIME = %d", _time);
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float length = sqrt(sz * sz + sx * sx);
		float rad = atan2(sz, sx);
		float deg = RAD2DEG(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += size;

		DrawFormatString(0, 250, GetColor(255, 0, 0), "STICK = %d", (int)_player.GetStick());
		DrawFormatString(0, 400, GetColor(255, 0, 0), "dasdspd = %f", _player.GetDashSpd());
		DrawFormatString(0, 350, GetColor(255, 0, 0), "レーザーコリジョン = %d", (int)_bUseCollision);

	}
	
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();

	//UI
	//ｈｐ
	DrawGraph(0, 0, _hp[_player.Getlife()], true);
	

	//タイマー
	//タイマー表示の枠
	DrawRotaGraph(300, 300, 1.0, 0, _displayTimes[12], true, false);
	int dis = 40;//数字表記の間隔
	int nx = 450;//数字表記する座標の右端
	int time = _time;
	
	//フレームでカウントしている_timeをタイマーの形に分ける
	int f, s, m;
	m = time / 3600;
	time %= 3600;
	s = time / 60;
	time %= 60;
	f = time % 60;
	f = f / 3 * 5;
	int cnts[] = { f, s, m };

	//今扱ってる時間（フレーム、秒、分）の1，2桁目の数字
	int digit1, digit2;
	digit1 = f % 10;
	digit2 = f / 10;
	int num = digit1;

	//右から一桁ずつ表示する
	for (int i = 1; i < 9; ++i) {
		//座標
		int x = nx - dis * i;
		if (i % 3 == 0) {
			//二桁表示したら扱う時間を繰り上げる
			time = cnts[i / 3];
			digit1 = time % 10;
			digit2 = time / 10;
			num = digit1;
			//クオーテーションの表示
			DrawRotaGraph(x - (dis / 4), 260, 0.17, 0, _displayTimes[9 + i / 3 ], true, false);
		}				
		else {			
			DrawRotaGraph(x, 280, 0.17, 0, _displayTimes[num], true, false);
			num = digit2;
		}
	}

	//残機数表示
	DrawRotaGraph(490, 90, 0.2, 0, _remain[99], true, false);
	DrawRotaGraph(548, 90, 0.2, 0, _remain[_conte], true, false);
	
	//死んだときの暗転処理
	if (_player.Getlife() <= 0) {
		if (_screenBright == 0) {
			--_conte;
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _screenBright);
		DrawBox(0, 0, 1920, 1080,
			GetColor(0, 0, 0), true);
		_screenBright += 4;
	}
	
	if (_screenBright > 256) {
		DrawGraph(400, 510, _hp[3], true);
		DrawGraph(900, 440, _displayTimes[13] , true);
		DrawGraph(1200, 440, _displayTimes[_conte], true);
	}

	if (_screenBright > 300) {
		if (_conte > 0) {
			_reStage = true;
		}
		else {
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "gameover");
			gGlobal._time = 0;
		}
	}

	return true;
}

//json
#include <stdio.h>
#include <stdlib.h>
#include "CFile/CFile.h"
#include "CFile/utf8sjis.h"
#include "CFile/picojson.h"

void ModeGame::LoadJsonfile()
{

	//レーザーの情報読み込む
	CFile f("Laser.json");
	if (!f.data()) { printf("read error."); return; }

	// data -> string
	std::string s = (char*)f.data();

	// json
	picojson::value json;
	picojson::parse(json, s);
	picojson::object jsRoot = json.get<picojson::object>();

	// データの確認-----------------------------------------------------------

	picojson::array sheet = jsRoot["Laser2"].get<picojson::array>();

	for (int i = 0; i < sheet.size(); ++i) {

		VECTOR startVPos = VGet(0, 0, 0);
		VECTOR endVPos = VGet(0, 0, 0);
		int type = 0;
		std::vector<int> trapNums;
		int form = 0;
		int stage = 0;
		bool move = false;
		VECTOR movedStartVPos = VGet(0, 0, 0);
		VECTOR movedEndVPos   = VGet(0, 0, 0);
		std::vector<VECTOR> movedVPoses;
		bool _switch = false;
		VECTOR switchStartVPos = VGet(0, 0, 0);
		VECTOR switchEndVPos   = VGet(0, 0, 0);
		std::vector<VECTOR> switchVPoses;
		VECTOR switchMovedStartVPos = VGet(0, 0, 0);
		VECTOR switchMovedEndVPos   = VGet(0, 0, 0);			
		std::vector<VECTOR> switchMovedVPoses;

		float delay = 0;
		float spd = 0;

		picojson::object x = sheet[i].get<picojson::object>();

		startVPos.x = (int)x["startpos_x"].get<double>();
		startVPos.y = (int)x["startpos_y"].get<double>();
		startVPos.z = (int)x["startpos_z"].get<double>();
		endVPos.x = (int)x["endpos_x"].get<double>();
		endVPos.y = (int)x["endpos_y"].get<double>();
		endVPos.z = (int)x["endpos_z"].get<double>();

		std::vector<VECTOR> vPoses;
		vPoses.push_back(startVPos);
		vPoses.push_back(endVPos);

		type = (int)x["type"].get<double>();
		int first = (int)x["trapnum"].get<double>();
		int last = (int)x["trapnum_last"].get<double>();
		trapNums.push_back(first);
		for (int i = ++first; i <= last; ++i) {
			trapNums.push_back(i);
		}
		form = (int)x["form"].get<double>();
		delay = (float)x["delay"].get<double>();
		spd = (float)x["spd"].get<double>();
		stage = (int)x["stage"].get<double>();
		move = x["move"].get<bool>();
		if (move) {
			movedStartVPos.x = (int)x["startpos_x_moved"].get<double>();
			movedStartVPos.y = (int)x["startpos_y_moved"].get<double>();
			movedStartVPos.z = (int)x["startpos_z_moved"].get<double>();
			movedEndVPos.x = (int)x["endpos_x_moved"].get<double>();
			movedEndVPos.y = (int)x["endpos_y_moved"].get<double>();
			movedEndVPos.z = (int)x["endpos_z_moved"].get<double>();
			movedVPoses.push_back(movedStartVPos);
			movedVPoses.push_back(movedEndVPos);
		};
		_switch = x["switch"].get<bool>();
		if (_switch) {
			switchStartVPos.x = (int)x["startpos_x_switch"].get<double>();
			switchStartVPos.y = (int)x["startpos_y_switch"].get<double>();
			switchStartVPos.z = (int)x["startpos_z_switch"].get<double>();
			switchEndVPos.x = (int)x["endpos_x_switch"].get<double>();
			switchEndVPos.y = (int)x["endpos_y_switch"].get<double>();
			switchEndVPos.z = (int)x["endpos_z_switch"].get<double>();
			switchVPoses.push_back(switchStartVPos);
			switchVPoses.push_back(switchEndVPos);

			switchMovedStartVPos.x = (int)x["startpos_x_moved_switch"].get<double>();
			switchMovedStartVPos.y = (int)x["startpos_y_moved_switch"].get<double>();
			switchMovedStartVPos.z = (int)x["startpos_z_moved_switch"].get<double>();
			switchMovedEndVPos.x = (int)x["endpos_x_moved_switch"].get<double>();
			switchMovedEndVPos.y = (int)x["endpos_y_moved_switch"].get<double>();
			switchMovedEndVPos.z = (int)x["endpos_z_moved_switch"].get<double>();
			switchMovedVPoses.push_back(switchStartVPos);
			switchMovedVPoses.push_back(switchEndVPos);
		}

		LaserData laserdata{ vPoses,type,trapNums,
			form,stage,move,movedVPoses,_switch
			,switchVPoses ,switchMovedVPoses,delay,spd };

		_laserData.push_back(laserdata);
		_stageMax = stage;
	}
	

	//トラップ情報の読み込み
	CFile trap("trap.json");
	if (!trap.data()) { printf("read error."); return; }

	 s = (char*)trap.data();

	// json
	picojson::value trapjson;
	picojson::parse(trapjson, s);
	jsRoot = trapjson.get<picojson::object>();

	sheet = jsRoot["Trap"].get<picojson::array>();
	for (int i = 0; i < sheet.size(); ++i) {

		VECTOR vPos = VGet(0, 0, 0);
		int type = 0;
		int stage = 0;
		VECTOR movedVPos = VGet(0, 0, 0);
		int switchRangeFirst;
		int switchRangeLast;
		std::vector<int> switchLaserNum;
		int spd;

		//レーザーの当たり判定（カプセル）の場所を読み込む
		picojson::object t = sheet[i].get<picojson::object>();
		vPos.x = (int)t["pos_x"].get<double>();
		vPos.y = (int)t["pos_y"].get<double>();
		vPos.z = (int)t["pos_z"].get<double>();

		//レーザーの種類と、トラップの番号を読み込む
		type = (int)t["type"].get<double>();
		stage = (int)t["stage"].get<double>();

		movedVPos.x = (int)t["movedpos_x"].get<double>();
		movedVPos.y = (int)t["movedpos_y"].get<double>();
		movedVPos.z = (int)t["movedpos_z"].get<double>();

		switchRangeFirst = (int)t["range_first"].get<double>();
		switchRangeLast = (int)t["range_last"].get<double>();
		switchLaserNum.push_back(switchRangeFirst);
		for (int i = ++switchRangeFirst; i <= switchRangeLast; ++i) {
			switchLaserNum.push_back(i);
		}
		spd = (int)t["spd"].get<double>();

		TrapData trapdata{ vPos,type ,stage,movedVPos,
			switchLaserNum,spd };
		_trapData.push_back(trapdata);
	}
	

	//プレイヤー情報の読み込み
	CFile player("Player.json");
	if (!player.data()) { printf("read error."); return; }

	s = (char*)player.data();

	// json
	picojson::value playerjson;
	picojson::parse(playerjson, s);
	jsRoot = playerjson.get<picojson::object>();

	sheet = jsRoot["Player"].get<picojson::array>();

		int jumpHeight;
		int airJumpHeight;
		float walkSpd;
		float dashSpd;
		float maxDashSpd;
		float _accelerateTime;
		float squatSpd;
		float dashTimeToSlidhing;

		picojson::object p = sheet[0].get<picojson::object>();
		jumpHeight      = (int)p["jumpHeight"].get<double>();
		airJumpHeight   = (int)p["airJumpHeight"].get<double>();
		walkSpd       = (float)p["walkSpd"].get<double>();
		dashSpd       = (float)p["dashSpd"].get<double>();
		maxDashSpd       = (float)p["maxDashSpd"].get<double>();
		_accelerateTime = (float)p["accelerateTime"].get<double>();
		squatSpd      = (float)p["squatSpd"].get<double>();
		dashTimeToSlidhing = (float)p["dashTimeToSlidhing"].get<double>();

		Player::PlayerData Playerdata{ jumpHeight,airJumpHeight 
			,walkSpd,dashSpd,maxDashSpd,_accelerateTime,
			squatSpd,dashTimeToSlidhing };

		_playerData = Playerdata;

}
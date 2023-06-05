#pragma once
#include "appframe.h"
#include <string>
#include "ModeMenu.h"
#include <memory>
#include "../../../AppFrame/Vector3D.h"
#include"ObjectBase.h"
#include"Player.h"
#include "LaserCollisionBase.h"
#include <vector> 
#include "Gimmick.h"
#include <unordered_map>


/**
* @file ModeGame.h
* @author 井上和哉
*/

// 計算用マクロ
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

// カメラ
class Camera {
public:
	VECTOR	_vPos;					// 位置
	VECTOR	_vTarget;				// 距離
	float	_clipNear, _clipFar;	// クリップ
};
// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	ModeGame(int stn,int conte);
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	bool GetDebugViewColloion() { return _bViewCollision; }
	void SetDebugViewColloion(bool b) { _bViewCollision = b; }
	bool GetDebugUseColloion() { return _bUseCollision; }
	void SetDebugUseColloion(bool b) { _bUseCollision = b; }
	bool GetDebugViewCameraInfo() { return _bViewCameraInfo; }
	void SetDebugViewCameraInfo(bool b) { _bViewCameraInfo = b; }
	bool GetDebugStageJump() { return _stageJump; }
	void SetDebugStageJump(bool b) { _stageJump = b; }
	bool GetCamChenge() { return _camChenge; }

	bool GetDebugReStage() { return _reStage; }
	void SetDebugReStage(bool b) { _reStage = b; }

	int GetTime() { return _time; }
	bool GetDebugCup() { return _bViewCollision; }

	int GetStageFloorCollision() { return _stageCollisionFloor; };
	std::vector<int> GetStageWallCollision() { return _stageWallCollisions; }//デバッグ
	std::vector<std::shared_ptr<GimmickBase>> GetGimmickCollision() { return _gimmicks; };

	Player _player;
	
	//レーザーの情報
	struct LaserData {
		std::vector<VECTOR> _vPoses;  //レーザーの始まりと終わりの座標
		int _type;  //レーザーの種類
		std::vector<int> _trapNums; //起動させるトラップの番号
		int _form;
		int _stageNum;
		bool _move;//動くか
		std::vector<VECTOR> _movedVPoses;
		bool _switch;//スイッチするか
		std::vector<VECTOR> _switchVPoses;
		std::vector<VECTOR> _switchMovedVPoses;
		//円形用
		float _delay;//ステージスタートから起動するまでの時間
		float _spd;//拡大の速さ

	};
	std::vector<LaserData> _laserData;
	std::vector<std::shared_ptr<LaserCollBase>> lasers;//全レーザーの配列

	//トラップの情報
	struct TrapData {
		VECTOR _vPos;
		int _type;
		int _stageNum;
		VECTOR _movedVPos;
		std::vector<int> _switchLaserNum;
		int _spd;
	};
	std::vector<TrapData> _trapData;
	std::vector<std::shared_ptr<GimmickBase>> _gimmicks;//全ギミックの配列

	//プレイヤーの情報
	Player::PlayerData _playerData;

protected:

	// カメラ
	Camera	_cam;

	// 3Dモデル描画用
	int _handle;

	int _time;
	//円形のレーザーと当たり判定
	bool CheckHitRoundCircleHorizontal();
	bool CheckHitRoundCircleVertical();

	//json読み込み
	//jsonファイルを読み込んで配列に情報をまとめる
	void LoadJsonfile(); 

	// デバッグ用
	bool _bViewCollision;
	bool _bUseCollision;
	bool _bViewCameraInfo;
	bool _stageJump;
	bool _reStage;

	// マップ用
	int _handleMap;
	int _handleSkySphere;
	int _frameMapCollision;

	//ステージの当たり判定
	std::vector<int> _stageWallCollisions;
	int _stageCollisionFloor;

	//ゴール用
	VECTOR _gspos = VGet(0, 300, 8000);
	VECTOR _gepos = VGet(0, 0, 8000);
	float _gr = 64;
	int _stn = 1;//ステージナンバー
	int _stageMax;
	int _goalModel;
	int _goalEffect;
	int _playingGoalEffect;

	//光源
	int _light;
	// シャドウマップ用
	int _handleShadowMap;
	int _handleShadowMap_2;

	//UIクラス
	std::vector<int> _hp;
	std::unordered_map<int, int> _displayTimes;
	std::unordered_map<int, int> _remain;

	int _screenBright = 0;//画面の明るさ

	int _conte;//コンティニュー回数
	bool _camChenge;//カメラの切り替えがされているか

}; 



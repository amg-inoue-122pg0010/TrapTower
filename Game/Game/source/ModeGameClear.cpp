#include "ModeGameClear.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "ApplicationGlobal.h"
#include "ModeStageSelect.h"

/**
* @file ModeGameClear.cpp
* @brief クリア画面の表示
* @author 井上和哉、石塚泉
*/

ModeGameClear::ModeGameClear(){

	_cgBack= ResourceServer::LoadGraph("res/GameClear/GameClear_rough01.png");
	_backAnimeMax = 64;
	_cgGameClear.resize(_backAnimeMax);
	ResourceServer::LoadDivGraph("res/gameover/gameover.png", _backAnimeMax, 8, 8, 1920, 1080, _cgGameClear.data());
	_cgMenu = ResourceServer::LoadGraph("res/GameOver/senntakusi.png");
	_animeMax = 5;
	_cgCursor = ResourceServer::LoadGraph("res/title/yajirusi.png");
	_menuNum = 1;
	PlaySoundMem(gGlobal._bgm["clear"], DX_PLAYTYPE_BACK, true);
	PlaySoundMem(gGlobal._sv["gameclear"], DX_PLAYTYPE_BACK, true);
	PlaySoundMem(gGlobal._pv["gameclear"], DX_PLAYTYPE_BACK, true);

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
}

bool ModeGameClear::Process(){
	int trg = ApplicationMain::GetInstance()->GetTrg();

	_animeCnt++;
	if (_sel == true) {

		//項目を選ぶ
		if (trg & PAD_INPUT_UP) {
			_menuNum--; _animeCnt = 0;
			PlaySoundMem(gGlobal._se["Select"], DX_PLAYTYPE_BACK, true);
		}
		if (trg & PAD_INPUT_DOWN) {
			_menuNum++; _animeCnt = 0;
			PlaySoundMem(gGlobal._se["Select"], DX_PLAYTYPE_BACK, true);
		}
		_menuNum = Math::Clamp(_menuNum, 1, 3);

		//決定
		if (trg & PAD_INPUT_2) {
			gGlobal._time = 0;
			PlaySoundMem(gGlobal._se["Dicision"], DX_PLAYTYPE_BACK, true);
			StopSoundMem(gGlobal._bgm["clear"]);
			switch (_menuNum) {
			case 1:
				ModeServer::GetInstance()->Del(this);
				ModeServer::GetInstance()->Add(new ModeGame(1, 3), 1, "game");
				PlaySoundMem(gGlobal._pv["retry"], DX_PLAYTYPE_BACK, true);
				break;
			case 2:
				//ステージセレクトモード
				ModeServer::GetInstance()->Del(this);
				ModeServer::GetInstance()->Add(new ModeStageSelect(), 1, "stageselect");

				break;
			case 3:
				ModeServer::GetInstance()->Del(this);
				ModeServer::GetInstance()->Add(new ModeTitle(), 1, "game");
				break;
			default:
				break;
			}
		}
		if (_animeCnt >= _animeMax * 3) {
			_animeCnt--;
		}
	}

	if (trg & PAD_INPUT_2) {
		_sel = !_sel;
	}
	return true;
}

bool ModeGameClear::Render(){
		DrawGraph(700, 0, _cgBack, false);

		//タイマー
		//タイマー表示の枠
		int dis = 80;//数字表記の間隔
		int nx = 750;//数字表記する座標の右端
		int time = gGlobal._time;

		//フレームでカウントしている_timeを60刻みの時間に分ける
		int f, s, m;
		m = time / 3600;
		time %= 3600;
		s = time / 60;
		time %= 60;
		f = time;
		int cnts[] = { f, s, m };

		//今扱ってる時間（フレーム、秒、分）の1，2桁目の数字
		int digit1, digit2;
		digit1 = time % 10;
		digit2 = time / 10 % 6;
		int num = digit1;

		//右から一桁ずつ表示する
		for (int i = 1; i < 9; ++i) {
			int x = nx - dis * i;
			if (i % 3 == 0) {
				//二桁表示したら扱う時間を繰り上げる
				time = cnts[i / 3];
				digit1 = time % 10;
				digit2 = time / 10 % 6;
				num = digit1;
				//クオーテーションの表示
				DrawRotaGraph(x - (dis / 4), 260, 0.4, 0, _displayTimes[9 + i / 3], true, false);
			}
			else {
				DrawRotaGraph(x, 280, 0.4, 0, _displayTimes[num], true, false);
				num = digit2;
			}
		}

		if (_sel == true) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _screenBright);
			DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
			_screenBright += 4;
		}if (_screenBright > 300) {
			_animeNum = (_animeCnt / 3) % _animeMax;
			if (_animeCnt / 16 % 2 == 0) {
				DrawRotaGraph(580, 500 + (_menuNum * 100), 0.7, 0, _cgCursor, true, false);
			}
			DrawGraph(0, 200, _cgMenu, true);
		}
	
	return true;
}

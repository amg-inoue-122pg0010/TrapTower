#include "ModeGameOver.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "ApplicationGlobal.h"

/**
* @file ModeGameOver.cpp
* @brief ゲームオーバー画面の表示
* @author 井上和哉、石塚泉
*/

ModeGameOver::ModeGameOver() {
	_sizeX = 1920;
	_sizeY = 1080;
	_animeNum = 0;
	_backAnimeMax = 53;
	_cgGameOver.resize(_backAnimeMax);
	_animeCnt = 0;
	_isFlip = false;
	ResourceServer::LoadDivGraph("res/gameover/gameover.png", _backAnimeMax, 8, 7, 1920, 1080, _cgGameOver.data());
	_cgMenu = ResourceServer::LoadGraph("res/GameOver/senntakusi.png");
	_animeMax = 5;
	_cgCursor = ResourceServer::LoadGraph("res/title/yajirusi.png");

	_menuNum = 1;
	PlaySoundMem(gGlobal._bgm["gameover1"], DX_PLAYTYPE_LOOP, true);
	PlaySoundMem(gGlobal._sv["gameover"], DX_PLAYTYPE_BACK, true);
	PlaySoundMem(gGlobal._pv["gameover"], DX_PLAYTYPE_BACK, true);
}

bool ModeGameOver::Process() {
	int trg = ApplicationMain::GetInstance()->GetTrg();

	_animeCnt++;
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

		PlaySoundMem(gGlobal._se["Dicision"], DX_PLAYTYPE_BACK, true);
		StopSoundMem(gGlobal._bgm["gameover1"]);
		switch (_menuNum) {
		case 1:
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeGame(1,3), 1, "game");
			PlaySoundMem(gGlobal._pv["retry"], DX_PLAYTYPE_BACK, true);
			break;
		case 2:

			break;
		case 3:
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "game");
			break;
		default:
			break;
		}
	}

	return true;
}

bool ModeGameOver::Render() {
	

	_animeNum = (_animeCnt / 3) % _backAnimeMax;
	DrawRotaGraph(1920 / 2, 1080 / 2, 1.0, 0, _cgGameOver[_animeNum], TRUE, _isFlip);
	if (_animeCnt / 16 % 2 == 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}
	DrawRotaGraph(580, 500 + (_menuNum * 100), 0.7, 0, _cgCursor, true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 200, _cgMenu, true);
	return true;

}

#include "ModeStageSelect.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"

/**
* @file ModeStageSelect.cpp
* @brief ステージセレクト画面の表示、選択されたステージをスタートする
* @author 井上和哉、酒井大彰
*/

ModeStageSelect::ModeStageSelect() {
	_cgBack = ResourceServer::LoadGraph("res/StageSelect/stageselect_pattern1.png");

	_animeMax = 5;
	_stagenumMax = 8;

	_cgCursor = ResourceServer::LoadGraph("res/title/yajirusi.png");
	_menuNum = 1;
	_animeCnt = 0;
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/1-1.png");
	_cgStages[0] = _cgStage;
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/1-2.png");
	_cgStages[1] = _cgStage; 
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/1-3.png");
	_cgStages[2] = _cgStage;
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/2-1.png");
	_cgStages[3] = _cgStage;
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/2-2.png");
	_cgStages[4] = _cgStage;
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/2-3.png");
	_cgStages[5] = _cgStage;
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/3-1.png");
	_cgStages[6] = _cgStage;
	_cgStage = ResourceServer::LoadGraph("res/StageSelect/3-2.png");
	_cgStages[7] = _cgStage;
	PlaySoundMem(gGlobal._bgm["Select"], DX_PLAYTYPE_LOOP, true);
}

bool ModeStageSelect::Process() {
	int trg = ApplicationMain::GetInstance()->GetTrg();

	_stageNum = (_stagenumMax - (_stagenumMax - _menuNum));
	//項目を選ぶ
	if (trg & PAD_INPUT_UP) {
		_menuNum++; _animeCnt = 0;
		PlaySoundMem(gGlobal._se["Select"], DX_PLAYTYPE_BACK, true);
	}
	if (trg & PAD_INPUT_DOWN) {
		_menuNum--; _animeCnt = 0;
		PlaySoundMem(gGlobal._se["Select"], DX_PLAYTYPE_BACK, true);
	}
	_menuNum = Math::Clamp(_menuNum, 1, _stagenumMax);

	//決定
	if (trg & PAD_INPUT_2) {
		PlaySoundMem(gGlobal._se["Dicision"], DX_PLAYTYPE_BACK, true);
		StopSoundMem(gGlobal._bgm["Select"]);

			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeGame(_stageNum,3), 1, "game");

	}
	else if (trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "game");
	}

	return true;
}

bool ModeStageSelect::Render() {

	DrawGraph(0, 0, _cgBack, false);
	//カーソル
	_animeNum = (_animeCnt / 3) % _animeMax;
	if (_animeCnt / 16 % 2 == 0) {
		DrawRotaGraph(500, 400 + ((_stagenumMax - (_menuNum + 1)) * ((700 / _stagenumMax))), 0.6, 0, _cgCursor, true, true);
	}

	DrawGraph(0, 0, _cgStages[_stageNum - 1 ], true);
	return true;
}

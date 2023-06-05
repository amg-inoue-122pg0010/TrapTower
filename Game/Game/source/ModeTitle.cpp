#include "ModeTitle.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeStageSelect.h"
#include "ApplicationGlobal.h"

/**
* @file ModeTitle.cpp
* @brief タイトルの表示
* @author 井上和哉、石塚泉
*/

   ModeTitle::ModeTitle(){
	   _cgBack = ResourceServer::LoadGraph("res/title/UI_Start002.png");
	   _cgPressButton = ResourceServer::LoadGraph("res/title/push.png");

	   _cgMenu = ResourceServer::LoadGraph("res/title/taitoru_senntaku.png");
	   _cgLogo = ResourceServer::LoadGraph("res/title/title.png");
	   _animeMax = 5;
	   _cgCursor = ResourceServer::LoadGraph("res/title/yajirusi.png");
	   _menuNum = 1;
	   _state = State::title;
	   _animeCnt = 0;
	   PlaySoundMem(gGlobal._bgm["title"], DX_PLAYTYPE_LOOP, true);
	   gGlobal._time = 0;
   }

   bool ModeTitle::Process() {
	   int trg = ApplicationMain::GetInstance()->GetTrg();

	   _animeCnt++;
	   switch (_state) {

	   case State::title:
		   if (trg & PAD_INPUT_2) {
			   _state = State::menu;
			   _animeCnt = 0;
			   PlaySoundMem(gGlobal._se["Dicision"], DX_PLAYTYPE_BACK, true);
		   }
		   break;
	   case State::menu:
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
			   StopSoundMem(gGlobal._bgm["title"]);
			   switch (_menuNum) {
			   case 1:
				   //ゲーム本編
				   ModeServer::GetInstance()->Del(this);
				   ModeServer::GetInstance()->Add(new ModeGame(1,3), 1, "game");
				   break;
			   case 2:
				   //ステージセレクトモード
				   ModeServer::GetInstance()->Del(this);
				   ModeServer::GetInstance()->Add(new ModeStageSelect(), 1, "stageselect");
				   break;
			   case 3:
				   DxLib_End();
				   break;				
			   default:
				   break;
			   }
		   }

		   break;
	   default:
		   break;
	   }
	   return true;
   }

   bool ModeTitle::Render() {

	   DrawGraph(0, 0, _cgBack, false);

	   //_cgPressButtonを点滅させる
	   bool PressButton = false;
	   int i = _animeCnt / 30;
	   if (i % 2 == 0) {
		   PressButton = true;
	   }

	   if (_state == State::title && PressButton) {
		   DrawRotaGraph(1980 / 2, 350, 1.3, 0, _cgPressButton, true, false);
	   }

	   if (_state == State::menu) {
		   _animeNum = (_animeCnt / 3) % _animeMax;

		   if (_animeCnt / 16 % 2 == 0) {
			   DrawRotaGraph(1020, 700 + (_menuNum * 95), 0.6, 0, _cgCursor, true, false);
		   }
		   DrawGraph(0, 0, _cgMenu, true);
	   }
	   DrawGraph(0, 0, _cgLogo, true);
	   return true;
   }

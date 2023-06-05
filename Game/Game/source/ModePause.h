#pragma once
#include "AppFrame.h"
#include "ModeGame.h"

/**
* @file ModeMenu.cpp
* @author ���a��
*/

class ModePause : public ModeBase {

	typedef ModeBase base;
public:
	ModePause(ModeGame* modegame);

	bool	Process();
	bool	Render();

protected:
	ModeGame* _modeGame;

	int _keyConfig;
	bool _drawConfig;
	int _configAlfa;
};


#pragma once
#include "..\..\AppFrame\source\Mode\ModeBase.h"
#include "AppFrame.h"

/**
* @file ModeStageSelect.h
* @author ���a�ƁA����史
*/

class ModeStageSelect : public ModeBase {
public:
	ModeStageSelect();

	bool	Process();
	bool	Render();

protected:
	int _cgStage;
	int _cgStages[8];
	int _stagenumMax;
	int _stageNum;

};


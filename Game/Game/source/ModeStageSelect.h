#pragma once
#include "..\..\AppFrame\source\Mode\ModeBase.h"
#include "AppFrame.h"

/**
* @file ModeStageSelect.h
* @author à‰è„òaç∆ÅAéà‰ëÂè≤
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


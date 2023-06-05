#include "ModeTitle.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeAmgLogo.h"

/**
* @file ModeAmgLogo.cpp
* @brief Logoをフェードイン・アウトで表示
* @author 酒井大彰
*/

ModeAmgLogo::ModeAmgLogo() {
	_alfa_swich = false;
	_alfa = 250;
	_logo = ResourceServer::LoadGraph("res/title/AMG-LOGO.png");

}

bool ModeAmgLogo::Process() {
	int trg = ApplicationMain::GetInstance()->GetTrg();
	if (trg & PAD_INPUT_2) {
		_alfa_swich = true;
	}

	if (_alfa_swich)
	{
		_alfa += 3;
		if (_alfa == 255)
		{
			ModeServer::GetInstance()->Del(this);
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
		}
	}
	else {
		_alfa -= 5;
		if (_alfa <= 0) {
			_alfa = 0;
		}
	}
	return true;
}

bool ModeAmgLogo::Render() {
	DrawGraph(320, 438, _logo, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alfa);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	return true;
}
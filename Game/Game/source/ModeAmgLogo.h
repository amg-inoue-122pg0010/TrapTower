#pragma once
#include "..\..\AppFrame\source\Mode\ModeBase.h"
#include "AppFrame.h"

/**
* @file ModeAmgLogo.h
* @author éà‰ëÂè≤
*/

class ModeAmgLogo : public ModeBase {
public:
  ModeAmgLogo();

  bool	Process();
  bool	Render();

protected:
  bool _alfa_swich;
  int _alfa;
  int _logo;
};
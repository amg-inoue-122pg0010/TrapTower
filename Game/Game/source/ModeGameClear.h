#pragma once
#include <vector>
#include "appframe.h"

/**
* @file ModeGameClear.h
* @author ���a�ƁA�Βː�
*/

class ModeGameClear :
    public ModeBase
{
public:
    ModeGameClear();
    bool	Process();
    bool	Render();

protected:
    int _score;
    std::vector<int> _cgGameClear;
    std::unordered_map<int, int> _displayTimes;
    bool _sel = false;
    int _screenBright = 0;//��ʂ̖��邳

};


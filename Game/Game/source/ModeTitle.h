#pragma once
#include "..\..\AppFrame\source\Mode\ModeBase.h"
#include "AppFrame.h"

/**
* @file ModeTitle.h
* @author ���a�ƁA�Βː�
*/

class ModeTitle :
    public ModeBase
{
public:
    ModeTitle();

    bool	Process();
    bool	Render();
    
    //��ʂ̏��
    enum State {
        title,
        menu,
    };
    State _state;

protected:
    int _cgLogo;
    int _cgPressButton;

};


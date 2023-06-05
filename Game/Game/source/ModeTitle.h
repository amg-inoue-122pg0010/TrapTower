#pragma once
#include "..\..\AppFrame\source\Mode\ModeBase.h"
#include "AppFrame.h"

/**
* @file ModeTitle.h
* @author ˆäã˜aÆAÎ’Ëò
*/

class ModeTitle :
    public ModeBase
{
public:
    ModeTitle();

    bool	Process();
    bool	Render();
    
    //‰æ–Ê‚Ìó‘Ô
    enum State {
        title,
        menu,
    };
    State _state;

protected:
    int _cgLogo;
    int _cgPressButton;

};


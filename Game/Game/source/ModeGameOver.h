#pragma once
#include <vector>
#include "appframe.h"

/**
* @file ModeGameOver.h
* @author ˆäã˜aÆAÎ’Ëò
*/

class ModeGameOver :
    public ModeBase
{
public:
    ModeGameOver();

    bool	Process();
    bool	Render();

private:
    int _sizeX;
    int _sizeY;
    std::vector<int> _cgGameOver;
    bool _isFlip;
};



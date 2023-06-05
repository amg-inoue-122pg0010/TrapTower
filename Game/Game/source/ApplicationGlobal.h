#pragma once

#include "appframe.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

public:
	int		_cgCursor;
	std::unordered_map<std::string, int>	_pv;	// プレイヤーボイスマップ
	std::unordered_map<std::string, int>	_sv;	// システムボイスマップ
	std::unordered_map<std::string, int>	_se;	// SEマップ
	std::unordered_map<std::string, int>	_bgm;	// BGMマップ
	int _time = 0;
}; 

// 他のソースでgGlobalを使えるように
extern ApplicationGlobal		gGlobal;

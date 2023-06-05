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
	std::unordered_map<std::string, int>	_pv;	// �v���C���[�{�C�X�}�b�v
	std::unordered_map<std::string, int>	_sv;	// �V�X�e���{�C�X�}�b�v
	std::unordered_map<std::string, int>	_se;	// SE�}�b�v
	std::unordered_map<std::string, int>	_bgm;	// BGM�}�b�v
	int _time = 0;
}; 

// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal		gGlobal;


#include "AppFrame.h"
#include "ApplicationGlobal.h"

// ŽÀ‘Ì
ApplicationGlobal		gGlobal;

ApplicationGlobal::ApplicationGlobal() {
}

ApplicationGlobal::~ApplicationGlobal() {
}


bool ApplicationGlobal::Init() {
	_cgCursor = ResourceServer::LoadGraph("res/cursor.png");

	_pv["damege1"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_damage01.mp3");//
	_pv["damege2"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_damage02.mp3");//
	_pv["dead"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_dead.mp3");//
	_pv["gameover"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_gameover.mp3");
	_pv["highscore"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_highscore.mp3");
	_pv["jump1st1"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_jamp1st01.mp3");//
	_pv["jump1st2"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_jamp1st02.mp3");//
	_pv["jump2nd"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_jamp2nd.mp3");//
	_pv["jumpwall"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_jampwall.mp3");//
	_pv["retry"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_retry.mp3");
	_pv["sliding"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_sliding.mp3");//
	_pv["stageclear1"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_stageclear01.mp3");
	_pv["stageclear2"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_stageclear02.mp3");
	_pv["gameclear"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_gameclear.mp3");
	_pv["start"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_start.mp3");
	_pv["stay"] = ResourceServer::LoadSoundMem("res/Audio/LetaVoice/vc_stay.mp3");

	_sv["gameclear"] = ResourceServer::LoadSoundMem("res/Audio/SystemVoice/sysvc_gameclear.mp3");
	_sv["gameover"] = ResourceServer::LoadSoundMem("res/Audio/SystemVoice/sysvc_gameover.mp3");
	_sv["highscore"] = ResourceServer::LoadSoundMem("res/Audio/SystemVoice/sysvc_highscore.mp3");
	_sv["stageclear"] = ResourceServer::LoadSoundMem("res/Audio/SystemVoice/sysvc_stageclear.mp3");
	_sv["sysvc_start"] = ResourceServer::LoadSoundMem("res/Audio/SystemVoice/sysvc_start.mp3");

	_se["laser_damage"] = ResourceServer::LoadSoundMem("res/Audio/SE/SE_laser_damage.mp3");
	_se["Alert"] = ResourceServer::LoadSoundMem("res/Audio/SE/SE_Alert.mp3");
	_se["Dicision"] = ResourceServer::LoadSoundMem("res/Audio/SE/SE_Dicision.mp3");
	_se["Pause"] = ResourceServer::LoadSoundMem("res/Audio/SE/SE_Pause.mp3");
	_se["Select"] = ResourceServer::LoadSoundMem("res/Audio/SE/SE_Select.mp3");
	_se["Sprint"] = ResourceServer::LoadSoundMem("res/Audio/SE/SE_Sprint.mp3");

	_bgm["bgm001"] = ResourceServer::LoadSoundMem("res/Audio/BGM/bgm001.mp3");
	_bgm["clear"] = ResourceServer::LoadSoundMem("res/Audio/BGM/BGM_clear.mp3");
	_bgm["gameover1"] = ResourceServer::LoadSoundMem("res/Audio/BGM/BGM_gameover.mp3");
	_bgm["gameover2"] = ResourceServer::LoadSoundMem("res/Audio/BGM/BGM_gameover02.mp3");
	_bgm["Select"] = ResourceServer::LoadSoundMem("res/Audio/BGM/BGM_Select.mp3");
	_bgm["Stage01"] = ResourceServer::LoadSoundMem("res/Audio/BGM/BGM_Stage01.mp3");
	_bgm["title"] = ResourceServer::LoadSoundMem("res/Audio/BGM/BGM_Title.mp3");
	return true;
}

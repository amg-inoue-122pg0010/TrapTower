#pragma once
#include "appframe.h"
#include <string>
#include "ModeMenu.h"
#include <memory>
#include "../../../AppFrame/Vector3D.h"
#include"ObjectBase.h"
#include"Player.h"
#include "LaserCollisionBase.h"
#include <vector> 
#include "Gimmick.h"
#include <unordered_map>


/**
* @file ModeGame.h
* @author ���a��
*/

// �v�Z�p�}�N��
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

// �J����
class Camera {
public:
	VECTOR	_vPos;					// �ʒu
	VECTOR	_vTarget;				// ����
	float	_clipNear, _clipFar;	// �N���b�v
};
// ���[�h
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	ModeGame(int stn,int conte);
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	bool GetDebugViewColloion() { return _bViewCollision; }
	void SetDebugViewColloion(bool b) { _bViewCollision = b; }
	bool GetDebugUseColloion() { return _bUseCollision; }
	void SetDebugUseColloion(bool b) { _bUseCollision = b; }
	bool GetDebugViewCameraInfo() { return _bViewCameraInfo; }
	void SetDebugViewCameraInfo(bool b) { _bViewCameraInfo = b; }
	bool GetDebugStageJump() { return _stageJump; }
	void SetDebugStageJump(bool b) { _stageJump = b; }
	bool GetCamChenge() { return _camChenge; }

	bool GetDebugReStage() { return _reStage; }
	void SetDebugReStage(bool b) { _reStage = b; }

	int GetTime() { return _time; }
	bool GetDebugCup() { return _bViewCollision; }

	int GetStageFloorCollision() { return _stageCollisionFloor; };
	std::vector<int> GetStageWallCollision() { return _stageWallCollisions; }//�f�o�b�O
	std::vector<std::shared_ptr<GimmickBase>> GetGimmickCollision() { return _gimmicks; };

	Player _player;
	
	//���[�U�[�̏��
	struct LaserData {
		std::vector<VECTOR> _vPoses;  //���[�U�[�̎n�܂�ƏI���̍��W
		int _type;  //���[�U�[�̎��
		std::vector<int> _trapNums; //�N��������g���b�v�̔ԍ�
		int _form;
		int _stageNum;
		bool _move;//������
		std::vector<VECTOR> _movedVPoses;
		bool _switch;//�X�C�b�`���邩
		std::vector<VECTOR> _switchVPoses;
		std::vector<VECTOR> _switchMovedVPoses;
		//�~�`�p
		float _delay;//�X�e�[�W�X�^�[�g����N������܂ł̎���
		float _spd;//�g��̑���

	};
	std::vector<LaserData> _laserData;
	std::vector<std::shared_ptr<LaserCollBase>> lasers;//�S���[�U�[�̔z��

	//�g���b�v�̏��
	struct TrapData {
		VECTOR _vPos;
		int _type;
		int _stageNum;
		VECTOR _movedVPos;
		std::vector<int> _switchLaserNum;
		int _spd;
	};
	std::vector<TrapData> _trapData;
	std::vector<std::shared_ptr<GimmickBase>> _gimmicks;//�S�M�~�b�N�̔z��

	//�v���C���[�̏��
	Player::PlayerData _playerData;

protected:

	// �J����
	Camera	_cam;

	// 3D���f���`��p
	int _handle;

	int _time;
	//�~�`�̃��[�U�[�Ɠ����蔻��
	bool CheckHitRoundCircleHorizontal();
	bool CheckHitRoundCircleVertical();

	//json�ǂݍ���
	//json�t�@�C����ǂݍ���Ŕz��ɏ����܂Ƃ߂�
	void LoadJsonfile(); 

	// �f�o�b�O�p
	bool _bViewCollision;
	bool _bUseCollision;
	bool _bViewCameraInfo;
	bool _stageJump;
	bool _reStage;

	// �}�b�v�p
	int _handleMap;
	int _handleSkySphere;
	int _frameMapCollision;

	//�X�e�[�W�̓����蔻��
	std::vector<int> _stageWallCollisions;
	int _stageCollisionFloor;

	//�S�[���p
	VECTOR _gspos = VGet(0, 300, 8000);
	VECTOR _gepos = VGet(0, 0, 8000);
	float _gr = 64;
	int _stn = 1;//�X�e�[�W�i���o�[
	int _stageMax;
	int _goalModel;
	int _goalEffect;
	int _playingGoalEffect;

	//����
	int _light;
	// �V���h�E�}�b�v�p
	int _handleShadowMap;
	int _handleShadowMap_2;

	//UI�N���X
	std::vector<int> _hp;
	std::unordered_map<int, int> _displayTimes;
	std::unordered_map<int, int> _remain;

	int _screenBright = 0;//��ʂ̖��邳

	int _conte;//�R���e�B�j���[��
	bool _camChenge;//�J�����̐؂�ւ�������Ă��邩

}; 



#pragma once
#include"singletonBase.h"
#include<map>

//fmod.hpp추가
#include"inc/fmod.hpp"
//lib링크
#pragma comment (lib, "lib/fmodex_vc.lib")

using namespace FMOD;

//여유분의 채널 갯수 설정(버퍼)
#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 5

//총 사운드 갯수
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:

	typedef map<string, Sound**>arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsiter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

private:

	System * _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;




public:

	HRESULT init(void);
	void release(void);
	void update(void);
	//추가
	void addSound(string keyName, string soundName, bool bgm, bool loop);
	//시작
	void play(string keyName, float volume = 1.0f);
	//정지
	void stop(string keyName);
	//일시정지
	void pause(string keyName);
	//다시시작
	void resume(string keyName);


	//플레이중이냐
	bool isPlaySound(string keyName);
	//정지 중이냐
	bool isPauseSound(string keyName);
	soundManager();
	~soundManager();
};


#include "stdafx.h"
#include "soundManager.h"


soundManager::soundManager()
	:_system(NULL),_sound(NULL),_channel(NULL)
{
}


soundManager::~soundManager()
{
}
HRESULT soundManager::init(void)
{
	//FMOD사운드 엔진을 쓰겠다고 선언
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_sound = new Sound*[TOTALSOUNDBUFFER];
	_channel = new Channel*[TOTALSOUNDBUFFER];

	memset(_sound, 0, sizeof(Sound*)*(TOTALSOUNDBUFFER));
	memset(_channel, 0, sizeof(Sound*)*(TOTALSOUNDBUFFER));



	return S_OK;
}
void soundManager::release(void)
{

}
void soundManager::update(void)
{
	_system->update();
}
//추가
void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds
				.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds
				.size()]);
		}
	}
	else
	{
		if (bgm)
		{
			_system
				->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system
				->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
		}
	}
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}
//시작
void soundManager::play(string keyName, float volume)
{
	arrSoundsiter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);

			_channel[count]->setVolume(volume);
			break;
		}
	}
}
//정지
void soundManager::stop(string keyName)
{
	arrSoundsiter iter = _mTotalSounds.begin();
	int count = 0;


	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}
//일시정지
void soundManager::pause(string keyName)
{

	arrSoundsiter iter = _mTotalSounds.begin();

	int count = 0;


	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}

}
//다시시작
void soundManager::resume(string keyName)
{
	arrSoundsiter iter = _mTotalSounds.begin();

	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}


//플레이중이냐
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	arrSoundsiter iter = _mTotalSounds.begin();
	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}
//정지 중이냐
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	arrSoundsiter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}
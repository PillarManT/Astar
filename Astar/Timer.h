#pragma once
class Timer
{
private :  

	bool _isHardware;			//고성능 타이머를 지원하느냐?
	float _timeScale;			//시간경과량
	float _timeElapsed;			//한 프레임당 경과량
	__int64 _curTime;			//현재시간
	__int64 _lastTime;			//마지막시간
	__int64 _periodFrequency;	//시간주기



	unsigned long _frameRate;		//FPS
	unsigned long _FPSFrameCount;	//FPS카운트
	float _FPSTimeElapsed;			//FPS마지막시간과 현재시간의 경과량
	float _worldTime;				//전체시간 경과량


public:

	//타이머 초기화
	HRESULT init();

	//현재시간 계산
	void tick(float lockFPS = 0.0f);

	//현재 FPS가져온다.
	unsigned long getFrameRate(char* str = nullptr)const;

	//한프레임당 경과시간
	float getElapsedTime() const { return _timeElapsed; }


	//전체 경과시간 가져온다,
	float getWorldTime() const { return _worldTime; }

	Timer();
	~Timer();
};


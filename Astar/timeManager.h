#pragma once
#include"singletonBase.h"
#include"Timer.h"
class timeManager : public singletonBase<timeManager>
{
private :

	Timer* _timer;


public:

	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(HDC hdc);

	//한프레임당 경과시간 가져오기 1/60
	float getElapsedTime() const { return _timer->getElapsedTime(); }

	//전체 시간 경과량 가져오기
	float getWorldTime() const { return _timer->getWorldTime(); }





	timeManager();
	~timeManager();
};


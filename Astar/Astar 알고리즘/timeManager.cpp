#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
{
}


timeManager::~timeManager()
{
}
HRESULT timeManager::init(void)
{

	_timer = new Timer;
	_timer->init();



	return S_OK;
}
void timeManager::release(void)
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}
void timeManager::update(float lock)
{	
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}
void timeManager::render(HDC hdc)
{
	char str[256];

	string strFrame;

	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(0, 0, 0));

#ifdef _DEBUG

	if (_timer != nullptr)
	{
		////FPS
		//sprintf(str, "FPS :  %d", _timer->getFrameRate());
		//TextOut(hdc, 0, 0, str, strlen(str));

		////전체 경과 시간
		//sprintf(str, "WorldTime :  %f", _timer->getWorldTime());
		//TextOut(hdc, 0, 20, str, strlen(str));


		////한 프레임당 경과시간
		//sprintf(str, "ElapsedTime :  %f", _timer->getElapsedTime());
		//TextOut(hdc, 0, 40, str, strlen(str));

	}
#else
	if (_timer != nullptr)
	{
		//FPS
		sprintf(str, "FPS :  %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif //_DEBUG
}
#include "stdafx.h"
#include "pixelCollisionTest.h"


pixelCollisionTest::pixelCollisionTest()
{
}


pixelCollisionTest::~pixelCollisionTest()
{
}
HRESULT pixelCollisionTest::init(void)
{
	IMAGEMANAGER->addImage("언덕", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(254, 0, 254));
	_ball = IMAGEMANAGER->addImage("공", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2 - 100;
	_y = WINSIZEY / 2 + 110;


	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//검사하는 Y축셋팅
	_probeY = _y + _ball->getHeight() / 2;




	return S_OK;
}
void pixelCollisionTest::release(void)
{
}
void pixelCollisionTest::update(void) 
{
	//픽셀검사에서 중요한건 연산방법~~~~
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;
	}

	//검사하는 프로브도 실시간으로 보정합시당
	_probeY = _y + _ball->getHeight() / 2;


	//범위는 아래와 같이 
	for (int i = _probeY - 50; i < _probeY + 50; ++i)
	{
		//픽셀 정보값을 가져와서 컬러 레퍼런스에 담자

		COLORREF color = GetPixel(IMAGEMANAGER->findImage("언덕")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 254 && g == 0 && b == 254))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
}
void pixelCollisionTest::render(void)
{
	IMAGEMANAGER->findImage("언덕")->render(getMemDc(), 0, 0);
	_ball->render(getMemDc(), _rc.left, _rc.top);
}
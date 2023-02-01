// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ ��Ÿ�� ��� �����Դϴ�.
//#include<iostream>


//���� ���� STL
#include<string>
//#include<vector>
//#include<list>
//#include<map>


//====================================
// ##���� ���� ������� ��⿡ �߰�!!
//====================================
#include"commonMacroFunction.h"
#include"randomFuction.h"
#include"keyManager.h"
#include"util.h"
#include"imageManager.h"
#include"timeManager.h"
#include"soundManager.h"
#include"txtData.h"
#include"collision.h"
using namespace std;
using namespace MY_UTIL;
//====================================
//    ##�̱��� �߰�
//====================================
//�����Լ� ������
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()

#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER  timeManager::getSingleton()

#define SOUNDMANAGER soundManager::getSingleton()
#define TXTDATA      txtData::getSingleton()

//====================================
//   ##������ �� ##(������ �ʱ�ȭ ����)
//====================================

#define WINNAME (LPTSTR)(TEXT("Astar"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX  1280
#define WINSIZEY  720

#define WINSTYLE  WS_CAPTION|WS_SYSMENU

//enum
enum TYPE
{
	NORMAL,
	START,
	ARRIVE,
	BLOCKED,
	RANGE,
	ROUTE,
	PLAYER
};

#define MAPSIZE	 10
#define FONTSIZE 15

//===============================================
//   ##��ũ�� �Լ� ##(���ΰ��� ������ �κп��� ���)
//===============================================

#define SAFE_DELETE(p)  {if(p) {delete(p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)  {if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if(p){(p)->release();(p)=nullptr;}}

//=================================================
//   ##�������� ## (�ν��Ͻ�, ������ �ڵ�, ���콺 ��ǥ)
//=================================================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

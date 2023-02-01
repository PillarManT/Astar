#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{

}
mainGame::~mainGame()
{

}
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("normal", "resource/tile.bmp", 60, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("start", "resource/tile_start.bmp", 60, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("arrive", "resource/tile_arrive.bmp", 60, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("blocked", "resource/tile_blocked.bmp", 60, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("range", "resource/tile_range.bmp", 60, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("route", "resource/tile_route.bmp", 60, 60, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("player", "resource/player.bmp", 60, 60, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("play", "resource/start.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stop", "resource/stop.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("reset", "resource/reset.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("select", "resource/select.bmp", 240, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("choice", "resource/choice.bmp", 60, 60, true, RGB(255, 0, 255));

	map = new BL*[MAPSIZE];
	for (int i = 0; i < MAPSIZE; i++)
	{
		map[i] = new BL[MAPSIZE];
	}
	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			map[i][j].blNum.x = j;
			map[i][j].blNum.y = i;
			map[i][j].blPos.x = 50 + map[i][j]._img->getWidth()*j - 3 * j;
			map[i][j].blPos.y = 50 + map[i][j]._img->getHeight()*i - 3 * i;
			map[i][j].rc = { map[i][j].blPos.x,map[i][j].blPos.y,map[i][j].blPos.x + map[i][j]._img->getWidth(),
				map[i][j].blPos.y + map[i][j]._img->getHeight() };
		}
	}

	startPos = { 0,0 };
	arrivePos = { 0,0 };

	font1 = CreateFont(FONTSIZE, 0, 0, 0, 300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("궁서체"));
	oldFont = (HFONT)SelectObject(getMemDc(), font1);

	a = 0;
	result = blNum = 0;

	isSameRoute = false;
	isGoal = false;
	isStart = false;
	blSearch = false;
	_type = NORMAL;

	select = { 700,300,940,360 };
	play = { 900,200,1000,300 };
	stop = { 800,400,900,500 };
	reset = { 1000,380,1100,480 };
	isPlay = false;
	totalRoute = 0;
	upbo = 0;
	return S_OK;
}
void mainGame::release(void)
{
	gameNode::release();

	DeleteObject(font1);
	DeleteObject(oldFont);

}
void mainGame::update(void)
{
	gameNode::update();
	if (isPlay) a++;

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		blSearch = false;
		if (PtInRect(&play, _ptMouse))isPlay = true;
		else if (PtInRect(&stop, _ptMouse))isPlay = false;
		else if (PtInRect(&reset, _ptMouse))
		{
			for (int i = 0; i < MAPSIZE; i++)
			{
				for (int j = 0; j < MAPSIZE; j++)
				{
					setNormalPos(j, i);
				}
			}
			totalRoute = 0;
			v_range.clear();
			v_route.clear();
			v_return.clear();
			isPlay = false;
		}
		else
		{
			for (int i = 0; i < MAPSIZE; i++)
			{
				if (blSearch)break;
				for (int j = 0; j < MAPSIZE; j++)
				{
					if (blSearch)break;
					if (PtInRect(&map[i][j].rc, _ptMouse))
					{
						switch (_type)
						{
						case NORMAL:
							setNormalPos(j, i);
							break;
						case START:
							setStartPos(j, i);
							break;
						case ARRIVE:
							setArrivePos(j, i);
							break;
						case BLOCKED:
							setBlockedPos(j, i);
							break;
						}
						blSearch = true;
					}
				}
			}
		}
	}
	if (KEYMANAGER->isonceKeyDown('0'))
	{
		_type = NORMAL;
	}
	if (KEYMANAGER->isonceKeyDown('1'))
	{
		_type = BLOCKED;
	}
	if (KEYMANAGER->isonceKeyDown('2'))
	{
		_type = START;
	}
	if (KEYMANAGER->isonceKeyDown('3'))
	{
		_type = ARRIVE;
	}

	if (a == 20 && !isGoal&&isPlay)
	{
		result = 0;
		setAroundBlock(player.blNum.x, player.blNum.y);
		for (int i = 0; i < v_range.size(); i++)
		{
			if (i == 0)
			{
				blNum = 0;
				result = v_range[i].result;
			}
			if (result > v_range[i].result)
			{
				result = v_range[i].result;
				blNum = i;
			}
		}
		player = v_range[blNum];
		setRoutePos(player.blNum.x, player.blNum.y);
		playerInit();
		totalRoute++;
		map[player.blNum.y][player.blNum.x].routeNum = totalRoute;
		v_route.push_back(player);
		if (player.blNum.x == arrivePos.x&&
			player.blNum.y == arrivePos.y)
			isGoal = true;
		a = 0;
	}
	else if (a == 20 && isGoal)
	{
		setReturnRoute(player.blNum.x, player.blNum.y);
		for (int i = 0; i < v_range.size(); i++)
		{
			if (i == 0)
			{
				blNum = 0;
				player.routeNum = v_range[i].routeNum;
			}
			if (player.routeNum > v_range[i].routeNum)
			{
				player.routeNum = v_range[i].routeNum;
				blNum = i;
			}
		}
		player = v_range[blNum];
		v_return.push_back(player);
		a = 0;
	}

}
void mainGame::render(void)
{
	//건들지 말것
	//==================================================//
	PatBlt(getMemDc(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==================================================//
	//위에 건들지 마라 경고한다~~~//

	for (int i = 0; i < MAPSIZE; i++)
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			map[j][i]._img->render(getMemDc(), map[j][i].blPos.x, map[j][i].blPos.y);
			/*sprintf(map[j][i].str, "%d", map[j][i].cost);
			TextOut(getMemDc(), map[j][i].blPos.x + FONTSIZE / 5, map[j][i].rc.bottom - FONTSIZE - 2,
				map[j][i].str, strlen(map[j][i].str));
			sprintf(map[j][i].str, "%d", map[j][i].distance);
			TextOut(getMemDc(), map[j][i].rc.right - FONTSIZE * 1.5, map[j][i].rc.bottom - FONTSIZE - 2,
				map[j][i].str, strlen(map[j][i].str));
			sprintf(map[j][i].str, "%d", map[j][i].result);
			TextOut(getMemDc(), map[j][i].blPos.x + FONTSIZE / 5, map[j][i].blPos.y + FONTSIZE / 5, map[j][i].str, strlen(map[j][i].str));*/
		}
	}
	if (isGoal)
	{
		for (int i = 0; i < v_return.size(); i++)
		{
			IMAGEMANAGER->render("choice", getMemDc(), v_return[i].blPos.x, v_return[i].blPos.y);
		}
	}
	if (isPlay) IMAGEMANAGER->render("player", getMemDc(), player.blPos.x, player.blPos.y);
	IMAGEMANAGER->render("select", getMemDc(), select.left, select.top);
	IMAGEMANAGER->render("play", getMemDc(), play.left, play.top);
	IMAGEMANAGER->render("stop", getMemDc(), stop.left, stop.top);
	IMAGEMANAGER->render("reset", getMemDc(), reset.left, reset.top);

	//////////////////////////
	TIMEMANAGER->render(getMemDc());
	//얘도 건들지 말것
	//==================================================//
	this->getBackBuffer()->render(getHDC(), 0, 0);
	//==================================================//
	//위에 건들지 마라 경고한다~~~//
}

void mainGame::setNormalPos(int x, int y)
{
	map[y][x].cost = 0;
	map[y][x].distance = 0;
	map[y][x].result = 0;
	map[y][x]._type = NORMAL;
	map[y][x]._img = IMAGEMANAGER->findImage("normal");
	map[y][x].routeNum = 0;
}

void mainGame::setStartPos(int x, int y)
{
	setNormalPos(startPos.x, startPos.y);
	startPos.x = x;
	startPos.y = y;
	map[y][x]._type = START;
	map[y][x]._img = IMAGEMANAGER->findImage("start");

	player.blNum = startPos;
	player.blPos = map[startPos.y][startPos.x].blPos;
	playerInit();
}

void mainGame::setArrivePos(int x, int y)
{
	setNormalPos(arrivePos.x, arrivePos.y);
	arrivePos.x = x;
	arrivePos.y = y;

	map[y][x]._type = ARRIVE;
	map[y][x]._img = IMAGEMANAGER->findImage("arrive");
}

void mainGame::setBlockedPos(int x, int y)
{
	map[y][x]._type = BLOCKED;
	map[y][x]._img = IMAGEMANAGER->findImage("blocked");
	map[y][x].isBlocked = true;
}

void mainGame::setRoutePos(int x, int y)
{
	map[y][x]._type = ROUTE;
	map[y][x]._img = IMAGEMANAGER->findImage("route");
}

void mainGame::setRangePos(int x, int y)
{
	if (startPos.x == x && startPos.y == y) return;

	map[y][x]._type = RANGE;
	map[y][x]._img = IMAGEMANAGER->findImage("range");
}

void mainGame::setAroundBlock(int x, int y)
{
	v_range.clear();
	for (int i = y - 1; i < y + 2; i++)
	{
		for (int j = x - 1; j < x + 2; j++)
		{
			if (j >= 0 && j < MAPSIZE&&i >= 0 && i < MAPSIZE)
			{
				isSameRoute = false;
				if (i == y && j == x ||
					map[i][j]._type == BLOCKED)continue;
				for (int k = 0; k < v_route.size(); k++)
				{
					if (v_route[k].blNum.x == map[i][j].blNum.x&&
						v_route[k].blNum.y == map[i][j].blNum.y ||
						startPos.x == j && startPos.y == i)
						isSameRoute = true;
				}
				if (isSameRoute)continue;
				setRangePos(map[i][j].blNum.x, map[i][j].blNum.y);
				setBlockValue(x, y, &map[i][j]);
				v_range.push_back(map[i][j]);
				upbo = 0;
			}
		}
	}
	if (v_range.size() == 0)
	{
		v_range.push_back(v_route.at(v_route.size() - 2 - upbo));
		upbo += 2;
	}
}

void mainGame::setBlockValue(int x, int y, BL*_bl)
{
	if (x == _bl->blNum.x || y == _bl->blNum.y)
		_bl->cost = 10;
	else _bl->cost = 14;
	_bl->distance = 0;

	if (arrivePos.x > _bl->blNum.x) _bl->distance += (arrivePos.x - _bl->blNum.x) * 10;
	else if (arrivePos.x < _bl->blNum.x)_bl->distance += (_bl->blNum.x - arrivePos.x) * 10;
	if (arrivePos.y > _bl->blNum.y) _bl->distance += (arrivePos.y - _bl->blNum.y) * 10;
	else if (arrivePos.y < _bl->blNum.y)_bl->distance += (_bl->blNum.y - arrivePos.y) * 10;

	_bl->result = _bl->cost + _bl->distance;
}

void mainGame::setReturnRoute(int x, int y)
{
	v_range.clear();
	for (int i = y - 1; i < y + 2; i++)
	{
		for (int j = x - 1; j < x + 2; j++)
		{
			if (j >= 0 && j < MAPSIZE&&i >= 0 && i < MAPSIZE)
			{
				if (map[i][j].routeNum != 0)
				{
					v_range.push_back(map[i][j]);
				}
			}
		}
	}
}

void mainGame::playerInit()
{
	player._img = IMAGEMANAGER->findImage("route");
	player._type = PLAYER;
}

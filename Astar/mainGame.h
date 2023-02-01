#pragma once
#include"gameNode.h"

typedef struct BLOCK
{
	POINT blNum;
	POINT blPos;
	RECT rc;
	int result, cost, distance;
	char str[256];
	bool isBlocked;
	image* _img;
	TYPE _type;
	int routeNum;
	BLOCK()
	{
		blPos = blNum = { 0, };
		rc = { 0, };
		result = cost = distance = 0;
		isBlocked = false;
		_img = IMAGEMANAGER->findImage("normal");
		_type = NORMAL;
		routeNum = 0;
	}
}BL;
class mainGame : public gameNode
{
private:


	BL ** map;
	//vector<BL> v_map;
	BL player;
	POINT startPos;
	POINT arrivePos;
	vector<BL> v_range;
	vector<BL> v_route;
	vector<BL> v_return;
	int a;
	int result, blNum;

	HFONT oldFont, font1;

	bool isSameRoute;
	bool isGoal;
	bool isStart;
	bool blSearch;
	TYPE _type;

	RECT select, play, stop, reset;
	bool isPlay;
	int totalRoute;
	int upbo;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setNormalPos(int x, int y);
	void setStartPos(int x, int y);
	void setArrivePos(int x, int y);
	void setBlockedPos(int x, int y);
	void setRoutePos(int x, int y);
	void setRangePos(int x,int y);
	void setAroundBlock(int x, int y);
	void setBlockValue(int x,int y,BL*_bl );
	void setReturnRoute(int x, int y);
	void playerInit();

	mainGame();
	~mainGame();
	
};//«¡∑Œ¡ß∆Æ æ”∫Ú


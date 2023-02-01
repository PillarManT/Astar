#pragma once
#include"gameNode.h"
class pixelCollisionTest :public gameNode
{
private : 


	image* _ball;

	RECT _rc;
	float _x, _y;


	//y Axis Å½»ç¿ë
	int _probeY;



public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollisionTest();
	~pixelCollisionTest();
};


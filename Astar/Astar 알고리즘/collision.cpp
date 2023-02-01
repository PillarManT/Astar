#include "stdafx.h"
#include "collision.h"


namespace MY_UTIL
{
	//POINT가 사각형안에 있냐
	bool checkPointInRect(const RECT& rc, const POINT& pt)
	{
		if ((rc.left < pt.x && pt.x < rc.right) && (rc.top < pt.y && pt.y < rc.bottom))return true;
		return false;
	}
	bool checkPointInRect(const RECT& rc, int x, int y)
	{
		if ((rc.left < x && x < rc.right) && (rc.top < y && y < rc.bottom))return true;
		return false;
	}
	bool checkPointInRect(const MYRECT& rc, float x, float y)
	{
		if ((rc.left < x && x < rc.right) && (rc.top < y && y < rc.bottom))return true;
		return false;
	}
	bool checkPointInRect(const MYRECT& rc, const MYPOINT& pt)
	{
		if ((rc.left < pt.x && pt.x < rc.right) && (rc.top < pt.y && pt.y < rc.bottom))return true;
		return false;
	}


	//POINT가 원안에 있냐
	bool checkPointCircle(float cX, float cY, float cR, const MYPOINT& pt)
	{
		float deltaX = pt.x - cX;
		float deltaY = pt.y - cY;


		float distSquare = deltaX*deltaX + deltaY*deltaY;

		float radiusSquare = cR* cR;

		if (radiusSquare < distSquare) return false;
		return true;
	}
	bool checkPointCircle(float cX, float cY, float cR, float x, float y)
	{
		float deltaX = x - cX;
		float deltaY = y - cY;

		float distSquare = deltaX*deltaX + deltaY*deltaY;

		float radiusSquare = cR* cR;

		if (radiusSquare < distSquare) return false;
		return true;
	}
	bool checkPointCircle(const MYCIRCLE& rc, float x, float y)
	{
		float deltaX = x - rc.x;
		float deltaY = y - rc.y;

		float distSquare = deltaX*deltaX + deltaY*deltaY;

		float radiusSquare = rc.r * rc.r;

		if (radiusSquare < distSquare) return false;
		return true;

	}
	bool checkPointCircle(const MYCIRCLE& rc, const MYPOINT&pt)
	{
		float deltaX = pt.x - rc.x;
		float deltaY = pt.y - rc.y;

		float distSquare = deltaX*deltaX + deltaY*deltaY;

		float radiusSquare = rc.r * rc.r;


		if (radiusSquare < distSquare) return false;
		return true;

	}

	//사각형이 사각형이랑 부디쳤냐

	bool isCollision(const MYRECT& rc1, const MYRECT& rc2)
	{
		if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
			(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top))return true;

		return false;
	}
	bool isCollision(const RECT& rc1, const RECT& rc2)
	{
		if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
			(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top))return true;

		return false;
	}

	//원과 원이 부디쳤냐
	bool isCollision(const MYCIRCLE& cir1, const MYCIRCLE& cir2)
	{
		float deltaX = cir2.x - cir1.x;
		float deltaY = cir2.y - cir1.y;

		float distSquare = deltaX*deltaX + deltaY*deltaY;
		float radius = cir1.r + cir2.r;

		float radiusSquare = radius* radius;

		if (radiusSquare < distSquare) return false;
		return true;
	}


	//사각형이 원과 부딪쳤냐
	bool isCollision(const MYCIRCLE& cir1, const RECT& rc)
	{
		return false;
	}
	bool isCollision(const MYCIRCLE& cir, const MYRECT& rc)
	{
		return false;
	}

	//부딪쳤다면 어찌 할꺼냐
	bool isCollisionReaction(const RECT& rcHold, RECT& rcMove)
	{
		RECT rcInter;

		if (!IntersectRect(&rcInter, &rcHold, &rcMove))return false;

		int interW = rcInter.right - rcInter.left;
		int interH = rcInter.bottom - rcInter.top;


		if (interW > interH)
		{

			if (rcInter.top == rcHold.top)
			{
				OffsetRect(&rcMove, 0, -interH);
			}
			else if (rcInter.bottom == rcHold.bottom)
			{
				OffsetRect(&rcMove, 0, interH);
			}
		}
		else
		{
			if (rcInter.left == rcHold.left)
			{
				OffsetRect(&rcMove, -interW, 0);
			}
			else if (rcInter.right == rcHold.right)
			{
				OffsetRect(&rcMove, interW, 0);
			}
		}
		return true;


	}
	bool isCollisionReaction(const MYRECT& mrcHold, MYRECT& mrcMove)
	{
		return false;
	}
	bool isCollisionReaction(const MYCIRCLE& cirHold, MYCIRCLE& CirMove)
	{
		float deltaX = CirMove.x - cirHold.x;
		float deltaY = CirMove.y - cirHold.y;
		float distance = sqrtf(deltaX*deltaX + deltaY*deltaY);
		float radius = cirHold.r + CirMove.r;

		if (distance < radius)
		{
			float angle = getAngle(cirHold.x, cirHold.y, CirMove.x, CirMove.y);

			float moveDelta = radius - distance;
			float moveX = cosf(angle) * moveDelta;
			float moveY = -sinf(angle) * moveDelta;


			CirMove.move(moveX, moveY);
			return true;
		}
		return false;
	}
}
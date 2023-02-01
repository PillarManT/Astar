#pragma once

#define DEG_TO_RAD 0.017435 //디그리 1도(라디안값)
#define PI 3.141592654
#define PI2 (PI*2)

#define PI_2		(PI/2)
#define PI_4		(PI/4)
#define PI_8		(PI/8)
#define PI_16		(PI/16)
#define PI_32		(PI/32)

#define FLOAT_TO_INT(f1) static_cast<int>(f1)
#define FLOAT_EPSILON 0.001f		//실수의 가장 작은단위(그리스어)


namespace MY_UTIL  //본인이 원하는 이름으로 바꿔도 됨
{
	float getAngle(float startX, float startY, float endX, float endY);
	float getDistance(float startX, float startY, float endX, float endY);
}


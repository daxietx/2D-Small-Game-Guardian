#include "stdafx.h"
#include <string>
#include "monster.h"
#include"math.h"
#include"time.h"

using namespace std;
Monster::Monster()
{
    x1=300;
	x2=400;
	y=20;
	id=1;
	height =49;
	width = 66;
    blood=3;
	POINT a;
	a.x=100;
	a.y=400;
	startPos.x=a.x;
	startPos.y=a.y;
	currentPos.x=startPos.x;
	currentPos.y=startPos.y;

	currentRect.x1=currentPos.x+width/4;
	currentRect.y1=currentPos.y+height/4;
	currentRect.x2=currentPos.x+width*3/4;
	currentRect.y2=currentPos.y+height*3/4;
	
}
Monster::~Monster()
{
}
void Monster::Render()
{
	monsterAnimation[i%4]->Render(currentPos.x,currentPos.y);
}

void Monster::Init(HGE *hge)
{
	m_hge=hge;
	monsterTex=m_hge->Texture_Load("bin/Textures/Monster1.png");
	i=0;
	for(int i=0; i<4; ++i)
	{
		monsterAnimation[i] = new hgeAnimation(monsterTex, 4, 4,i*width ,0,width, height);
	}
}
hgeRect Monster::getRect()
{
	return currentRect;
}
void Monster::setStartPos(POINT point)
{
	startPos.x=point.x;
	startPos.y=point.y;
}
void Monster::setBoundary(int a,int b,int c)
{
	x1=a;
	x2=b;
	y=c;
}
bool Monster::isHitBound()
{
	if(currentPos.y<=y)
		return true;
	return false;
}
bool Monster::isHit(POINT bulletPoint)
{
	if(getRect().TestPoint(bulletPoint.x,bulletPoint.y))
	{
		blood--;
		return true;
	}	

	return false;
}
bool Monster::isDead()
{
	if(blood<=0)
		return true;
	return false;
}
POINT Monster::GetCurrentPos()
{
	return currentPos;
}
void Monster::setInitPositon(POINT startPosition)
{
	startPos.x=startPosition.x;
	startPos.y=startPosition.y;
	currentPos.x=startPos.x;
	currentPos.y=startPos.y;

	currentRect.x1=currentPos.x+width/4;
	currentRect.y1=currentPos.y+height/4;
	currentRect.x2=currentPos.x+width*3/4 ;
	currentRect.y2=currentPos.y+height*3/4;
}
void Monster::Move()
{
	
	if((startPos.x<=x2)&&(startPos.x>=x1))   
	{
		currentPos.y-=0.1;
	}
	
	else if((startPos.x>x2))
	{
		int dx,dy;
		float k,a;
		dx=x2-startPos.x;
		dy=y-startPos.y;
		k=dy/dx;
		a=y-k*x2;
		currentPos.y-=1;
		currentPos.x=(currentPos.y-a)/k;
	}
	else 
	{
		int dx,dy;
		float k,a;
		dx=x1-startPos.x;
		dy=y-startPos.y;
		k=dy/dx;
		a=y-k*x1;
		currentPos.y-=1;
		currentPos.x=(currentPos.y-a)/k;
	}

	currentRect.x1=currentPos.x+width/4;
	currentRect.y1=currentPos.y+height/4;
	currentRect.x2=currentPos.x+width*3/4;
	currentRect.y2=currentPos.y+height*3/4;
	i++;
}

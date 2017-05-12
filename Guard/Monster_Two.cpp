#include "Monster_Two.h"
Monster_Two::Monster_Two()
{
	id=2;
    height =61;
	width = 70;
    blood=2;
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
Monster_Two::~Monster_Two()
{
}
void Monster_Two::Init(HGE *hge)
{
	m_hge=hge;
	monsterTex=m_hge->Texture_Load("bin/Textures/Monster2.png");
	i=0;
	for(int i=0; i<4; ++i)
	{
		monsterAnimation[i] = new hgeAnimation(monsterTex, 4, 4,i*width ,0,width, height);
	}
}

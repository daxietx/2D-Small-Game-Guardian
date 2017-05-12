#include"Boss.h"
Boss::Boss()
{
	blood=2;
	currentPos.x=400;
	currentPos.y=400;
	d=false;
	b=0;
	c=681;

	height = 200;
	width = 179;

	currentRect.x1=currentPos.x/4;
	currentRect.y1=currentPos.y/4;
	currentRect.x2=currentPos.x+width*0.75;
	currentRect.y2=currentPos.y+height*0.75;
}
Boss::~Boss()
{
}
void Boss::Move()
{
	currentPos.y-=10;
	if(currentPos.y==150)
		currentPos.x=356;
	else
	{
	currentPos.x=rand()%c+b;
	}
	currentRect.x1=currentPos.x+width/4;
	currentRect.y1=currentPos.y+height/4;
	currentRect.x2=currentPos.x+width*0.75;
	currentRect.y2=currentPos.y+height*0.75;
	i++;
	b+=8;
	c-=8;

}
void Boss::Init(HGE *hge)
{
	m_hge=hge;
	monsterTex=m_hge->Texture_Load("bin/Textures/BOSS.png");
	i=0;
	for (int i=0; i<4; ++i)
	{
		monsterAnimation[i] = new hgeAnimation(monsterTex, 4, 4,0 ,0,width, height);
	}
}
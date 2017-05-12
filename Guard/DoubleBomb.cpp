#include "stdafx.h"
#include <string>
#include "DoubleBomb.h"

DoubleBomb::DoubleBomb()
{
	tube1Position.x=460;
	tube1Position.y=120;
	tube2Position.x=476;
	tube2Position.y=120;
	bulletNum = 2;
}

DoubleBomb::~DoubleBomb(void)
{
}

void DoubleBomb::Init(HGE *hge)
{
	bo_hge=hge;
	bombTex1=bo_hge->Texture_Load("bin/Textures/ÅÚÉí.png");
	bombTex2=bo_hge->Texture_Load("bin/Textures/Ë«ÅÚÍ².png");
	if(bombTex1)
		spr1=new hgeSprite(bombTex1,0,0,100,100);
	if(bombTex2)
		spr2=new hgeSprite(bombTex2,0,0,100,100);
		spr2->SetHotSpot(50,50);
		for(int i=0;i<bullets.size();++i)
	{
		bullets[i].Render();
	}
}

void DoubleBomb::Render()
{
	spr1->Render(position.x,position.y);
	spr2->RenderEx(centerPosition.x,centerPosition.y,angle,1);
	for(int i=0;i<bullets.size();++i)
	{
		bullets[i].Render();
	}
}

void DoubleBomb::Launch(float startx,float starty,float endx,float endy)
{
	GetTub1EndPosition();
	GetTub2EndPosition();
	Bullet bullet1(bo_hge,tube1Position.x,tube1Position.y,endx,endy);
	Bullet bullet2(bo_hge,tube2Position.x,tube2Position.y,endx,endy);
	bullet1.Init(bo_hge);
	bullet1.Tick(bo_hge);
	bullet2.Init(bo_hge);
	bullet2.Tick(bo_hge);
	bullets.push_back(bullet1);
	bullets.push_back(bullet2);
}
POINT DoubleBomb::GetTub1EndPosition()
{
	POINT a;
	a.x=tube1Position.x-(sin(angle))*44;
	a.y=tube1Position.y+(cos(angle))*44;
	return a;
}
POINT DoubleBomb::GetTub2EndPosition()
{
	POINT a;
	a.x=tube2Position.x-(sin(angle))*44;
	a.y=tube2Position.y+(cos(angle))*44;
	return a;
}
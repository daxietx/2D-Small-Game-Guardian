#include "stdafx.h"
#include <string>
#include "FireBomb.h"

FireBomb::FireBomb()
{
	bulletNum = 2;
}

FireBomb::~FireBomb(void)
{
}

void FireBomb::Init(HGE *hge)
{
	bo_hge=hge;
	bombTex1=bo_hge->Texture_Load("bin/Textures/Åç»ðÅÚÉí.png");
	bombTex2=bo_hge->Texture_Load("bin/Textures/Åç»ðÅÚÍ².png");
	if(bombTex1)
		spr1=new hgeSprite(bombTex1,0,0,100,100);
	if(bombTex2)
		spr2=new hgeSprite(bombTex2,0,0,100,100);
	spr2->SetHotSpot(50,50);
	fire.Init(hge);
}

void FireBomb::Render()
{
	spr1->Render(position.x,position.y);
	spr2->RenderEx(centerPosition.x,centerPosition.y,angle,1);
	fire.Render();
}

void FireBomb::Launch(float startx,float starty,float endx,float endy)
{
	
	fire.Tick(startx,starty,endx,endy);
}

void FireBomb::Update(float dt)
{
	fire.Update(dt);
}

POINT FireBomb::GetTub1EndPosition()
{
	POINT a;
	a.x=tube1Position.x-(sin(angle))*44;
	a.y=tube1Position.y+(cos(angle))*44;
	return a;
}
POINT FireBomb::GetTub2EndPosition()
{
	POINT a;
	a.x=tube2Position.x-(sin(angle))*44;
	a.y=tube2Position.y+(cos(angle))*44;
	return a;
}
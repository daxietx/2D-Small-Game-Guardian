#include"Bomb.h"
Bomb::Bomb()
{
	position.x=420;
	position.y=70;
	centerPosition.x=470;
	centerPosition.y=120;
	angle=0;
	bombEndPosition.x=470;
	bombEndPosition.y=164;
	bulletNum = 1;
}
Bomb::~Bomb(void)
{
}
void Bomb::Init(HGE *hge)
{
	bo_hge=hge;
	bombTex1=bo_hge->Texture_Load("bin/Textures/ÅÚÉí.png");
	bombTex2=bo_hge->Texture_Load("bin/Textures/ÅÚÍ².png");
	if(bombTex1)
		spr1=new hgeSprite(bombTex1,0,0,100,100);
	if(bombTex2)
		spr2=new hgeSprite(bombTex2,0,0,100,100);
	spr2->SetHotSpot(50,50);
	for(int i=0;i<bullets.size();i++)
		bullets[i].Init(hge);
	slopeIsPositive = true;
}
void Bomb::Render()
{
	spr1->Render(position.x,position.y);
	spr2->RenderEx(centerPosition.x,centerPosition.y,angle, 1);
	
	for(int i=0;i<bullets.size();++i)
	{
		bullets[i].Render();
	}
}
float Bomb::GetDirection()
{
	return direction;
}
void Bomb::SetDirection(float direct)
{
	direction=direct;
}
void Bomb::Rotate(float Angle)
{
	angle=Angle;
}
void Bomb::AngleTrans(POINT mousePos)
{
	float side1=centerPosition.x -mousePos.x;
	float side2=mousePos.y-centerPosition.y;
	angle=atan2(side1,side2);
	bombEndPosition.x=centerPosition.x-(sin(angle))*44;
	bombEndPosition.y=centerPosition.y+(cos(angle))*44;
}

void Bomb::Launch(float startx,float starty,float endx,float endy )
{
	Bullet bullet(bo_hge,startx,starty,endx,endy);
	bullet.Init(bo_hge);
	bullet.Tick(bo_hge);
	bullets.push_back(bullet);
}

void Bomb::Update(float dt)
{
	vector<Bullet >::iterator it=bullets.begin();
	while(it!=bullets.end())
	{
		if(it->currentPos.y>=600)
		{
			bullets.erase(it);
			break;
		}
		it->Move(dt);
		it++;
	}
}
POINT Bomb::GetBombEndPosition()
{
	POINT a;
	a.x=bombEndPosition.x;
	a.y=bombEndPosition.y;
	return a;
}
POINT Bomb::GetTub1EndPosition()
{
	POINT a;
	a.x=tube1Position.x-(sin(angle))*44;
	a.y=tube1Position.y+(cos(angle))*44;
	return a;
}
POINT Bomb::GetTub2EndPosition()
{
	POINT a;
	a.x=tube2Position.x-(sin(angle))*44;
	a.y=tube2Position.y+(cos(angle))*44;
	return a;
}

void Bomb::GetRoute(int startx,int starty,int endx,int endy)
{
	int x,y,dx,dy,e;
	float a,k;
	POINT point;
	dx  = endx - startx;
	dy = endy - starty;
	x = startx;
	y = starty;
	k=dy/dx;
	a=starty-k*startx;
	while(y<endy)
	{	
		POINT b;
		point.x=x;
		point.y=y;
		routePoints.push_back(point);
		y++;
		x=(y-a)/k;
	}
	if(dx>=0)
		slopeIsPositive = false;
	else 
		slopeIsPositive = true;
}

void Bomb::GetJudgePoints()
{
	if(routePoints.size()>0){
		POINT current;
		POINT p; 
		current.x = fire.currentPos.x;
		current.y = fire.currentPos.y;
		if(slopeIsPositive){
			for(int i = 0;i<routePoints.size();i++)
			{
				if((routePoints[i].x>=current.x)&&(routePoints[i].y<=current.y))
				{
					p.x = routePoints[i].x;
					p.y = routePoints[i].y;
					judgePoints.push_back (p);	
				}
			}
			if(routePoints.size()==judgePoints.size())
				routePoints.clear();
		}
		else
		{
			for(int i = 0;i<routePoints.size();i++)
			{
				if((routePoints[i].x<=current.x)&&(routePoints[i].y<=current.y))
				{
					p.x = routePoints[i].x;
					p.y = routePoints[i].y;
					judgePoints.push_back (p);	
				}
			}
			if(routePoints.size()==judgePoints.size())
				routePoints.clear();
		}
	}
}
#include "Bombshell.h"

Bombshell::Bombshell()
{
	width=59;
	height=52;
	//startPos.x = 0;
	//startPos.y = 0;
	currentPos.x = 8;
	currentPos.y = 250;

	killPower=3;

	canRender = false;

	isBomb = false;

	lifeTime = 0.1;

}
Bombshell::~Bombshell()
{

}

void Bombshell::Init(HGE *hge)
{
	m_hge = hge;
	bombTex=m_hge->Texture_Load("bin/Textures/炸弹道具.png");
	if(bombTex)
		spr=new hgeSprite(bombTex,0,0,width,height);
	//booTex=m_hge->Texture_Load("bin/Textures/boo.png");
	//if(booTex)
	//	boo=new hgeSprite(booTex,0,0,115,120);

	boo_psi = "bin/Effects/粒子系统/particle1.psi";
	booTex1 = m_hge->Texture_Load("bin/Effects/粒子系统/particles.png");
	spr1 = new hgeSprite(booTex1,64,64,32,32);
    spr1->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);        //      设置混合模式
    spr1->SetHotSpot(16, 16);    // 设置粒子精灵中心点

}
void Bombshell::Render()
{
	if(!isBomb)
		spr->Render(currentPos.x,currentPos.y);
	else
	{
		canRender = false;
	}
	
	bombRect.x1=currentPos.x;
	bombRect.y1=currentPos.y;
	bombRect.x2=currentPos.x+width;
	bombRect.y2=currentPos.y+height;
}

void  Bombshell::BlastRender()
{
	bomb_particle_effect->Render();
}

void Bombshell::Update(float dt)
{
	bomb_particle_effect->Update(dt);
}


void Bombshell::SetRange()
{
	booRect.x1=currentPos.x-30;
	booRect.y1=currentPos.y-30;
	booRect.x2=currentPos.x+30;
	booRect.y2=currentPos.y+30;
}

bool Bombshell::isPutDown(float x, float y)
{
	if(bombRect.TestPoint(x,y))
	{
		blastPos.x = x;
		blastPos.y = y;
		isBomb=true;
		return true;
	}
	else 
	{
		isBomb=false;
		return false;
	}
}

void Bombshell::PickUp(float x, float y)
{
	currentPos.x = x;
	currentPos.y = y;
}

void Bombshell::Blast()
{
	bomb_particle_effect = new hgeParticleSystem(boo_psi,spr1);
	bomb_particle_effect->MoveTo(blastPos.x,blastPos.y);
	bomb_particle_effect->info.fLifetime = lifeTime;
	bomb_particle_effect->info.fSizeStart = 6;
	bomb_particle_effect->Fire();
}
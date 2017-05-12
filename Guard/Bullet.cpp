#include "stdafx.h"
#include <string>
#include "Bullet.h"
#include "math.h"

Bullet::Bullet()
{
}
Bullet::Bullet(HGE* bu_hge,float startx,float starty,float endx,float endy)
{
	bulletTex = NULL;

	speed = 15;

	startPos.x=startx;
	startPos.y=starty;

	currentPos.x = startx;
	currentPos.y = starty;

	endPos.x = endx;
	endPos.y = endy;

	height = 48;
	width = 32;

	damage = 1;
	lifeTime = 100;
}

Bullet::~Bullet()
{
	//delete bullet_psi;
	//delete bu_spr;
	//bu_hge->Release();
	//delete bu_spr;
	//hge->Texture_Free(bulletTex);
}

void Bullet::Init(HGE *hge)
{
	bu_hge=hge;
	bullet_psi = "bin/Effects/粒子系统/particle7.psi";
	bulletTex = bu_hge->Texture_Load("bin/Effects/粒子系统/particles.png");
    bu_spr = new hgeSprite(bulletTex, 0, 96, 32, 32);  //创建粒子精灵
    bu_spr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);//设置混合模式
    bu_spr->SetHotSpot(16, 16);    // 设置粒子精灵中心点
	
}

void Bullet::Tick(HGE* hge)
{

	bullet_particle_effect = new hgeParticleSystem(bullet_psi,bu_spr);
	bullet_particle_effect->info.fLifetime = lifeTime;
	bullet_particle_effect->info.nEmission = 500;
	bullet_particle_effect->Fire();  //喷火
}

void Bullet::Move(float dt)          
{
	if(endPos.y>=startPos.y){
		float dx,dy;
		float speedx,speedy;
		dx = endPos.x - startPos.x;
		dy = endPos.y - startPos.y;
		speedx = speed * (dx / sqrt(dx*dx+dy*dy));
		speedy = speed * (dy / sqrt(dx*dx+dy*dy));

		currentPos.y += speedy;
		currentPos.x += speedx;

		float side1 = startPos.x - endPos.x;
		float side2 = endPos.y - startPos.y;
		float angle = atan2(side1,side2);
		bullet_particle_effect->info.fDirection = angle;
		bullet_particle_effect->Transpose(currentPos.x,currentPos.y);//移动放射点放射的所有粒子
		bullet_particle_effect->Fire();
		bullet_particle_effect->Update(dt);
	}
}

void Bullet::Render()
{
	bullet_particle_effect->Render();
}
POINT Bullet::GetCurrentPos()
{
	return currentPos;
}

void Bullet::SetStartPos(POINT point)
{
	startPos.x=point.x;
	startPos.y=point.y;
}

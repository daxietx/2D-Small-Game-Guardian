#include "Fire.h"

Fire::Fire()
{
}

void Fire::Init(HGE *hge)
{
	fire_hge = hge;
	fire_psi = "bin/Effects/粒子系统/particle3.psi";
	fireTex = fire_hge->Texture_Load("bin/Effects/粒子系统/particles.png");
    fire_sprite = new hgeSprite(fireTex, 0, 96, 32, 32);  //创建粒子精灵
    fire_sprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);        //      设置混合模式
    fire_sprite->SetHotSpot(16, 16);    // 设置粒子精灵中心点
	lifeTime = 0.3;
}

Fire::~Fire()
{
	delete fire_particle_effect;
	fire_hge->Release();

}

void Fire::Tick(float startx,float starty,float endx,float endy)
{
	startPos.x = startx;
	startPos.y = starty;
	endPos.x = endx;
	endPos.y = endy;
	currentPos.x = startx;
	currentPos.y = starty;
	fire_particle_effect = new hgeParticleSystem(fire_psi,fire_sprite);
	fire_particle_effect->TrackBoundingBox(true);//启动粒子系统的边界框追踪
	fire_particle_effect->info.bRelative = true; //fDirection成员将被看作是与当前粒子系统的移动方向关联
	fire_particle_effect->info.fLifetime = lifeTime;
	fire_particle_effect->info.nEmission = 500;
	fire_particle_effect->MoveTo(startx,starty);  //喷火起始位置 
	fire_particle_effect->Fire();  //喷火

}

void Fire::Render()
{
	fire_particle_effect->Render();
}

void  Fire::Update(float dt)
{
		currentPos.x += ((endPos.x - startPos.x) / lifeTime) * dt; 
		currentPos.y += ((endPos.y - startPos.y) / lifeTime) * dt; 
		fire_particle_effect->MoveTo(currentPos.x,currentPos.y);
		fire_particle_effect->Update(dt);
}

hgeRect*  Fire::GetFireRect()
{
	 fire_particle_effect->GetBoundingBox(fireRect);
	 return fireRect;
}

POINT Fire::GetcurrentPos()
{
	float *x=NULL;
	float *y=NULL;
	POINT p;
	fire_particle_effect->GetPosition(x,y);
	p.x = *x;
	p.y = *y;
	delete x,y;
	return p;
}

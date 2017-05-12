#include "Fire.h"

Fire::Fire()
{
}

void Fire::Init(HGE *hge)
{
	fire_hge = hge;
	fire_psi = "bin/Effects/����ϵͳ/particle3.psi";
	fireTex = fire_hge->Texture_Load("bin/Effects/����ϵͳ/particles.png");
    fire_sprite = new hgeSprite(fireTex, 0, 96, 32, 32);  //�������Ӿ���
    fire_sprite->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);        //      ���û��ģʽ
    fire_sprite->SetHotSpot(16, 16);    // �������Ӿ������ĵ�
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
	fire_particle_effect->TrackBoundingBox(true);//��������ϵͳ�ı߽��׷��
	fire_particle_effect->info.bRelative = true; //fDirection��Ա�����������뵱ǰ����ϵͳ���ƶ��������
	fire_particle_effect->info.fLifetime = lifeTime;
	fire_particle_effect->info.nEmission = 500;
	fire_particle_effect->MoveTo(startx,starty);  //�����ʼλ�� 
	fire_particle_effect->Fire();  //���

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

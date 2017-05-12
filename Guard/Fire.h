#pragma once
#include "hge.h"
#include "hgeparticle.h"
#include "hgesprite.h"
#include <Math.h>
#include <vector>
using namespace std;

class Fire
{
public:
	Fire();
	~Fire();
	void Init(HGE *hge);
	void Tick(float startx,float starty,float endx,float endy);
	void Render();
	void Update(float dt);
	hgeRect* GetFireRect();
	POINT GetcurrentPos();

	HGE* fire_hge;
	HTEXTURE  fireTex;
	hgeParticleSystem* fire_particle_effect;
	hgeSprite* fire_sprite;
	const char* fire_psi;
	hgeParticleSystemInfo *psi;

	POINT startPos;
	POINT currentPos;
	POINT endPos;
	float lifeTime;
	hgeRect* fireRect;
};
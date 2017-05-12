#include "stdafx.h"
#include <string>
#include "hge.h"
#include "hgeparticle.h"
#include "hgesprite.h"
using namespace std;

class Bullet
{
public:
	Bullet();
	Bullet(HGE* hge,float startx,float starty,float endx,float endy);
	~Bullet(void);
	
	void Init(HGE* hge);
	void Render();
	void Move(float dt);
	void SetStartPos(POINT point);
	
	void Tick(HGE* hge);

public:
	HGE* bu_hge;
	hgeSprite *bu_spr;
	HTEXTURE bulletTex;       //子弹图片纹理
	hgeParticleSystem* bullet_particle_effect;
	const char* bullet_psi;

	POINT startPos;          //子弹产生初始位置
	POINT currentPos;       //子弹当前所在位置
	POINT endPos;           //子弹消失的位置

	float lifeTime;         //粒子存活时间
	int damage;             //单发子弹的伤害值
	float speed;

	float height;
	float width;

	POINT GetCurrentPos();
};
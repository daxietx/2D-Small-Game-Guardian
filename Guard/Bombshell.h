#include "stdafx.h"
#include "hge.h"
#include "hgeparticle.h"
#include "hgesprite.h"
class Bombshell
{
public:
	Bombshell();
	~Bombshell();

	HGE *m_hge;
	hgeSprite *spr;
	//hgeSprite *boo;//爆炸效果
	HTEXTURE bombTex;
	//HTEXTURE booTex;//爆炸效果的贴图

	hgeSprite *spr1;
	HTEXTURE booTex1;
	const char* boo_psi;
	hgeParticleSystem* bomb_particle_effect;

	//POINT startPos;
	POINT currentPos;
	POINT blastPos;
	//POINT endPos;

	//炸弹图片的宽高
	float width;
	float height;
	//炸弹图片的矩形
	hgeRect bombRect;

	//爆炸效果的宽高
	float booWidth;
	float booHeight;
	hgeRect booRect;

	//炸弹的状态
	bool canRender; //可以渲染
	bool isBomb; //爆炸
	int killPower;

	float lifeTime;  //粒子存活时间

public:
	void Init(HGE *hge);
	void Render();

	void BlastRender();//渲染爆炸效果
	void Update(float dt);
	void Blast();//爆炸

	void SetRange();//根据当前位置设定炸弹范围

	void PickUp(float x,float y); //炸弹被拾取
	bool isPutDown(float x, float y); //炸弹被放下
};
	


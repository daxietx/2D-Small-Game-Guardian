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
	HTEXTURE bulletTex;       //�ӵ�ͼƬ����
	hgeParticleSystem* bullet_particle_effect;
	const char* bullet_psi;

	POINT startPos;          //�ӵ�������ʼλ��
	POINT currentPos;       //�ӵ���ǰ����λ��
	POINT endPos;           //�ӵ���ʧ��λ��

	float lifeTime;         //���Ӵ��ʱ��
	int damage;             //�����ӵ����˺�ֵ
	float speed;

	float height;
	float width;

	POINT GetCurrentPos();
};
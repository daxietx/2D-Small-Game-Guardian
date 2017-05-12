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
	//hgeSprite *boo;//��ըЧ��
	HTEXTURE bombTex;
	//HTEXTURE booTex;//��ըЧ������ͼ

	hgeSprite *spr1;
	HTEXTURE booTex1;
	const char* boo_psi;
	hgeParticleSystem* bomb_particle_effect;

	//POINT startPos;
	POINT currentPos;
	POINT blastPos;
	//POINT endPos;

	//ը��ͼƬ�Ŀ��
	float width;
	float height;
	//ը��ͼƬ�ľ���
	hgeRect bombRect;

	//��ըЧ���Ŀ��
	float booWidth;
	float booHeight;
	hgeRect booRect;

	//ը����״̬
	bool canRender; //������Ⱦ
	bool isBomb; //��ը
	int killPower;

	float lifeTime;  //���Ӵ��ʱ��

public:
	void Init(HGE *hge);
	void Render();

	void BlastRender();//��Ⱦ��ըЧ��
	void Update(float dt);
	void Blast();//��ը

	void SetRange();//���ݵ�ǰλ���趨ը����Χ

	void PickUp(float x,float y); //ը����ʰȡ
	bool isPutDown(float x, float y); //ը��������
};
	


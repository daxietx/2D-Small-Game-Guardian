#include "stdafx.h"
#include <string>
#include <vector>
using namespace std;

class Monster
{
public:
	Monster();
	~Monster(void);
	virtual void Init(HGE *hge);
	void Move();
	void Render();
	void setStartPos(POINT point);
	hgeRect getRect();
	POINT GetCurrentPos();
	void setBoundary(int a,int b,int c);
	bool isHitBound();
	bool isHit(POINT bulletPoint);
	bool isDead();
	void setInitPositon(POINT startPositon);
public:
	HGE* m_hge;
	hgeAnimation  *monsterAnimation[4];
	HTEXTURE monsterTex;
	POINT startPos;
	POINT currentPos;
	POINT endPos;
	hgeRect currentRect;
	float height;
	float width;
	double x1,x2,y;
	int i;
	int blood;
	int id;
};
#include "stdafx.h"
#include <string>
#include "Bullet.h"
#include "Fire.h"
#include <vector>
using namespace std;

class Bomb
{
public:
	Bomb();
	~Bomb(void);

	virtual void Render();
	virtual void Init(HGE *hge);
	float GetDirection();
	void SetDirection(float direct);
	void Rotate(float angle);
	void AngleTrans(POINT mousePos);
	virtual void Launch(float startx,float starty,float endx,float endy);
	virtual void Update(float dt);
	
	POINT GetBombEndPosition();
	virtual POINT GetTub1EndPosition();
	virtual POINT GetTub2EndPosition();

	virtual void GetRoute(int startx,int starty,int endx,int endy);       //得到炮火路径上所有的点
	virtual void GetJudgePoints();                                        //得到当前炮火路径 


	int bombID;
	HGE* bo_hge;
	HTEXTURE bombTex1;
	HTEXTURE bombTex2;
	hgeSprite *spr1;
	hgeSprite *spr2;
	float direction;
	POINT position;
	POINT bombEndPosition;
	POINT bombEndPosition2;
	POINT tube1Position;
	POINT tube2Position;
	double angle;
	int price;
	POINT centerPosition;

	vector<Bullet> bullets;
	int bulletNum;             //一次发射子弹数量

	Fire fire;
	bool slopeIsPositive;     //判断喷火路径的斜率是否为正
	float sideLength;         //小方框边长的一半
	vector <POINT> routePoints;
	vector <POINT> judgePoints;
};
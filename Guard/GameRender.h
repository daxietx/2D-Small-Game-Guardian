#include "stdafx.h"
#include"Monster_Four.h"
#include "FireBomb.h"
#include "Castle.h"
#include "Bombshell.h"
#include "list"
#include <vector>
using namespace std;

class CGameSetting;
class CMusicPlay;

class GameRender
{
public:
	GameRender(void);
	~GameRender();
	static GameRender* GetInstance();
	void Init(HGE * hge);
	bool FrameFunc();
	void RenderFunc();
	GAME_STATE GetState();	
	void Start();

	void UpdateMonster();
	void UpdateBoss();
	void AddMonster();
	void IsAutoCreatMonster();
	void UpdateState(); 
	void UpdateBombshell(float dt);
	void UpdateMonNum();
	void MonsterMove();
	void UpdateSecondState();

	void StartItemEffect(float x,float y);
	void UpdateItemEffect(float dt);
	void RenderItemEffect();

	HGE * m_hge;
	static GameRender *m_pGameRender;
	HTEXTURE bg_Tex;        //背景纹理
	hgeSprite * bg_Spr;      //背景的精灵

	hgeSprite *cursor;  //鼠标精灵
	HTEXTURE cursorTex; //鼠标纹理
	hgeGUI   *cursorGui;
	int guiId;
	POINT p;            //接受鼠标点击
	bool mouseClicked; //判断鼠标是否点击

	Castle castle;

	hgeSprite *itemSpr;    //道具特效的精灵
	HTEXTURE itemEffectTex;
	hgeParticleSystem* item_particle_effect;
	const char* item_psi;
	bool itemClicked;

	vector<Monster > monster;   //存储怪物
	vector<Boss > bosses;
	bool monsterIsDisappear;
	int totalMonsterNum;
	int monsterCreatNum;
	int monsterDeadNum;
	GAME_STATE gameState;
	CGameSetting       *m_pGameSetting;  //游戏设置类指针
	CMusicPlay         *m_pMusicPlay;    //音乐播放类指针

	float oldTime;
	float currentTime;
	float lastTime;
	float currentTime1;
	float startTime2;         //判断爆炸应该爆多久
	float currentTime2;

	vector<Bomb *> bombs;      //存储所有炮
	int weaponID;              //炮ID
	int doubleBombPrice;       //双管炮价格
	int firePrice;             //喷火器价格

	int bombshellPrice;        //炸弹道具价格
	int chengFangPrice;        //城防道具价格
	int FrameNum;




	//道具的纹理，精灵 道具所在的矩形
	HTEXTURE chengFangTex;
	HTEXTURE  bombshellTex;
	HTEXTURE fireTex;
	HTEXTURE doubleBombTex;
	hgeSprite *chengFangspr;
	hgeSprite *bombshellspr;
	hgeSprite *firespr;
	hgeSprite *doubleBombspr;
	hgeRect chengFangRect;
	hgeRect bombshellRect;
	hgeRect fireRect;
	hgeRect doubleBombRect;

	//金钱的纹理，精灵
	HTEXTURE moneyTex;
	hgeSprite * moneySpr[10];

	//血条的纹理，精灵
	HTEXTURE bloodTex;
	hgeSprite * bloodSpr[6];

	int moneyNum;        //金钱数

	vector<Bombshell> bombshells;

	//鼠标浮动的位置
	float mouse_x;
	float mouse_y;
	bool hasBomb;//容器中有炸弹

	bool fireAbleRender;     //粒子可以渲染
	bool isDeadBoss;
};

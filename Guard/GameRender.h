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
	HTEXTURE bg_Tex;        //��������
	hgeSprite * bg_Spr;      //�����ľ���

	hgeSprite *cursor;  //��꾫��
	HTEXTURE cursorTex; //�������
	hgeGUI   *cursorGui;
	int guiId;
	POINT p;            //���������
	bool mouseClicked; //�ж�����Ƿ���

	Castle castle;

	hgeSprite *itemSpr;    //������Ч�ľ���
	HTEXTURE itemEffectTex;
	hgeParticleSystem* item_particle_effect;
	const char* item_psi;
	bool itemClicked;

	vector<Monster > monster;   //�洢����
	vector<Boss > bosses;
	bool monsterIsDisappear;
	int totalMonsterNum;
	int monsterCreatNum;
	int monsterDeadNum;
	GAME_STATE gameState;
	CGameSetting       *m_pGameSetting;  //��Ϸ������ָ��
	CMusicPlay         *m_pMusicPlay;    //���ֲ�����ָ��

	float oldTime;
	float currentTime;
	float lastTime;
	float currentTime1;
	float startTime2;         //�жϱ�ըӦ�ñ����
	float currentTime2;

	vector<Bomb *> bombs;      //�洢������
	int weaponID;              //��ID
	int doubleBombPrice;       //˫���ڼ۸�
	int firePrice;             //������۸�

	int bombshellPrice;        //ը�����߼۸�
	int chengFangPrice;        //�Ƿ����߼۸�
	int FrameNum;




	//���ߵ��������� �������ڵľ���
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

	//��Ǯ����������
	HTEXTURE moneyTex;
	hgeSprite * moneySpr[10];

	//Ѫ������������
	HTEXTURE bloodTex;
	hgeSprite * bloodSpr[6];

	int moneyNum;        //��Ǯ��

	vector<Bombshell> bombshells;

	//��긡����λ��
	float mouse_x;
	float mouse_y;
	bool hasBomb;//��������ը��

	bool fireAbleRender;     //���ӿ�����Ⱦ
	bool isDeadBoss;
};

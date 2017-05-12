//游戏控制类，控制游戏界面的输入与输出
#pragma once
#include "stdafx.h"
#include <vector>
#include "FlashSprite.h"
#include"GameRender.h"
using namespace std;

class CGameSetting;
class CMusicPlay;

class CGameManager
{
public:
	~CGameManager(void);
	static CGameManager* GetInstance();
	void Init(HGE * hge);
	bool FrameFunc();
	void RenderFunc();
	string GetInputStr();
	//动画
	FlashSprite* pFlashSprite;
	FlashSprite* pFlashSprite1;
	FlashSprite* pFlashSprite2;
	FlashSprite* pFlashSprite3;

private:
	CGameManager(void);
	static CGameManager *m_pGameManager;
	HGE * m_hge;
	GameRender pGameRender;
	vector<HTEXTURE>   m_bgTex;       //存放背景图片
	vector<hgeGUI*>    m_gui;         //存放界面控件
	vector<HTEXTURE>   m_tex;         //存放纹理
	hgeSprite          *m_pBgSpr;     //背景精灵
	hgeSprite		   *m_pCursorSpr; //鼠标精灵  

	HTEXTURE           m_EffectTex;        //存放音效的纹理
	hgeSprite          *m_pEffectSpr[7];   //存放音效的精灵

	int                m_nGuiID;      //界面ID
	CGameSetting       *m_pGameSetting;  //游戏设置类指针
	CMusicPlay         *m_pMusicPlay;    //音乐播放类指针
};


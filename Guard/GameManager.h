//��Ϸ�����࣬������Ϸ��������������
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
	//����
	FlashSprite* pFlashSprite;
	FlashSprite* pFlashSprite1;
	FlashSprite* pFlashSprite2;
	FlashSprite* pFlashSprite3;

private:
	CGameManager(void);
	static CGameManager *m_pGameManager;
	HGE * m_hge;
	GameRender pGameRender;
	vector<HTEXTURE>   m_bgTex;       //��ű���ͼƬ
	vector<hgeGUI*>    m_gui;         //��Ž���ؼ�
	vector<HTEXTURE>   m_tex;         //�������
	hgeSprite          *m_pBgSpr;     //��������
	hgeSprite		   *m_pCursorSpr; //��꾫��  

	HTEXTURE           m_EffectTex;        //�����Ч������
	hgeSprite          *m_pEffectSpr[7];   //�����Ч�ľ���

	int                m_nGuiID;      //����ID
	CGameSetting       *m_pGameSetting;  //��Ϸ������ָ��
	CMusicPlay         *m_pMusicPlay;    //���ֲ�����ָ��
};


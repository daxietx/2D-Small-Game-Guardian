#include "StdAfx.h"
#include "MapManager.h"
#include "MusicPlay.h"

CMapManager* CMapManager::m_pMapManager = NULL;

CMapManager* CMapManager::GetInstance(HGE * hge)
{
	if (m_pMapManager==NULL)
	{
		m_pMapManager = new CMapManager(hge);
	}
	return m_pMapManager;
}


CMapManager::CMapManager(HGE *hge)
	:m_pHge(hge)//,m_pPlayer(NULL), m_pTool(NULL), m_pWeapons(NULL)
{
	m_pHge = hge;
	m_nMapId = 0;
	m_MapInfo.resize(0);
	m_mapTex = NULL;         //��ͼ����
	m_mapSprite = NULL;      //��ͼ����

	
	//��������
	m_font = new hgeFont("bin/Fonts/font1.fnt");
	//����ͼ����
	MapInfo mapInfo;

	//�ػ�ģʽ��ͼ
	mapInfo.mapName = "bin/Textures/��Ϸ����/����.png";

	m_MapInfo.push_back(mapInfo);
}


CMapManager::~CMapManager(void)
{
	m_pHge->Texture_Free(m_mapTex);
	delete m_font;
	delete m_mapSprite;

}


void CMapManager::Start()  //��Ϸ��ʼ
{
	/*pGameRender.Start();*/
	//m_state =pGameRender.GetState();  //������Ϸ״̬
	/*pGameRender.Init(m_pHge);*/
	InitMap();

}

//֡����
//���Ƶ��˵Ĳ������ƶ�
//���Ƶ��ߵĲ���
//��������
//����״̬
void CMapManager::FrameFunc(float dt) 
{
	/*pGameRender.FrameFunc();*/

}


void CMapManager::RenderFunc() //���ƺ���
{
	//���Ƶ�ͼ
	/*m_mapSprite->Render(0, 0);*/
	/*pGameRender.RenderFunc();*/

}



void CMapManager::InitMap()
{
	switch(m_ModeName)  //ȷ����ͼ���
	{
	case DEFEND:
		m_nMapId = m_nLevel - 1;
		break;
	default:
		break;
	}
	//���ص�ͼ����
	if (m_mapTex!=NULL)
	{
		m_pHge->Texture_Free(m_mapTex);
		m_mapTex = NULL;
	}
	if (m_mapSprite!=NULL)
	{
		delete m_mapSprite;
		m_mapSprite = NULL;
	}
	m_mapTex = m_pHge->Texture_Load(m_MapInfo[m_nMapId].mapName.c_str());
	m_mapSprite = new hgeSprite(m_mapTex, 0, 0, 850, 600);
	
}




//GAME_STATE CMapManager::GetState()
//{
//	//�������Ƿ����
//	return pGameRender.GetState();
//}





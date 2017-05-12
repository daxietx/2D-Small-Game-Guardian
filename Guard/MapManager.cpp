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
	m_mapTex = NULL;         //地图纹理
	m_mapSprite = NULL;      //地图精灵

	
	//加载字体
	m_font = new hgeFont("bin/Fonts/font1.fnt");
	//填充地图数据
	MapInfo mapInfo;

	//守护模式地图
	mapInfo.mapName = "bin/Textures/游戏场景/场景.png";

	m_MapInfo.push_back(mapInfo);
}


CMapManager::~CMapManager(void)
{
	m_pHge->Texture_Free(m_mapTex);
	delete m_font;
	delete m_mapSprite;

}


void CMapManager::Start()  //游戏开始
{
	/*pGameRender.Start();*/
	//m_state =pGameRender.GetState();  //设置游戏状态
	/*pGameRender.Init(m_pHge);*/
	InitMap();

}

//帧函数
//控制敌人的产生、移动
//控制道具的产生
//控制武器
//更新状态
void CMapManager::FrameFunc(float dt) 
{
	/*pGameRender.FrameFunc();*/

}


void CMapManager::RenderFunc() //绘制函数
{
	//绘制地图
	/*m_mapSprite->Render(0, 0);*/
	/*pGameRender.RenderFunc();*/

}



void CMapManager::InitMap()
{
	switch(m_ModeName)  //确定地图编号
	{
	case DEFEND:
		m_nMapId = m_nLevel - 1;
		break;
	default:
		break;
	}
	//加载地图纹理
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
//	//检测基地是否存在
//	return pGameRender.GetState();
//}





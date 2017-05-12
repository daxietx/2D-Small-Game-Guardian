#include "stdafx.h"
#include "GameSetting.h"

CGameSetting* CGameSetting::m_pGameSetting=NULL;

CGameSetting* CGameSetting::GetInstance(HGE * hge)
{
	if (m_pGameSetting == NULL)
	{
		m_pGameSetting=new CGameSetting(hge);
	}
	return m_pGameSetting;
}
CGameSetting::CGameSetting(HGE* hge)
{
	m_hge=hge;
	Read();
}

void CGameSetting::Read()
{
	m_hge->System_SetState(HGE_INIFILE, "INI/GameSetting.ini");//设置系统状态
	m_Sound  = m_hge->Ini_GetInt("GameSetting", "SOUND", 0);
	m_Volume1 = m_hge->Ini_GetInt("GameSetting", "VOLUME1", 50);
	m_Volume2 = m_hge->Ini_GetInt("GameSetting", "VOLUME2", 50);
	Write();//用于初始化ini文件
}

void CGameSetting::Write()
{
	m_hge->System_SetState(HGE_INIFILE, "INI/GameSetting.ini");//设置系统状态
	if (m_Sound)
	{
		m_hge->Ini_SetInt("GameSetting","SOUND",1);
	}
	else
	{
		m_hge->Ini_SetInt("GameSetting","SOUND",0);
	}
	m_hge->Ini_SetInt("GameSetting","VOLUME1",m_Volume1);
	m_hge->Ini_SetInt("GameSetting","VOLUME2",m_Volume2);
}
void CGameSetting::Set_SOUND()
{
	if (m_Sound)
	{
		m_Sound=false;
	}
	else
		m_Sound=true;
}

void CGameSetting::Set_VOLUME1(int volume)
{
	m_Volume1=volume;
}

void CGameSetting::Set_VOLUME2(int volume)
{
	m_Volume2=volume;
}

bool CGameSetting::Get_SOUND()
{
	return m_Sound;
}
int CGameSetting::Get_VOLUME1()
{
	return m_Volume1;
}

int CGameSetting::Get_VOLUME2()
{
	return m_Volume2;
}
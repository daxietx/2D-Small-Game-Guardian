#pragma once
#include <string>
#include "Stdafx.h"
using namespace std;

class CGameSetting
{
public:
	static CGameSetting * GetInstance(HGE * hge);
	void Read(); //从ini文件中读取游戏设置信息
	void Write();//向ini文件中写入游戏设置信息
	void Set_SOUND();
	void Set_VOLUME1(int volume);  //菜单音量
	void Set_VOLUME2(int volume);  //音效音量
	bool Get_SOUND();
	int Get_VOLUME1();  //菜单音量
	int Get_VOLUME2();  //音效音量
private:
	CGameSetting(HGE * hge);
	static CGameSetting* m_pGameSetting;

	HGE * m_hge;
	bool m_Sound;
	int m_Volume1;  //菜单音量
	int m_Volume2;  //音效音量
};
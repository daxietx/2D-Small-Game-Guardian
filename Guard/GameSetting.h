#pragma once
#include <string>
#include "Stdafx.h"
using namespace std;

class CGameSetting
{
public:
	static CGameSetting * GetInstance(HGE * hge);
	void Read(); //��ini�ļ��ж�ȡ��Ϸ������Ϣ
	void Write();//��ini�ļ���д����Ϸ������Ϣ
	void Set_SOUND();
	void Set_VOLUME1(int volume);  //�˵�����
	void Set_VOLUME2(int volume);  //��Ч����
	bool Get_SOUND();
	int Get_VOLUME1();  //�˵�����
	int Get_VOLUME2();  //��Ч����
private:
	CGameSetting(HGE * hge);
	static CGameSetting* m_pGameSetting;

	HGE * m_hge;
	bool m_Sound;
	int m_Volume1;  //�˵�����
	int m_Volume2;  //��Ч����
};
#include "stdafx.h"
#include "MusicPlay.h"
#include "GameSetting.h"

CMusicPlay* CMusicPlay::m_pMusicPlay = NULL;

CMusicPlay* CMusicPlay::GetInstance(HGE * hge)
{
	if (m_pMusicPlay==NULL)
	{
		m_pMusicPlay = new CMusicPlay(hge);
	}
	return m_pMusicPlay;
}

CMusicPlay::CMusicPlay(HGE * hge)
{
	m_pHge = hge;
	m_effects.resize(0);
	//���ظ���������Դ
	m_effects.push_back(hge->Effect_Load("bin/Effects/MouseClick.mp3"));  //�����������Ч
	m_effects.push_back(hge->Effect_Load("bin/Effects/MainMenu.mp3"));   //������������Ч
	m_effects.push_back(hge->Effect_Load("bin/Effects/Fighting1.mp3"));        //������Ϸʱ����Ч
	m_effects.push_back(hge->Effect_Load("bin/Effects/Victory1.WAV"));    //��һ��ʤ��ʱ����Ч
	m_effects.push_back(hge->Effect_Load("bin/Effects/Victory2.WAV"));    //�ڶ���ʤ��ʱ����Ч
	m_effects.push_back(hge->Effect_Load("bin/Effects/���ų���.WAV"));    //BOSSս��Ч
	m_effects.push_back(hge->Effect_Load("bin/Effects/����ʤ��.WAV"));    //ʧ����Ч
	m_effects.push_back(hge->Effect_Load("bin/Effects/Bombshell.mp3"));    //ը����ը����
    m_effects.push_back(hge->Effect_Load("bin/Effects/BOSSDead.mp3"));   //BOSS����������
	m_effects.push_back(hge->Effect_Load("bin/Effects/BOSSHit.mp3"));   //BOSS�����е�����
	m_effects.push_back(hge->Effect_Load("bin/Effects/DoubleBomb.mp3"));   //˫Ͳ�ڷ���������
	m_effects.push_back(hge->Effect_Load("bin/Effects/Fire.WAV"));   //����ڷ���������
	m_effects.push_back(hge->Effect_Load("bin/Effects/heal.mp3"));   //�Ƿ����߱����������
	m_effects.push_back(hge->Effect_Load("bin/Effects/HitWallLaugh.mp3"));//С��ײ����ǽ������
	m_effects.push_back(hge->Effect_Load("bin/Effects/MonsterDead.mp3"));  
	m_effects.push_back(hge->Effect_Load("bin/Effects/SingleBomb.mp3"));
	m_effects.push_back(hge->Effect_Load("bin/Effects/Switch.mp3"));
}//


CMusicPlay::~CMusicPlay(void)
{
	//�ͷ����е�������Դ
	for (int i=0; i<m_effects.size(); ++i)
	{
		m_pHge->Effect_Free(m_effects[i]);
	}
}

void CMusicPlay::Play(MUSIC_TYPE type)
{   
	//��ʼ������
	for (int i=0; i<m_effects.size(); ++i)
	{
		l_effects.push_back(m_effects[type]);
	}

	if (!CGameSetting::GetInstance(m_pHge)->Get_SOUND()
		&&(CGameSetting::GetInstance(m_pHge)->Get_VOLUME1()>0
		||CGameSetting::GetInstance(m_pHge)->Get_VOLUME2()>0))  //��ȡ�Ƿ���
	{
		if((type == btn_click)||(type == Bombshell1)||(type == BOSSDead1)||(type == BOSSHit1)||(type == DoubleBomb1)
			||(type == Fire1)||(type == heal1)||(type == HitWallLaugh1)||(type == MonsterDead1)
			||(type == SingleBomb1)||(type == Switch1))
		{
			l_effects[type] = m_pHge->Effect_PlayEx(m_effects[type], 
				CGameSetting::GetInstance(m_pHge)->Get_VOLUME2(), 0, 1.0f, false);//�����������Ч
		}
		else
		{
			l_effects[type] = m_pHge->Effect_PlayEx(m_effects[type], 
				CGameSetting::GetInstance(m_pHge)->Get_VOLUME1(), 0, 1.0f, false);//����������Ч
		}
	}
}

void CMusicPlay::Stop(MUSIC_TYPE type)
{
	m_pHge->Channel_Stop(l_effects[type]);  //ֹͣ����
}

void CMusicPlay::Pause(MUSIC_TYPE type)
{
	m_pHge->Channel_Pause(l_effects[type]);  //��ͣ����
}

void CMusicPlay::Resume(MUSIC_TYPE type)
{
	m_pHge->Channel_Resume(l_effects[type]);  //�ָ�����
}

void CMusicPlay::Set_VolumePlus(MUSIC_TYPE type)   
{
	int volume_plus;
	if ((type == btn_click)||(type == Bombshell1)||(type == BOSSDead1)||(type == BOSSHit1)||(type == DoubleBomb1)
			||(type == Fire1)||(type == heal1)||(type == HitWallLaugh1)||(type == MonsterDead1)
			||(type == SingleBomb1)||(type == Switch1))
	{
		volume_plus = CGameSetting::GetInstance(m_pHge)->Get_VOLUME2();
		if (volume_plus < 100)
		{
			volume_plus = volume_plus + 10;
	        m_pHge->Channel_SetVolume(l_effects[type], volume_plus);
		}
		CGameSetting::GetInstance(m_pHge)->Set_VOLUME2(volume_plus);   
	}
	else
	{
		volume_plus = CGameSetting::GetInstance(m_pHge)->Get_VOLUME1();
		if (volume_plus < 100)
		{
			volume_plus = volume_plus + 10;
			m_pHge->Channel_SetVolume(l_effects[type], volume_plus);
		}
		CGameSetting::GetInstance(m_pHge)->Set_VOLUME1(volume_plus);   
	}
}

void CMusicPlay::Set_VolumeReduce(MUSIC_TYPE type)   
{
	int volume_reduce;
	if (type == btn_click)
	{
		volume_reduce = CGameSetting::GetInstance(m_pHge)->Get_VOLUME2();
		if (volume_reduce > 0)
		{
			volume_reduce = volume_reduce - 10;
	        m_pHge->Channel_SetVolume(l_effects[type], volume_reduce);
		}
		CGameSetting::GetInstance(m_pHge)->Set_VOLUME2(volume_reduce);   
	}
	else
	{
		volume_reduce = CGameSetting::GetInstance(m_pHge)->Get_VOLUME1();
		if (volume_reduce > 0)
		{
			volume_reduce = volume_reduce - 10;
			m_pHge->Channel_SetVolume(l_effects[type], volume_reduce);
		}
		CGameSetting::GetInstance(m_pHge)->Set_VOLUME1(volume_reduce);  
	}
}
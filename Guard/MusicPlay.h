#pragma once
#include "Stdafx.h"
#include <vector>
using namespace std;

class CMusicPlay
{
public:
	~CMusicPlay(void);

	static CMusicPlay* GetInstance(HGE * hge);
	void Play(MUSIC_TYPE type);               //��������
	void Pause(MUSIC_TYPE type);              //������ͣ
	void Stop(MUSIC_TYPE type);               //����ֹͣ���������ͷ���Դ
	void Resume(MUSIC_TYPE type);             //���ָֻ����ָ���ͣ����
	void Set_VolumePlus(MUSIC_TYPE type);     //������������
	void Set_VolumeReduce(MUSIC_TYPE type);   //�������ּ�С
private:
	CMusicPlay(HGE * hge);
	static CMusicPlay *m_pMusicPlay;

	HGE *m_pHge;
	vector<HEFFECT>   m_effects; //��Ÿ�����Ч
	vector<HCHANNEL>  l_effects; //��Ÿ�����Ч������
};
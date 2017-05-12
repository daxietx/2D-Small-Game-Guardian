#pragma once
#include "Stdafx.h"
#include <vector>
using namespace std;

class CMusicPlay
{
public:
	~CMusicPlay(void);

	static CMusicPlay* GetInstance(HGE * hge);
	void Play(MUSIC_TYPE type);               //播放音乐
	void Pause(MUSIC_TYPE type);              //音乐暂停
	void Stop(MUSIC_TYPE type);               //音乐停止，这样会释放资源
	void Resume(MUSIC_TYPE type);             //音乐恢复，恢复暂停音乐
	void Set_VolumePlus(MUSIC_TYPE type);     //控制音乐增大
	void Set_VolumeReduce(MUSIC_TYPE type);   //控制音乐减小
private:
	CMusicPlay(HGE * hge);
	static CMusicPlay *m_pMusicPlay;

	HGE *m_pHge;
	vector<HEFFECT>   m_effects; //存放各种音效
	vector<HCHANNEL>  l_effects; //存放各种音效的音轨
};
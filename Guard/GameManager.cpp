#include "stdafx.h"
#include "GameManager.h"
#include "GameSetting.h"
#include "MusicPlay.h"

CGameManager* CGameManager::m_pGameManager = NULL;

CGameManager* CGameManager::GetInstance()
{
	if (m_pGameManager==NULL)
	{
		m_pGameManager = new CGameManager();
	}
	return m_pGameManager;
}

CGameManager::CGameManager(void)
{
	m_bgTex.resize(0);
	m_gui.resize(0);
	m_tex.resize(0);

	m_pEffectSpr[7] = NULL;  //音效的精灵指针

	m_pBgSpr = NULL;    //背景精灵指针
	m_pCursorSpr = NULL;//鼠标精灵指针
	m_pGameSetting = NULL;//游戏控制类指针
	m_pMusicPlay = NULL;  //音乐控制类指针
	//flash精灵
	pFlashSprite=NULL;

}

CGameManager::~CGameManager(void)
{
	//释放背景图片纹理
	for (int i=0; i<m_bgTex.size(); ++i)
	{
		m_hge->Texture_Free(m_bgTex[i]);
	}

	//释放其它纹理
	for (int i=0; i<m_tex.size(); ++i)
	{
		m_hge->Texture_Free(m_tex[i]);
	}

	//删除控件容器类指针
	for (int i=0; i<m_gui.size(); ++i)
	{
		delete m_gui[i];
	}

	//删除音效的纹理
	m_hge->Texture_Free(m_EffectTex);

	delete m_pBgSpr;    //删除背景精灵指针
	m_pBgSpr = NULL;
	delete m_pCursorSpr;//删除鼠标精灵指针
	m_pCursorSpr = NULL;
	delete m_pGameSetting;//删除游戏控制类指针
	m_pGameSetting = NULL;
	delete m_pMusicPlay;  //删除音乐控制类指针
	m_pMusicPlay = NULL;
	delete pFlashSprite;//删除flash类指针
	pFlashSprite=NULL;
}

void CGameManager::Init(HGE * hge)//加载所有的资源
{

	m_hge = hge;

	//获取其它类的实例对象
	m_pGameSetting = CGameSetting::GetInstance(hge);//游戏设置类指针
	m_pMusicPlay = CMusicPlay::GetInstance(hge);    //音乐控制类指针

	hgeGUI   *gui;
	HTEXTURE tex;
	//载入鼠标纹理和创建鼠标精灵
	tex = hge->Texture_Load("bin/Textures/cursor.png");
	m_tex.push_back(tex);
	m_pCursorSpr = new hgeSprite(tex,0,0,28,31);

	/************************界面0***************************************/
	//flash播放界面
	tex = hge->Texture_Load("bin/Textures/游戏界面/Begin.png "); 
	m_bgTex.push_back(tex);
	gui = new hgeGUI();      
	tex = hge->Texture_Load("bin/Textures/游戏界面/play.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 17, 464, 152, 100, tex, 0, 0));
	//Setting
	tex = hge->Texture_Load("bin/Textures/游戏界面/setting.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 761, 21, 72, 65, tex, 0, 0));


	pFlashSprite = new FlashSprite;
	//// 加载flash文件
	pFlashSprite->StartFlash("open.swf",850,600);
	pFlashSprite->SetLoopPlay(false);
	m_gui.push_back(gui);
//////////////////////////////////////////////////////////////////////////////////////
	
	pFlashSprite1 = new FlashSprite;
	//// 加载flash文件结束
	pFlashSprite1->StartFlash("ceshijieshu.swf",850,600);
	pFlashSprite1->SetLoopPlay(false);
	pFlashSprite1->Pause();


    pFlashSprite2 = new FlashSprite;
	//// 加载flash文件
	pFlashSprite2->StartFlash("1.swf",850,600);
	pFlashSprite2->SetLoopPlay(false);
	pFlashSprite2->Pause();

    pFlashSprite3 = new FlashSprite;
	//// 加载flash文件
	pFlashSprite3->StartFlash("2.swf",850,600);
	pFlashSprite3->SetLoopPlay(false);
	pFlashSprite3->Pause();






    /************************界面1***************************************/
	//主菜单界面
	//载入背景图片
	tex = hge->Texture_Load("bin/Textures/游戏界面/Begin.png"); 
	m_bgTex.push_back(tex);
	//加载按钮控件
	gui = new hgeGUI();                                                                                                                                                                           
	//Play按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/play.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 17, 464, 152, 100, tex, 0, 0));
	//Setting按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/setting.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 761, 21, 72, 65, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/****************************界面2************************************/
	//Setting界面
	//载入背景图片
	tex = hge->Texture_Load("bin/Textures/游戏界面/SettingPG.png");
	m_bgTex.push_back(tex);
	//加载按钮控件
	gui = new hgeGUI();
	//离开（小X）按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/小X.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 778, 24, 63, 63, tex, 0, 0));
	//帮助按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/HelpBook.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 635, 370, 105, 150, tex, 0, 0));
	//游戏音乐升高按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/Rise.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(3, 757, 203, 43, 41, tex, 0, 0));
	//游戏音乐降低按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/Lower.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(4, 581, 202, 43, 41, tex, 0, 0));
	//游戏音效升高按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/Rise.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(5, 757, 308, 43, 41, tex, 0, 0));
	//游戏音效降低按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/Lower.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(6, 581, 308, 43, 41, tex, 0, 0));

	//加载音效的纹理
	m_EffectTex = hge->Texture_Load("bin/Textures/游戏界面/Voice.png");
	if(m_EffectTex)
	{
		for(int i=0; i<7; i++)
		{
			m_pEffectSpr[i] = new hgeSprite(m_EffectTex, 114*i, 0, 114, 38);
		}
	}

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/****************************界面3*************************************/
	//帮助界面
	//载入背景图片
	tex = hge->Texture_Load("bin/Textures/游戏界面/Help.png");
	m_bgTex.push_back(tex);
	//加载按钮控件
	gui = new hgeGUI();
	//离开（小X）按钮
	tex = hge->Texture_Load("bin/Textures/游戏界面/小X.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 778, 24, 63, 63, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/*****************************界面4***********************************/
	//Escape按键反应界面
	//载入背景图片
	tex = hge->Texture_Load("bin/Textures/游戏场景/暂停键菜单.png");
	m_bgTex.push_back(tex);
	//加载按钮控件
	gui = new hgeGUI();
	//Resume 按钮
	tex = hge->Texture_Load("bin/Textures/游戏场景/Resume.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 361, 245, 204, 65, tex, 0, 0));
	//Give Up 按钮
	tex = hge->Texture_Load("bin/Textures/游戏场景/Give Up.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 361, 321, 204, 65, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/*******************************界面5*********************************/
	//SUCCESS_1界面
	//载入背景图片
	tex = hge->Texture_Load("bin/Textures/游戏场景/初步画面（测试）.png");
	m_bgTex.push_back(tex);
	//加载按钮控件
	gui = new hgeGUI();
	//下一关按钮
	tex = hge->Texture_Load("bin/Textures/游戏场景/NextLevel.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 715, 544, 113, 41, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/*******************************界面6*********************************/
	//SUCCESS_2界面
	//载入背景图片
	tex = hge->Texture_Load("bin/Textures/游戏场景/初步画面（测试）.png");
	m_bgTex.push_back(tex);
	//加载按钮控件
	gui = new hgeGUI();

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/********************************界面7*********************************/
	//游戏失败
	//载入背景图片
	tex = hge->Texture_Load("bin/Textures/游戏场景/失败.png");
	m_bgTex.push_back(tex);
	//加载按钮控件
	gui = new hgeGUI();
	//失败重玩按钮
	tex = hge->Texture_Load("bin/Textures/游戏场景/失败重玩.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 700, 508, 137, 34, tex, 0, 0));
	//失败退出按钮
	tex = hge->Texture_Load("bin/Textures/游戏场景/失败退出.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 730, 548, 97, 34, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/****************************************************************/
	//将主界面设置为初始界面
	m_nGuiID=0;
	m_pBgSpr=new hgeSprite(m_bgTex[m_nGuiID],0,0,850,600);
	m_gui[m_nGuiID]->Enter();
}

bool CGameManager::FrameFunc()
{
	float dt = m_hge->Timer_GetDelta();
	int id;
	static int lastid=0;

	switch(m_nGuiID)
	{
	case 0://Flash
		id = m_gui[m_nGuiID]->Update(dt);
		if (m_hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			pFlashSprite->Pause();
			m_nGuiID=1;
		}
		if(!pFlashSprite->IsPlaying())
		{
			m_nGuiID=1;
			m_pMusicPlay->Play(main_menu);
		}
		pFlashSprite->Update(dt);
		break;
	case 1:  //主界面
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //点击Play按钮
				pFlashSprite2->Unpause();
				pFlashSprite2->Update(dt);
				if(!pFlashSprite2->IsPlaying()){
					pGameRender.castle.AddFull();
					m_nGuiID = -1;
					m_pMusicPlay->Play(defend);
					m_pMusicPlay->Stop(main_menu);
					pGameRender.Start();
					pGameRender.Init(m_hge);
				}
				break;

			case 2:  //点击Setting按钮
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if(id) 
		{ 
			m_pMusicPlay->Play(btn_click);  //播放按钮点击声音
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 2:  //Setting界面
		id = m_gui[m_nGuiID]->Update(dt);
		if (id == -1)
		{
			switch(lastid)
			{
			case 1:  //点击离开(小X)按钮
				m_nGuiID = 1;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_gui[m_nGuiID]->Enter();
				break;

			case 2:  //点击HelpBook按钮
				m_nGuiID = 3;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_gui[m_nGuiID]->Enter();
				break;

			case 3:  //游戏音乐升高按钮
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_pMusicPlay->Set_VolumePlus(main_menu);
				m_gui[m_nGuiID]->Enter();
				break;

			case 4:  //游戏音乐降低按钮
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_pMusicPlay->Set_VolumeReduce(main_menu);
				m_gui[m_nGuiID]->Enter();
				break;

			case 5:  //游戏音效升高按钮
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_pMusicPlay->Set_VolumePlus(btn_click);
				m_gui[m_nGuiID]->Enter();
				break;

			case 6: //游戏音效降低按钮
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_pMusicPlay->Set_VolumeReduce(btn_click);
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if (id)
		{
			m_pMusicPlay->Play(btn_click);  //播放按钮点击声音
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 3:  //帮助界面
		id = m_gui[m_nGuiID]->Update(dt);
		if (id == -1)
		{
			switch(lastid)
			{
			case 1:  //点击离开(小X)按钮
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if (id)
		{
			m_pMusicPlay->Play(btn_click);    //播放按钮点击声音
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 4:  //Esc界面
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //Resume按钮
				m_nGuiID=-1;
				m_pMusicPlay->Resume(defend);
				m_pMusicPlay->Resume(defend2);
				break;

			case 2:  //Give up按钮
				m_nGuiID = 1;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_pMusicPlay->Stop(defend);
				m_pMusicPlay->Stop(defend2);
				m_pMusicPlay->Play(main_menu);
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if(id)
		{
			m_pMusicPlay->Play(btn_click);  //播放按钮点击音效
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 5:   //SUCCESS_1界面
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //下一关按钮
				pFlashSprite3->Unpause();
				pFlashSprite3->Update(dt);
				if(!pFlashSprite3->IsPlaying())
				{
					m_nGuiID = -1;
					m_pMusicPlay->Play(defend2);
					m_pMusicPlay->Stop(victory1);
					pGameRender.gameState=RUNNING2;
				}
				break;

			default:
				break;
			}
		}
		else if(id)
		{
			m_pMusicPlay->Play(btn_click);  //播放按钮点击音效
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 6:  //SUCCESS_2界面
		id = m_gui[m_nGuiID]->Update(dt);
		pFlashSprite1->Unpause();
		pFlashSprite1->Update(dt);
		if(!pFlashSprite1->IsPlaying()){
			m_nGuiID =1;
			m_pMusicPlay->Stop(victory2);
			m_pMusicPlay->Play(main_menu);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
			m_gui[m_nGuiID]->Enter();
		}
		break;

	case 7:  //游戏失败界面
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //失败重玩按钮
				m_nGuiID = -1;
				m_pMusicPlay->Stop(fail);
				m_pMusicPlay->Play(defend);
				pGameRender.castle.AddFull();
				pGameRender.Start();
				pGameRender.Init(m_hge);
				break;

			case 2:  //失败退出按钮
				m_nGuiID = 1;
				m_pMusicPlay->Stop(fail);
				m_pMusicPlay->Play(main_menu);
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				pGameRender.gameState=A;
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if(id)
		{
			m_pMusicPlay->Play(btn_click);  //播放按钮点击音效
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	default:  //游戏运行界面
		switch(pGameRender.GetState())  //检测关卡状态
		{
		case RUNNING:
		case RUNNING2:
			//判断键盘输入
			if (m_hge->Input_GetKeyState(HGEK_ESCAPE))
			{
				//弹出暂停界面
				m_nGuiID = 4;
				m_pMusicPlay->Pause(defend);
				m_pMusicPlay->Pause(defend2);
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
				m_gui[m_nGuiID]->Enter();
			}
			pGameRender.FrameFunc();      //调用帧函数
			break;

		case SUCCESS:
			//弹出第一关游戏成功界面
			m_nGuiID = 5;
			m_pMusicPlay->Stop(defend);
			m_pMusicPlay->Play(victory1);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
			m_gui[m_nGuiID]->Enter();
			break;

		case SUCCESS2:
			m_nGuiID = 6;
			m_pMusicPlay->Stop(defend2);
			m_pMusicPlay->Play(victory2);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
			m_gui[m_nGuiID]->Enter();
			break;

		case FAILED:
			//弹出游戏失败界面
			m_nGuiID = 7;
			m_pMusicPlay->Stop(defend);
			m_pMusicPlay->Stop(defend2);
			m_pMusicPlay->Play(fail);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //设置背景图片
			m_gui[m_nGuiID]->Enter();
			break;

		default:
			break;
		}
		break;
	}
	return false;
}


void CGameManager::RenderFunc()
{
	m_hge->Gfx_BeginScene();
	m_hge->Gfx_Clear(0);

	int volume_1 = CGameSetting::GetInstance(m_hge)->Get_VOLUME1(); //将获得的音量大小转化成音效纹理队列中的对应图片
	                                                                //此处是音乐
	switch(volume_1)
	{
	case 50:
		volume_1 = 3;
		break;
	
	case 60:
		volume_1 = 4;
		break;
	case 70:
		volume_1 = 5;
		break;
	case 80:
		volume_1 = 6;
	    break;
	
	case 40:
		volume_1 = 2;
		break;
	case 30:
		volume_1 = 1;
		break;
	case 20:
		volume_1 = 0;
		break;

	default:
		if(volume_1 > 80)
		{
			volume_1 = 6;
		}
		else
		{
			volume_1 = 0;
		}
		break;
	}

	int volume_2 = CGameSetting::GetInstance(m_hge)->Get_VOLUME2();  //将获得的音量大小转化成音效纹理队列中的对应图片
	                                                                 //此处是音效
	switch(volume_2)
	{
	case 50:
		volume_2 = 3;
		break;
	
	case 60:
		volume_2 = 4;
		break;
	case 70:
		volume_2 = 5;
		break;
	case 80:
		volume_2 = 6;
	    break;
	
	case 40:
		volume_2 = 2;
		break;
	case 30:
		volume_2 = 1;
		break;
	case 20:
		volume_2 = 0;
		break;

	default:
		if(volume_2 > 80)
		{
			volume_2 = 6;
		}
		else
		{
			volume_2 = 0;
		}
		break;
	}

	switch(m_nGuiID)
	{
	case 0:
		pFlashSprite->Render(0,0);
		break;

	case 1:  //主菜单界面
		if(!pFlashSprite2->IsPlaying()){
			m_pBgSpr->Render(0, 0);	
			m_gui[m_nGuiID]->Render();
		}
		pFlashSprite2->Render(0,0);
		break;

	case 2:  //Setting界面
		m_pBgSpr->Render(0, 0);		
		m_pEffectSpr[volume_1]->Render(639,206);  //渲染音效纹理
		m_pEffectSpr[volume_2]->Render(638,309);  //渲染音效纹理
		m_gui[m_nGuiID]->Render();
		break;

	case 3:  //帮助界面
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();

		break;

	case 4:  //ESC界面
		pGameRender.RenderFunc();
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();
		break;

	case 5:  //SUCCESS_1界面
		pFlashSprite3->Render(0,0);
		if(!pFlashSprite3->IsPlaying())
		{
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();
		}
		break;

	case 6:  //SUCCESS_2界面
		pFlashSprite1->Render(0,0);
		break;

	case 7:  //失败界面
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();
		break;

	default:  //游戏运行时界面
		pGameRender.RenderFunc();
		break;
	}

	m_hge->Gfx_EndScene();
}














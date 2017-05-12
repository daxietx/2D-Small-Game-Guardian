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

	m_pEffectSpr[7] = NULL;  //��Ч�ľ���ָ��

	m_pBgSpr = NULL;    //��������ָ��
	m_pCursorSpr = NULL;//��꾫��ָ��
	m_pGameSetting = NULL;//��Ϸ������ָ��
	m_pMusicPlay = NULL;  //���ֿ�����ָ��
	//flash����
	pFlashSprite=NULL;

}

CGameManager::~CGameManager(void)
{
	//�ͷű���ͼƬ����
	for (int i=0; i<m_bgTex.size(); ++i)
	{
		m_hge->Texture_Free(m_bgTex[i]);
	}

	//�ͷ���������
	for (int i=0; i<m_tex.size(); ++i)
	{
		m_hge->Texture_Free(m_tex[i]);
	}

	//ɾ���ؼ�������ָ��
	for (int i=0; i<m_gui.size(); ++i)
	{
		delete m_gui[i];
	}

	//ɾ����Ч������
	m_hge->Texture_Free(m_EffectTex);

	delete m_pBgSpr;    //ɾ����������ָ��
	m_pBgSpr = NULL;
	delete m_pCursorSpr;//ɾ����꾫��ָ��
	m_pCursorSpr = NULL;
	delete m_pGameSetting;//ɾ����Ϸ������ָ��
	m_pGameSetting = NULL;
	delete m_pMusicPlay;  //ɾ�����ֿ�����ָ��
	m_pMusicPlay = NULL;
	delete pFlashSprite;//ɾ��flash��ָ��
	pFlashSprite=NULL;
}

void CGameManager::Init(HGE * hge)//�������е���Դ
{

	m_hge = hge;

	//��ȡ�������ʵ������
	m_pGameSetting = CGameSetting::GetInstance(hge);//��Ϸ������ָ��
	m_pMusicPlay = CMusicPlay::GetInstance(hge);    //���ֿ�����ָ��

	hgeGUI   *gui;
	HTEXTURE tex;
	//�����������ʹ�����꾫��
	tex = hge->Texture_Load("bin/Textures/cursor.png");
	m_tex.push_back(tex);
	m_pCursorSpr = new hgeSprite(tex,0,0,28,31);

	/************************����0***************************************/
	//flash���Ž���
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Begin.png "); 
	m_bgTex.push_back(tex);
	gui = new hgeGUI();      
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/play.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 17, 464, 152, 100, tex, 0, 0));
	//Setting
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/setting.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 761, 21, 72, 65, tex, 0, 0));


	pFlashSprite = new FlashSprite;
	//// ����flash�ļ�
	pFlashSprite->StartFlash("open.swf",850,600);
	pFlashSprite->SetLoopPlay(false);
	m_gui.push_back(gui);
//////////////////////////////////////////////////////////////////////////////////////
	
	pFlashSprite1 = new FlashSprite;
	//// ����flash�ļ�����
	pFlashSprite1->StartFlash("ceshijieshu.swf",850,600);
	pFlashSprite1->SetLoopPlay(false);
	pFlashSprite1->Pause();


    pFlashSprite2 = new FlashSprite;
	//// ����flash�ļ�
	pFlashSprite2->StartFlash("1.swf",850,600);
	pFlashSprite2->SetLoopPlay(false);
	pFlashSprite2->Pause();

    pFlashSprite3 = new FlashSprite;
	//// ����flash�ļ�
	pFlashSprite3->StartFlash("2.swf",850,600);
	pFlashSprite3->SetLoopPlay(false);
	pFlashSprite3->Pause();






    /************************����1***************************************/
	//���˵�����
	//���뱳��ͼƬ
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Begin.png"); 
	m_bgTex.push_back(tex);
	//���ذ�ť�ؼ�
	gui = new hgeGUI();                                                                                                                                                                           
	//Play��ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/play.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 17, 464, 152, 100, tex, 0, 0));
	//Setting��ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/setting.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 761, 21, 72, 65, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/****************************����2************************************/
	//Setting����
	//���뱳��ͼƬ
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/SettingPG.png");
	m_bgTex.push_back(tex);
	//���ذ�ť�ؼ�
	gui = new hgeGUI();
	//�뿪��СX����ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/СX.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 778, 24, 63, 63, tex, 0, 0));
	//������ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/HelpBook.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 635, 370, 105, 150, tex, 0, 0));
	//��Ϸ�������߰�ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Rise.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(3, 757, 203, 43, 41, tex, 0, 0));
	//��Ϸ���ֽ��Ͱ�ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Lower.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(4, 581, 202, 43, 41, tex, 0, 0));
	//��Ϸ��Ч���߰�ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Rise.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(5, 757, 308, 43, 41, tex, 0, 0));
	//��Ϸ��Ч���Ͱ�ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Lower.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(6, 581, 308, 43, 41, tex, 0, 0));

	//������Ч������
	m_EffectTex = hge->Texture_Load("bin/Textures/��Ϸ����/Voice.png");
	if(m_EffectTex)
	{
		for(int i=0; i<7; i++)
		{
			m_pEffectSpr[i] = new hgeSprite(m_EffectTex, 114*i, 0, 114, 38);
		}
	}

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/****************************����3*************************************/
	//��������
	//���뱳��ͼƬ
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Help.png");
	m_bgTex.push_back(tex);
	//���ذ�ť�ؼ�
	gui = new hgeGUI();
	//�뿪��СX����ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/СX.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 778, 24, 63, 63, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/*****************************����4***********************************/
	//Escape������Ӧ����
	//���뱳��ͼƬ
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/��ͣ���˵�.png");
	m_bgTex.push_back(tex);
	//���ذ�ť�ؼ�
	gui = new hgeGUI();
	//Resume ��ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Resume.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 361, 245, 204, 65, tex, 0, 0));
	//Give Up ��ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/Give Up.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 361, 321, 204, 65, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/*******************************����5*********************************/
	//SUCCESS_1����
	//���뱳��ͼƬ
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/�������棨���ԣ�.png");
	m_bgTex.push_back(tex);
	//���ذ�ť�ؼ�
	gui = new hgeGUI();
	//��һ�ذ�ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/NextLevel.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 715, 544, 113, 41, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/*******************************����6*********************************/
	//SUCCESS_2����
	//���뱳��ͼƬ
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/�������棨���ԣ�.png");
	m_bgTex.push_back(tex);
	//���ذ�ť�ؼ�
	gui = new hgeGUI();

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/********************************����7*********************************/
	//��Ϸʧ��
	//���뱳��ͼƬ
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/ʧ��.png");
	m_bgTex.push_back(tex);
	//���ذ�ť�ؼ�
	gui = new hgeGUI();
	//ʧ�����水ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/ʧ������.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(1, 700, 508, 137, 34, tex, 0, 0));
	//ʧ���˳���ť
	tex = hge->Texture_Load("bin/Textures/��Ϸ����/ʧ���˳�.png");
	m_tex.push_back(tex);
	gui->AddCtrl(new hgeGUIButton(2, 730, 548, 97, 34, tex, 0, 0));

	gui->SetCursor(m_pCursorSpr);
	m_gui.push_back(gui);

	/****************************************************************/
	//������������Ϊ��ʼ����
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
	case 1:  //������
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //���Play��ť
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

			case 2:  //���Setting��ť
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if(id) 
		{ 
			m_pMusicPlay->Play(btn_click);  //���Ű�ť�������
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 2:  //Setting����
		id = m_gui[m_nGuiID]->Update(dt);
		if (id == -1)
		{
			switch(lastid)
			{
			case 1:  //����뿪(СX)��ť
				m_nGuiID = 1;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_gui[m_nGuiID]->Enter();
				break;

			case 2:  //���HelpBook��ť
				m_nGuiID = 3;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_gui[m_nGuiID]->Enter();
				break;

			case 3:  //��Ϸ�������߰�ť
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_pMusicPlay->Set_VolumePlus(main_menu);
				m_gui[m_nGuiID]->Enter();
				break;

			case 4:  //��Ϸ���ֽ��Ͱ�ť
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_pMusicPlay->Set_VolumeReduce(main_menu);
				m_gui[m_nGuiID]->Enter();
				break;

			case 5:  //��Ϸ��Ч���߰�ť
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_pMusicPlay->Set_VolumePlus(btn_click);
				m_gui[m_nGuiID]->Enter();
				break;

			case 6: //��Ϸ��Ч���Ͱ�ť
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_pMusicPlay->Set_VolumeReduce(btn_click);
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if (id)
		{
			m_pMusicPlay->Play(btn_click);  //���Ű�ť�������
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 3:  //��������
		id = m_gui[m_nGuiID]->Update(dt);
		if (id == -1)
		{
			switch(lastid)
			{
			case 1:  //����뿪(СX)��ť
				m_nGuiID = 2;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if (id)
		{
			m_pMusicPlay->Play(btn_click);    //���Ű�ť�������
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 4:  //Esc����
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //Resume��ť
				m_nGuiID=-1;
				m_pMusicPlay->Resume(defend);
				m_pMusicPlay->Resume(defend2);
				break;

			case 2:  //Give up��ť
				m_nGuiID = 1;
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
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
			m_pMusicPlay->Play(btn_click);  //���Ű�ť�����Ч
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 5:   //SUCCESS_1����
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //��һ�ذ�ť
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
			m_pMusicPlay->Play(btn_click);  //���Ű�ť�����Ч
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	case 6:  //SUCCESS_2����
		id = m_gui[m_nGuiID]->Update(dt);
		pFlashSprite1->Unpause();
		pFlashSprite1->Update(dt);
		if(!pFlashSprite1->IsPlaying()){
			m_nGuiID =1;
			m_pMusicPlay->Stop(victory2);
			m_pMusicPlay->Play(main_menu);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
			m_gui[m_nGuiID]->Enter();
		}
		break;

	case 7:  //��Ϸʧ�ܽ���
		id = m_gui[m_nGuiID]->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{
			case 1:  //ʧ�����水ť
				m_nGuiID = -1;
				m_pMusicPlay->Stop(fail);
				m_pMusicPlay->Play(defend);
				pGameRender.castle.AddFull();
				pGameRender.Start();
				pGameRender.Init(m_hge);
				break;

			case 2:  //ʧ���˳���ť
				m_nGuiID = 1;
				m_pMusicPlay->Stop(fail);
				m_pMusicPlay->Play(main_menu);
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				pGameRender.gameState=A;
				m_gui[m_nGuiID]->Enter();
				break;

			default:
				break;
			}
		}
		else if(id)
		{
			m_pMusicPlay->Play(btn_click);  //���Ű�ť�����Ч
			lastid=id; 
			m_gui[m_nGuiID]->Leave();
		}
		break;

	default:  //��Ϸ���н���
		switch(pGameRender.GetState())  //���ؿ�״̬
		{
		case RUNNING:
		case RUNNING2:
			//�жϼ�������
			if (m_hge->Input_GetKeyState(HGEK_ESCAPE))
			{
				//������ͣ����
				m_nGuiID = 4;
				m_pMusicPlay->Pause(defend);
				m_pMusicPlay->Pause(defend2);
				m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
				m_gui[m_nGuiID]->Enter();
			}
			pGameRender.FrameFunc();      //����֡����
			break;

		case SUCCESS:
			//������һ����Ϸ�ɹ�����
			m_nGuiID = 5;
			m_pMusicPlay->Stop(defend);
			m_pMusicPlay->Play(victory1);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
			m_gui[m_nGuiID]->Enter();
			break;

		case SUCCESS2:
			m_nGuiID = 6;
			m_pMusicPlay->Stop(defend2);
			m_pMusicPlay->Play(victory2);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
			m_gui[m_nGuiID]->Enter();
			break;

		case FAILED:
			//������Ϸʧ�ܽ���
			m_nGuiID = 7;
			m_pMusicPlay->Stop(defend);
			m_pMusicPlay->Stop(defend2);
			m_pMusicPlay->Play(fail);
			m_pBgSpr->SetTexture(m_bgTex[m_nGuiID]); //���ñ���ͼƬ
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

	int volume_1 = CGameSetting::GetInstance(m_hge)->Get_VOLUME1(); //����õ�������Сת������Ч��������еĶ�ӦͼƬ
	                                                                //�˴�������
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

	int volume_2 = CGameSetting::GetInstance(m_hge)->Get_VOLUME2();  //����õ�������Сת������Ч��������еĶ�ӦͼƬ
	                                                                 //�˴�����Ч
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

	case 1:  //���˵�����
		if(!pFlashSprite2->IsPlaying()){
			m_pBgSpr->Render(0, 0);	
			m_gui[m_nGuiID]->Render();
		}
		pFlashSprite2->Render(0,0);
		break;

	case 2:  //Setting����
		m_pBgSpr->Render(0, 0);		
		m_pEffectSpr[volume_1]->Render(639,206);  //��Ⱦ��Ч����
		m_pEffectSpr[volume_2]->Render(638,309);  //��Ⱦ��Ч����
		m_gui[m_nGuiID]->Render();
		break;

	case 3:  //��������
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();

		break;

	case 4:  //ESC����
		pGameRender.RenderFunc();
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();
		break;

	case 5:  //SUCCESS_1����
		pFlashSprite3->Render(0,0);
		if(!pFlashSprite3->IsPlaying())
		{
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();
		}
		break;

	case 6:  //SUCCESS_2����
		pFlashSprite1->Render(0,0);
		break;

	case 7:  //ʧ�ܽ���
		m_pBgSpr->Render(0, 0);
		m_gui[m_nGuiID]->Render();
		break;

	default:  //��Ϸ����ʱ����
		pGameRender.RenderFunc();
		break;
	}

	m_hge->Gfx_EndScene();
}














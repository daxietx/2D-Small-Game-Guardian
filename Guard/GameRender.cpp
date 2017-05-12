#include "stdafx.h"
#include "GameRender.h"
#include<time.h>
#include "GameSetting.h"
#include "MusicPlay.h"

GameRender* GameRender::m_pGameRender = NULL;
GameRender::GameRender(void)
{
	cursor = NULL;
	fireAbleRender = false;
	m_pGameSetting = NULL;//游戏控制类指针
	m_pMusicPlay = NULL;  //音乐控制类指针

}
GameRender::~GameRender()
{
	delete cursor;
}

GameRender* GameRender::GetInstance()
{
	if (m_pGameRender==NULL)
	{
		m_pGameRender = new GameRender();
	}
	return m_pGameRender;
}

void GameRender::RenderFunc()
{

	//渲染背景和武器
	bg_Spr->Render(0,0);


	if(fireAbleRender)
	{
		bombs[weaponID]->Render();
	}
	else
		bombs[weaponID]->Render();

	//渲染小怪
	for(int i=0;i<monster.size();++i)
	{
		monster[i].Render();
	}

	//判断道具按钮是否该显现
     if(moneyNum>=firePrice)
		firespr->Render(fireRect.x1,fireRect.y1);
	if(moneyNum>=chengFangPrice)
	chengFangspr->Render(chengFangRect.x1,chengFangRect.y1);
	if(moneyNum>doubleBombPrice)
		doubleBombspr->Render(doubleBombRect.x1,doubleBombRect.y1);
	if(moneyNum>=bombshellPrice)
		bombshellspr->Render(bombshellRect.x1,bombshellRect.y1);

	//渲染道具点击时的特效
	if(itemClicked == true)
		RenderItemEffect();
	
	//显示金币数
	if(moneyNum<0)
	{
	moneyNum=0;
	moneySpr[moneyNum]->Render(44,55);
	}
	else if(moneyNum<10)
	moneySpr[moneyNum]->Render(44,55);
	else if(moneyNum>=10&&moneyNum<100)                                                 //moneyNum最大是两位数
	{
		int i;
		i=moneyNum/10;
		moneySpr[i]->Render(44,55);
		moneySpr[moneyNum-i*10]->Render(64,55);
	}
	else if((moneyNum>=100)&&(moneyNum<1000))
	{
		int i;
		i=moneyNum/100;
		moneySpr[i]->Render(44,55);
		int j;
		j=(moneyNum-i*100)/10;
		moneySpr[j]->Render(64,55);
		int m;
		m=moneyNum-i*100-j*10;
		moneySpr[j]->Render(84,55);
	}
	//显示城墙的血条
	int k;
	k=castle.lifeNum;
	if(castle.life>0&&castle.life<1)
		k=1;
	bloodSpr[k]->Render(44,26);

	//渲染炸弹
	if(hasBomb)
	{
		for(int i=0;i<bombshells.size();i++)
		{
			if(bombshells[i].canRender)
				bombshells[i].Render();

			if(bombshells[i].isBomb)
				bombshells[i].BlastRender();
		}
	}

	//如果游戏处于RUNNING2，boss才被渲染
	if(gameState==RUNNING2)
	if(isDeadBoss==false)
	bosses[0].Render();

	//渲染鼠标
	cursorGui->Render();
}

bool GameRender::FrameFunc()
{
	 float dt = m_hge->Timer_GetDelta();
	 m_hge->Gfx_Clear(0xFF000000);
 
	 //当游戏处于RUNNING状态时，才更新，因为这里面涉及到了，小怪隔多少时间产生和Boss隔多少时间换位置的问题。
	 if(gameState==RUNNING)
	 {
		 UpdateState();
	 IsAutoCreatMonster();
	 }

	 //当游戏处于RUNNING2状态时boss才被更新
	 if(gameState==RUNNING2)
	 {
		 UpdateSecondState();
		 if(isDeadBoss==false)
		 UpdateBoss();
	 }

	 //更新鼠标。
	 cursorGui->Update(dt);
	 cursorGui->Enter();


	 //更新小怪
	 UpdateMonster();                            //怪物移动
	   //先将所有小怪的位置与炸弹的爆炸范围比较一下并删除爆炸了的炸弹
	 UpdateMonNum();

	 //更新小怪的位置
	 MonsterMove();

	 //根据输入的空格键切换武器到默认状态
	 if(m_hge->Input_GetKey()==HGEK_SPACE)
	 {
		 m_pMusicPlay->Play(Switch1);
		 weaponID=0;
	 }
	  //得到鼠标的点击点，来渲染子弹，和根据点击后的点，判断哪个道具按钮被点击了，并减少moneyNum
	 if(m_hge->Input_GetKey()==HGEK_LBUTTON)      //鼠标点击，发射子弹
	 {
		 mouseClicked = true;
		 float x=0;
		 float y=0;
		 m_hge->Input_GetMousePos(&x,&y);	 
		 p.x = x;
		 p.y = y;


		 
		 //判断道具是否被点击，点击了，就不发射子弹，没被点击就发射子弹。
		if(chengFangRect.TestPoint(p.x,p.y)||bombshellRect.TestPoint(p.x,p.y)||fireRect.TestPoint(p.x,p.y)||doubleBombRect.TestPoint(p.x,p.y))
		  {
		 //根据点击了哪个道具来更新金钱数或者炸弹的渲染。
		 if(chengFangRect.TestPoint(p.x,p.y)&&moneyNum>=20)
		 {
			 m_pMusicPlay->Play(heal1);
			 moneyNum-=20;
			 castle.AddFull();
			 itemClicked = true;
			 StartItemEffect(36,193);
		 }

		  if(bombshellRect.TestPoint(p.x,p.y)&&moneyNum>=20)
		  {
			  m_pMusicPlay->Play(Switch1);
			  Bombshell bombshell;
			  bombshell.Init(m_hge);
			  bombshells.push_back(bombshell);
			  moneyNum-=20;
			  hasBomb = true;
			  itemClicked = true;
			  StartItemEffect(36,271);
		  }
		   else if(bombshells.size()<0) hasBomb = false;

		   if(fireRect.TestPoint(p.x,p.y)&&moneyNum>=50)
		   {
			m_pMusicPlay->Play(Switch1);
			moneyNum-=50;
			weaponID=2;
			 bombs[weaponID]->Launch(bombs[weaponID]->GetBombEndPosition().x,bombs[weaponID]->GetBombEndPosition().y,p.x,p.y);
			bombs[weaponID]->GetRoute(500,200,p.x,p.y);
			fireAbleRender = true;
			itemClicked = true;
			StartItemEffect(36,431);
		   }

		    if(doubleBombRect.TestPoint(p.x,p.y)&&moneyNum>=30)
			{
			 m_pMusicPlay->Play(Switch1);
			 moneyNum-=30;
			 weaponID=1;
			 itemClicked = true;
			  StartItemEffect(36,351);
			}
		  }
		  else
		  {
		  //得到鼠标的点击后才开始加一个子弹
		 if(lastTime==currentTime)
		 {
		  if(weaponID==0)
		  m_pMusicPlay->Play(SingleBomb1);
		  else if(weaponID==1)
		  m_pMusicPlay->Play(DoubleBomb1);
		  else
		  m_pMusicPlay->Play(Fire1);
		  bombs[weaponID]->Launch(bombs[weaponID]->GetBombEndPosition().x,bombs[weaponID]->GetBombEndPosition().y,p.x,p.y);
		  lastTime= m_hge->Timer_GetTime();
		 }
		 currentTime1= m_hge->Timer_GetTime();
		 if(currentTime1-lastTime>0.3)
		 {
		  if(weaponID==0)
		  m_pMusicPlay->Play(SingleBomb1);
		  else if(weaponID==1)
		  m_pMusicPlay->Play(DoubleBomb1);
		  else
		  m_pMusicPlay->Play(Fire1);
		  bombs[weaponID]->Launch(bombs[weaponID]->GetBombEndPosition().x,bombs[weaponID]->GetBombEndPosition().y,p.x,p.y);
		  bombs[weaponID]->GetRoute(bombs[weaponID]->GetBombEndPosition().x,bombs[weaponID]->GetBombEndPosition().y,p.x,p.y);
		  lastTime=currentTime1;
		 }
		  }


		  if(hasBomb)
		 {
		 //如果炸弹被放下,那么该爆炸
		 for(int i=0;i<bombshells.size();i++)
		 {
			 if(bombshells[i].isPutDown(p.x,p.y))
			 {
				 m_pMusicPlay->Play(Bombshell1);
				 startTime2=m_hge->Timer_GetTime();
				 bombshells[i].Blast();
				 bombshells[i].isBomb=true;
				 bombshells[i].SetRange();
			 }
			 else
			 {
				 bombshells[i].isBomb=false;
				 bombshells[i].canRender=true;
			 }
		 }
		 }
	 }
	 //////////////////////////////////////////////////////////////////
	 if(weaponID==2)
		bombs[weaponID]->GetJudgePoints();
	 ////////////////////////////////////////////////////////////////////
	  //炸弹随鼠标移动
	m_hge->Input_GetMousePos(&mouse_x,&mouse_y); //捕捉鼠标实时位置
	if(hasBomb)
	{
		for(int i = 0;i<bombshells.size();i++)
		{
			if(bombshells[i].isBomb)
				 bombshells[i].Update(dt);
			if(bombshells[i].canRender)
			{
				bombshells[i].PickUp(mouse_x,mouse_y);
			}
		}
	}

      FrameNum++;
	 //根据鼠标的点击来调整炮筒转的角度
	  POINT a;
	 a.x=mouse_x+4;                          //这里的27,26，是鼠标图片的中心位置。
	 a.y=mouse_y+2;
	 bombs[weaponID]->AngleTrans(a);   

	 //更新子弹
	 if(mouseClicked == true)
		 bombs[weaponID]->Update(dt);               //子弹移动
	 //更新道具特效
	 if(itemClicked == true)
		 UpdateItemEffect(dt);	 
	
	return false;
}

void GameRender::Init(HGE * hge)
{
	m_hge = hge;

	m_pGameSetting = CGameSetting::GetInstance(hge);//游戏设置类指针
	m_pMusicPlay = CMusicPlay::GetInstance(hge);    //音乐控制类指针
	for(int i=0;i<5;i++)
	{
	m_pMusicPlay->Set_VolumePlus(Fire1);
	m_pMusicPlay->Set_VolumePlus(BOSSHit1);
	m_pMusicPlay->Set_VolumePlus(BOSSDead1);
	m_pMusicPlay->Set_VolumePlus(Switch1);
	m_pMusicPlay->Set_VolumePlus(heal1);
	}
	//加载背景图。
	bg_Tex=m_hge->Texture_Load("bin/Textures/场景.png"); //设置背景
	bg_Spr=new hgeSprite(bg_Tex,0,0,850,600);
	

	/////////////加载道具纹理////////////////////////
	chengFangTex=m_hge->Texture_Load("bin/Textures/城防.png");
	if(chengFangTex)
		chengFangspr=new hgeSprite(chengFangTex,0,0,74, 73);
	chengFangRect.x1=0;
	chengFangRect.y1=157;
	chengFangRect.x2=74;
	chengFangRect.y2=230;



	bombshellTex=m_hge->Texture_Load("bin/Textures/炸弹.png");
	if(bombshellTex)
		bombshellspr=new hgeSprite(bombshellTex,0,0, 72, 76);
	bombshellRect.x1=0;
	bombshellRect.y1=235;
	bombshellRect.x2=72;
	bombshellRect.y2=311;


	fireTex=m_hge->Texture_Load("bin/Textures/喷火器.png");
	if(fireTex)
		firespr=new hgeSprite(fireTex,0,0,73, 78);
	fireRect.x1=0;
	fireRect.y1=395;
	fireRect.x2=73;
	fireRect.y2=473;


	
	doubleBombTex=m_hge->Texture_Load("bin/Textures/双炮.png");
	if(doubleBombTex)
		doubleBombspr=new hgeSprite(doubleBombTex,0,0,72, 78);
	doubleBombRect.x1=0;
	doubleBombRect.y1=315;
	doubleBombRect.x2=72;
	doubleBombRect.y2=393;

	///////////////////////初始化道具特效/////////////////////
	item_psi = "bin/Effects/粒子系统/particle9.psi";
	itemEffectTex = m_hge->Texture_Load("bin/Effects/粒子系统/particles.png");
	itemSpr = new hgeSprite(itemEffectTex,0,32,32,32);
    itemSpr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);        //      设置混合模式
    itemSpr->SetHotSpot(16, 16);    // 设置粒子精灵中心点
	item_particle_effect = new hgeParticleSystem(item_psi,itemSpr);
	item_particle_effect->info.fLifetime = 0.07;
	item_particle_effect->info.nEmission = 500;

	//////////////////////加载金币纹理////////////////////////
	moneyTex=m_hge->Texture_Load("bin/Textures/金币.png");
	if(moneyTex)
		for(int i=0;i<10;i++)
		moneySpr[i]=new hgeSprite(moneyTex,22*i,0,22, 28);

	
	////////////////////////加载血条的纹理///////////////////////
	bloodTex=m_hge->Texture_Load("bin/Textures/血条.png");
	if(bloodTex)
	for(int i=0;i<6;i++)
		bloodSpr[i]=new hgeSprite(bloodTex,90*i,0,90, 16);


	//加载鼠标纹理
	cursorGui = new hgeGUI();                            //设置鼠标
	cursorTex = hge->Texture_Load("bin/Textures/cursor.png");
	cursor = new hgeSprite(cursorTex,0,0,28,31);
	cursorGui->SetCursor(cursor);
	mouseClicked = false;                                //游戏初始鼠标点击为false


	//初始化炮
	for(int i=0;i<3;i++)
		bombs[i]->Init(m_hge);


     //初始化小怪和大Boss                             
	for(int i=0;i<4;i++)
		AddMonster();
	bosses[0].Init(m_hge);

	//初始化鼠标点击点。
	p.x = -1;
	p.y = -1;

	
	//初始化时间。用这时间差，来判断是否调用isAutoCreatMonster（），和Boss是否更新位置。
	oldTime= m_hge->Timer_GetTime();
	lastTime=m_hge->Timer_GetTime();;
	currentTime= m_hge->Timer_GetTime();
	currentTime1= lastTime;
	startTime2=m_hge->Timer_GetTime();
	currentTime2=startTime2;
}

void GameRender::Start()
{
	//设置属性的初始值
	Boss boss;

	bosses.push_back(boss);

	gameState=RUNNING;
	bosses[0].setBoundary(castle.x1,castle.x2,150);
	bosses[0].currentPos.x=400;
	bosses[0].currentPos.y=550;
	bosses[0].b=0;
	bosses[0].c=681;
	monster.clear();
	bombs.clear();

	moneyNum=0;
	totalMonsterNum=50;
	monsterCreatNum=0;
	monsterDeadNum=0;
	hasBomb = false;
	FrameNum=0;
	isDeadBoss=false;

	monsterIsDisappear=false;
	chengFangPrice=20;
	doubleBombPrice=30;
	bombshellPrice=20;
	firePrice=50;
	weaponID=0;
	
	
	//游戏开始时，应该自动产生的东西。
	Bomb* initBomb = new Bomb();                                   //载入炮
	bombs.push_back(initBomb);
	Bomb* doubleBomb = new DoubleBomb();
	bombs.push_back(doubleBomb);
	Bomb* fireBomb=new FireBomb();
	bombs.push_back(fireBomb);
}

void GameRender::AddMonster()
{
	int kindMonster;
	if(monsterCreatNum<totalMonsterNum)
	{
	    srand((100)*(monsterCreatNum*monsterCreatNum));
		kindMonster=rand()%3;
		POINT startPos;
		startPos.x=rand()%650+80;
		startPos.y=540;
		if(kindMonster==2)
		{
		Monster monster1;
		monster1.setInitPositon(startPos);
		monster1.setBoundary(castle.x1,castle.x2,castle.y);
		monster1.Init(m_hge);
		monster.push_back(monster1);
		}
		else if(kindMonster==1)
		{
	    Monster_Two monster1;
		monster1.setInitPositon(startPos);
		monster1.setBoundary(castle.x1,castle.x2,castle.y);
		monster1.Init(m_hge);
		monster.push_back(monster1);
		}
		else if(kindMonster==0)
		{
		Monster_Three monster1;
		monster1.setInitPositon(startPos);
		monster1.setBoundary(castle.x1,castle.x2,castle.y);
		monster1.Init(m_hge);
		monster.push_back(monster1);
		}
		monsterCreatNum++;
	}
}
void GameRender::UpdateBoss()
{
	vector<Boss >::iterator it1=bosses.begin();
	bool killByBomb=false;
	if(hasBomb)
		{
			for(int i = 0;i<bombshells.size();i++)
			{
				killByBomb = bombshells[i].isBomb && 
					bombshells[i].booRect.TestPoint(bosses[0].currentPos.x,bosses[0].currentPos.y);
				if(killByBomb)
				bosses[0].blood-=bombshells[i].killPower;              
			}

		}

	if(weaponID==0||weaponID==1){
		vector<Bullet >::iterator it=bombs[weaponID]->bullets.begin();
		
		while(it!=bombs[weaponID]->bullets.end())
		{
			if(it1->isHit(it->currentPos))
			{
				m_pMusicPlay->Play(BOSSHit1);
				bombs[weaponID]->bullets.erase(it);
				if(it1->isDead())
				{
					m_pMusicPlay->Play(BOSSDead1);
					isDeadBoss=true;
					 bosses.erase(it1);
			        /*gameState=SUCCESS2;
			        MessageBox(NULL,"游戏成功","提示",MB_OK);*/
				}
				else
					m_pMusicPlay->Play(BOSSHit1);
				break;
			
			}
			it++;
		}
	}
	if(weaponID==2)
	{
		for(int i = 0; i<bombs[weaponID]->judgePoints.size();i++)
		{
			POINT p;
			p.x=bombs[weaponID]->judgePoints[i].x;
			p.y=bombs[weaponID]->judgePoints[i].y;
			if(it1->isHit(p))
			{
				if(it1->isDead()){
					isDeadBoss=true;
					 bosses.erase(it1);
					/*gameState=SUCCESS2;
					MessageBox(NULL,"游戏成功","提示",MB_OK);*/
					break;
				}				
			}
		}
	}
	currentTime=m_hge->Timer_GetTime();

	if(currentTime-oldTime>0.5)
	{
		
		it1->Move();
		oldTime=currentTime;
	}
}
void GameRender::UpdateMonNum()
{
	float dt = m_hge->Timer_GetDelta();
	bool killByBomb=false;
	int j=monster.size();
	int i=0;
	int n=0;
	while(i!=j)
	{
		vector<Monster >::iterator it=monster.begin();
		for(int m=0;m<i;m++)
			it++;
	//判断怪物们被炸弹炸死
	while(it!=monster.end())
	{
		if(hasBomb)
		{
			for(int i = 0;i<bombshells.size();i++)
			{
				killByBomb = bombshells[i].isBomb && bombshells[i].booRect.TestPoint(it->currentPos.x,it->currentPos.y);
				if(killByBomb)
				{
				it->blood-=bombshells[i].killPower;
				}
			}	
				if(it->isDead())
					{
						if(it->id==1)
							moneyNum+=6;
						else if(it->id==2)
							moneyNum+=4;
						else if(it->id==3)
							moneyNum+=2;
						else
							moneyNum+=4;
					m_pMusicPlay->Play(MonsterDead1);
					monsterDeadNum++;
					monster.erase(it);
					j--;
					n++;
					break;
					}
		}
		it++;
		i++;
	}
	}
	for(int m=0;m<n;m++)
		AddMonster();
	currentTime2=m_hge->Timer_GetTime();
	if(currentTime2-startTime2>0.1)
	UpdateBombshell(dt);
}
//控制怪的速度。
void GameRender::MonsterMove()
{

	vector<Monster >::iterator it=monster.begin();
	while(it!=monster.end())
	{
		if((it->id==3)&&(FrameNum%1==0))
			it->Move();
		else if(((it->id==2)||(it->id==4))&&(FrameNum%2==0))
			it->Move();
		else if((it->id==1)&&(FrameNum%10==0))
		 it->Move();
		 it++;
	}
	if(FrameNum==10)
	FrameNum=0;
}
void GameRender::UpdateMonster()
{
	float dt = m_hge->Timer_GetDelta();
	bool isErase = false;
	vector<Monster >::iterator it=monster.begin();
	while(it!=monster.end())
	{
	   bool a=it->isHitBound();
		if(a)  
		{
			m_pMusicPlay->Play(HitWallLaugh1);
			if(it->id==1)
				castle.lifeNum--;
			else if(it->id==2)
				castle.lifeNum-=0.5;
			else if(it->id==3)
			{
				if(moneyNum>=2)
					moneyNum-=2;
				else
				castle.lifeNum-=1;
			}
			else
				castle.lifeNum-=1;
			monster.erase(it);
			AddMonster();
			monsterDeadNum++;
			break;
		}
		if(weaponID==0||weaponID==1){
			vector<Bullet >::iterator it1=bombs[weaponID]->bullets.begin();
			while(it1!=bombs[weaponID]->bullets.end())
			{	
		
				if(it->isHit(it1->currentPos))
				{	
					m_pMusicPlay->Play(MonsterDead1);
					if(it->isDead())
					{
						if(it->id==1)
							moneyNum+=6;
						else if(it->id==2)
							moneyNum+=4;
						else if(it->id==3)
							moneyNum+=2;
						else
							moneyNum+=4;
					monsterDeadNum++;
					monster.erase(it);
					AddMonster();
					}
					bombs[weaponID]->bullets.erase(it1);
					isErase = true;
					break;
				}	
				else
				{
					it1++;
				}
			}
			if(isErase)
				break;
		}
		if(weaponID==2)
		{
			for(int i = 0; i<bombs[weaponID]->judgePoints.size();i++)
			{
				POINT p;
				p.x=bombs[weaponID]->judgePoints[i].x;
				p.y=bombs[weaponID]->judgePoints[i].y;
				if(it->isHit(p))
				{
					m_pMusicPlay->Play(MonsterDead1);
					if(it->isDead()){
						if(it->id==1)
							moneyNum+=6;
						else if(it->id==2)
							moneyNum+=4;
						else if(it->id==3)
							moneyNum+=2;
						else
							moneyNum+=4;
						monsterDeadNum++;
						monster.erase(it);
						AddMonster();	
						isErase = true;
						break;
					}
				}

			}
			//bombs[weaponID]->routePoints.clear();
			if(isErase)
				break;
		}
		it++;
	}
	if(weaponID==2)
		bombs[weaponID]->judgePoints.clear();
}

void GameRender::IsAutoCreatMonster()
{
	currentTime=m_hge->Timer_GetTime();
	if(currentTime-oldTime>1)
	{
		AddMonster();
		oldTime=currentTime;
	}
}

//这个游戏状态只更新第一关的状态。
void GameRender::UpdateState()
{
	bool a=(monsterDeadNum==totalMonsterNum)&&(castle.lifeNum!=0);
	if(castle.lifeNum<=0)
	{
		gameState=FAILED;

		/*MessageBox(NULL,"游戏失败","提示",MB_OK);*/
	}
	
	else if((monsterDeadNum==totalMonsterNum)&&(castle.lifeNum!=0))
	{
		float dt = m_hge->Timer_GetDelta();
		gameState=SUCCESS;
		if(hasBomb)
	    {
		UpdateBombshell(dt);
	     }
		for(int i=0;i<3;i++)
			bombs[i]->bullets.clear();
		
		for(int j=0;j<10;j++)
		{
		srand((100)*(j*j));
		POINT startPos;
		startPos.x=rand()%650+80;
		startPos.y=540;
		Monster_Four monster1;
		monster1.setInitPositon(startPos);
		monster1.setBoundary(castle.x1,castle.x2,castle.y);
		monster1.Init(m_hge);
		monster.push_back(monster1);
		}
	}
}
GAME_STATE GameRender::GetState()
{
	return gameState;
}
void GameRender::UpdateBombshell(float dt)
{
	bool isErase = false;
	vector<Bombshell>::iterator it=bombshells.begin();
	while(it!=bombshells.end())
	{
		if((it)->isBomb)
		{
			bombshells.erase(it);
			isErase = true;
			break;
		}
		else
			it++;
	}
}

void  GameRender::StartItemEffect(float x,float y)
{
	item_particle_effect->MoveTo(x,y);
	item_particle_effect->Fire();
}

void GameRender::UpdateItemEffect(float dt)
{
	item_particle_effect->Update(dt);
}

void GameRender::RenderItemEffect()
{
	item_particle_effect->Render();
}
void GameRender::UpdateSecondState()
{
	if((isDeadBoss==true)&&(monster.size()==0))
	{
		gameState=SUCCESS2;
	}
	 if(isDeadBoss==false&&bosses[0].isHitBound())
		 gameState=FAILED;
	if(castle.lifeNum==0)
	{
		gameState=FAILED;
	}
}
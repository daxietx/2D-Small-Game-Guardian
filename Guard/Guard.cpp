#include "stdafx.h"
#include "GameManager.h"

//全局对象
HGE *hge = 0;
CGameManager *pGameManager = NULL;


//帧函数
bool FrameFunc()
{
	return pGameManager->FrameFunc();
}

//绘制函数
bool RenderFunc()
{
	pGameManager->RenderFunc();
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "Guard.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Guard");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 850);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_FPS,100);

	if(hge->System_Initiate())
	{
		pGameManager = CGameManager::GetInstance();
		pGameManager->Init(hge);
		
		// Let's rock now!
		hge->System_Start();

		// Delete created objects and free loaded resources
		delete pGameManager;
	}
	else
	{
		char *a = hge->System_GetErrorMessage();
		MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", 0);
	}

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}

/******************************************************************************/
/*!
file    GameOverState.cpp
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

The GameOver state is really used just to quit.  Since I have an splash
state, I make sure to have an quit state to close resources even though for
the demo it is just used for debug stuff.
*/
/******************************************************************************/
#include "GameWinState.h"

#include "WEDebugTools.h"
#include "WEInput.h"
#include "WEGraphics.h"
#include "WEStateManager.h"
#include "WEApplication.h"
#include "WEMtx44.h"
#include "WEVec2.h"
#include "WEIntersection.h"

#include "DemoStates.h"
#include "GameTypes.h"

namespace
{
	struct GameWinData
	{
		int gameWinTexture;
	};
	GameWinData gw_data;
}

/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void GameWinLoad(void)
{
	gw_data.gameWinTexture = WEGraphics::LoadTexture("Textures\\YouWin.tga");
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.
*/
/******************************************************************************/
void GameWinInit(void)
{
	/*The amount of red in the logo texture*/
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.

*/
/******************************************************************************/
void GameWinUpdate(float)
{
	if (WEInput::IsTriggered(WE_R))
		WEStateManager::SetNextState(DS_MAIN);
	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::Quit();
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	WEGraphics::StartDraw();
	WEGraphics::SetToOrtho();
	WEGraphics::SetTextureColor(255,255,255,255);
	WEGraphics::SetTexture(gw_data.gameWinTexture);
	WEGraphics::SetBackgroundColor(255.f, 255.f, 255.f);

	WEMtx44::MakeTransform(transform, (float)windowWidth, (float)windowHeight, 0,
		windowWidth / 2.0f, windowHeight / 2.0f, 0);
	WEGraphics::Draw(transform);

	WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.

*/
/******************************************************************************/
void GameWinShutdown(void)
{
	/*I am now done with the console so I can detroy it.*/
	WEDEBUG_DESTROY_CONSOLE();
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.

*/
/******************************************************************************/
void GameWinUnload(void)
{
	WEGraphics::UnloadTexture(gw_data.gameWinTexture);
}
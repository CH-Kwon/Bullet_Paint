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
#include "GameOverState.h"
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
	struct GameOverData
	{
		int exitTexture;
		int restartTexture;
		int gameOverTexture;
		Button exit;
		Button restart;
	};
	GameOverData go_data;
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
void GameOverLoad(void)
{
	go_data.gameOverTexture = WEGraphics::LoadTexture("Textures\\GameOver.tga");
	go_data.restartTexture = WEGraphics::LoadTexture("Textures\\Restart.tga");
	go_data.exitTexture = WEGraphics::LoadTexture("Textures\\QQuit.tga");
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.
*/
/******************************************************************************/
void GameOverInit(void)
{
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	WEGraphics::SetBackgroundColor(255.f, 255.f, 255.f);

	//start button
	go_data.restart.pos.x = windowWidth / 2;
	go_data.restart.pos.y = windowHeight / 1.5f;
	go_data.restart.texture = go_data.restartTexture;
	go_data.restart.scale.x = windowWidth / 5;
	go_data.restart.scale.y = windowHeight / 7;

	//quit button
	go_data.exit.pos.x = windowWidth / 2;
	go_data.exit.pos.y = windowHeight / 3;
	go_data.exit.texture = go_data.exitTexture;
	go_data.exit.scale.x = windowWidth / 6;
	go_data.exit.scale.y = windowHeight / 8;

	

	/*The amount of red in the logo texture*/
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.

*/
/******************************************************************************/
void GameOverUpdate(float)
{
	WEMtx44 transform;
	int windowWidth = WEApplication::GetWidth();
	int windowHeight = WEApplication::GetHeight();

	//Exit game
	/*if (WEInput::IsTriggered(WE_Q))
	WEStateManager::Quit();

	//Restart game
	if (WEInput::IsTriggered(WE_R))
	WEStateManager::SetNextState(DS_COOL);*/

	WEGraphics::StartDraw();
	WEGraphics::SetToOrtho();
	WEGraphics::SetTexture(go_data.gameOverTexture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform, (float)windowWidth, (float)windowHeight, 0,
		windowWidth / 2.0f, windowHeight / 2.0f, 0.0f);
	WEGraphics::Draw(transform);


	WEGraphics::SetTexture(go_data.restartTexture);
	WEMtx44::MakeTransform(transform,
		go_data.restart.scale.x, go_data.restart.scale.y, 0.f,
		go_data.restart.pos.x, go_data.restart.pos.y, 0.f);
	WEGraphics::Draw(transform);


	WEGraphics::SetTexture(go_data.exitTexture);
	WEMtx44::MakeTransform(transform,
		go_data.exit.scale.x, go_data.exit.scale.y, 0.f,
		go_data.exit.pos.x, go_data.exit.pos.y, 0.f);
	WEGraphics::Draw(transform);

	if (WEInput::IsTriggered(WE_MOUSE_LEFT))
	{
		WEVec2 mouse;
		WEInput::GetMouse(mouse);
		if (WEIntersection::PointRect(mouse, go_data.restart.pos,
			go_data.restart.scale.x, go_data.restart.scale.y))
		{
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::PointRect(mouse, go_data.exit.pos,
			go_data.exit.scale.x, go_data.exit.scale.y))
		{
			WEStateManager::Quit();
		}
	}



	WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.

*/
/******************************************************************************/
void GameOverShutdown(void)
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
void GameOverUnload(void)
{
	WEGraphics::UnloadTexture(go_data.gameOverTexture);
	WEGraphics::UnloadTexture(go_data.exitTexture);
	WEGraphics::UnloadTexture(go_data.restartTexture);
}

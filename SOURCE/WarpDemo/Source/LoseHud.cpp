/******************************************************************************/
/*!
file    LoseHud.cpp
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/5/31

The LoseHud is really used for Lose condition HUD.  
*/
/******************************************************************************/
#include "LoseHud.h"

#include "WEDebugTools.h"
#include "WEIntersection.h"
#include "WEApplication.h"
#include "WEMath.h"
#include "WEVec2.h"
#include "WEMtx44.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEInput.h"

#include "DemoStates.h"
#include "GameTypes.h"
#include <cstdio>
#define WE_MAX_TIME 5.f

class Lose
{
public:
	int HudBoxTexture;
	int quitTexture;
	int restartTexture;
	int selectTexture;
	int LoseTexture;
	Button restart;
	Button quit;
	Button select;
	bool isFullScreen;
};
static Lose s_data;

namespace
{
	int Xcount;
	const int Textcount = 2;
}
/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void LoseHUD::LoseHudLoad(void)
{
	s_data.HudBoxTexture = WEGraphics::LoadTexture("Textures\\HudBox.tga");
	s_data.quitTexture = WEGraphics::LoadTexture("Textures\\HudQuit.tga");
	s_data.restartTexture = WEGraphics::LoadTexture("Textures\\HudRestart.tga");
	s_data.selectTexture = WEGraphics::LoadTexture("Textures\\Select.tga");
	s_data.LoseTexture = WEGraphics::LoadTexture("Textures\\losehud.tga");
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void LoseHUD::LoseHudInit(void)
{
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	Xcount = 0;
	//restart button
	s_data.restart.pos.x = windowWidth / 2;
	s_data.restart.pos.y =  windowHeight / 2.0f;
	s_data.restart.texture = s_data.restartTexture;
	s_data.restart.scale.x = windowWidth / 7;
	s_data.restart.scale.y = windowHeight / 7;

	//quit button
	s_data.quit.pos.x = windowWidth / 2;
	s_data.quit.pos.y = windowHeight / 3.0f;
	s_data.quit.texture = s_data.quitTexture;
	s_data.quit.scale.x = windowWidth / 7;
	s_data.quit.scale.y = windowHeight / 7;

	//select button
	s_data.select.pos.x = windowWidth / 2.5f;
	s_data.select.pos.y = windowHeight / 2.0f;
	s_data.select.texture = s_data.selectTexture;
	s_data.select.scale.x = windowWidth / 7;
	s_data.select.scale.y = windowHeight / 7;

	s_data.isFullScreen = false;
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void LoseHUD::LoseHudUpdate(float)
{
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	WEGraphics::SetToOrtho();

	/*Set the image to draw*/
	WEGraphics::SetTexture(s_data.HudBoxTexture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform, (float)windowWidth / 2.0f, (float)windowHeight / 1.2f, 0,
		windowWidth / 2.0f, windowHeight / 2.0f, 0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.selectTexture);
	WEMtx44::MakeTransform(transform,
		s_data.select.scale.x, s_data.select.scale.y, 0.f,
		s_data.select.pos.x, s_data.select.pos.y, 0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.restartTexture);
	WEMtx44::MakeTransform(transform,
		s_data.restart.scale.x, s_data.restart.scale.y, 0.f,
		s_data.restart.pos.x, s_data.restart.pos.y, 0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.quitTexture);
	WEMtx44::MakeTransform(transform,
		s_data.quit.scale.x, s_data.quit.scale.y, 0.f,
		s_data.quit.pos.x, s_data.quit.pos.y, 0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.LoseTexture);
	WEMtx44::MakeTransform(transform,
		windowWidth / 2.5f, windowHeight / 7.0f, 0.f,
		windowWidth / 2, windowHeight / 1.2f, 0);
	WEGraphics::Draw(transform);
	/* Player moving */
	if (Xcount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_UP))
		{
			s_data.select.pos.y += windowHeight / 6;
			Xcount--;
		}
	}
	if (Xcount != Textcount - 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_DOWN))
		{
			s_data.select.pos.y -= windowHeight / 6;
			Xcount++;
		}
	}

	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();
	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	/* Button Reaction */
	extern int LevelNumber;
	if (WEInput::IsTriggered(WE_SPACE))
	{
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.restart.pos,
			s_data.restart.scale.x, s_data.restart.scale.y))
		{
			WEStateManager::Restart();
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.quit.pos,
			s_data.quit.scale.x, s_data.quit.scale.y))
		{
			WEStateManager::SetNextState(DS_SELECTLEVEL);
		}
	}

	if (WEInput::IsTriggered(WE_MOUSE_LEFT))
	{
		if (WEIntersection::PointRect(mouse, s_data.restart.pos,
			s_data.restart.scale.x, s_data.restart.scale.y))
		{
			WEStateManager::Restart();
		}
		if (WEIntersection::PointRect(mouse, s_data.quit.pos,
			s_data.quit.scale.x, s_data.quit.scale.y))
		{
			WEStateManager::SetNextState(DS_MAIN);
		}
	}

	if (WEInput::IsTriggered(WE_F))
	{
		s_data.isFullScreen = !s_data.isFullScreen;
		WEApplication::SetFullScreen(s_data.isFullScreen);
	}
}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void LoseHUD::LoseHudShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void LoseHUD::LoseHudUnload(void)
{
	WEGraphics::UnloadTexture(s_data.HudBoxTexture);
	WEGraphics::UnloadTexture(s_data.quitTexture);
	WEGraphics::UnloadTexture(s_data.restartTexture);
	WEGraphics::UnloadTexture(s_data.selectTexture);
	WEGraphics::UnloadTexture(s_data.LoseTexture);
}

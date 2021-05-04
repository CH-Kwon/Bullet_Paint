/******************************************************************************/
/*!
file    WinHud.cpp
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\par  
\date   2017/5/27

\breif The WinHud is used for Win condition HUD.
*/
/******************************************************************************/
#include "WinHud.h"

#include "WEDebugTools.h"
#include "WEIntersection.h"
#include "WEApplication.h"
#include "WEMath.h"
#include "WEVec2.h"
#include "WEMtx44.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEInput.h"

#include "Star.h"
#include "DemoStates.h"
#include "GameTypes.h"
#include <cstdio>
#define WE_MAX_TIME 5.f

class Win
{
public:
		int HudBoxTexture;
		int quitTexture;
		int nextTexture;
		int restartTexture;
		int selectTexture;
		int winTexture;
		Button restart;
		Button next;
		Button quit;
		Button select;
		bool isFullScreen;
		int Star_ID;
};
static Win s_data;

namespace
{
	int Xcount;
	const int Textcount = 3;
	const float starPos = 15;
	const float starScale = 70;
}
/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void WinHud::WinHudLoad(void)
{
	s_data.HudBoxTexture = WEGraphics::LoadTexture("Textures\\HudBox.tga");
	s_data.quitTexture = WEGraphics::LoadTexture("Textures\\HudQuit.tga");
	s_data.nextTexture = WEGraphics::LoadTexture("Textures\\Hudnext.tga");
	s_data.restartTexture = WEGraphics::LoadTexture("Textures\\HudRestart.tga");
	s_data.selectTexture = WEGraphics::LoadTexture("Textures\\Select.tga");
	s_data.winTexture = WEGraphics::LoadTexture("Textures\\winhud.tga");
	s_data.Star_ID = WEGraphics::LoadTexture("Textures\\star.tga");
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void WinHud::WinHudInit(void)
{
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	Xcount = 0;
	//restart button
	s_data.restart.pos.x = windowWidth / 2;
	s_data.restart.pos.y = windowHeight / 2.0f;
	s_data.restart.texture = s_data.restartTexture;
	s_data.restart.scale.x = windowWidth / 7;
	s_data.restart.scale.y = windowHeight / 7;

	//quit button
	s_data.quit.pos.x = windowWidth / 2;
	s_data.quit.pos.y = windowHeight / 3.0f;
	s_data.quit.texture = s_data.quitTexture;
	s_data.quit.scale.x = windowWidth / 7;
	s_data.quit.scale.y = windowHeight / 7;

	//next button
	s_data.next.pos.x = windowWidth / 2;
	s_data.next.pos.y = windowHeight / 1.5f;
	s_data.next.texture = s_data.nextTexture;
	s_data.next.scale.x = windowWidth / 7;
	s_data.next.scale.y = windowHeight / 7;

	//select button
	s_data.select.pos.x = windowWidth / 2.5f;
	s_data.select.pos.y = windowHeight / 1.5f;
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
void WinHud::WinHudUpdate(float)
{
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	WEGraphics::SetToOrtho();

	/*Set the image to draw*/
	WEGraphics::SetTexture(s_data.HudBoxTexture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform, (float)windowWidth/2.0f, (float)windowHeight/1.2f, 0,
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

	WEGraphics::SetTexture(s_data.nextTexture);
	WEMtx44::MakeTransform(transform,
		s_data.next.scale.x, s_data.next.scale.y, 0.f,
		s_data.next.pos.x, s_data.next.pos.y, 0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.winTexture);
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
	if (Xcount != Textcount -1)
	{
		if (WEInput::IsTriggered(WE_ARROW_DOWN))
		{
			s_data.select.pos.y -= windowHeight / 6;
			Xcount++;
		}
	}
	WEVec2 pos;
	pos.Set(windowWidth / 2.5f, windowHeight / 4.6f );
	/* Drawing Star */
	for (int i = 0; i < Star::StarCount(); ++i)
	{
		WEGraphics::SetTexture(s_data.Star_ID);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		WEMtx44::MakeTransform(transform,
			starScale, starScale,
			0,
			pos.x, pos.y , 0);
		WEGraphics::Draw(transform);
		pos.x += windowWidth / 10;
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
			WEStateManager::SetNextState(DS_MAIN);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.next.pos,
			s_data.next.scale.x, s_data.next.scale.y))
		{
			LevelNumber = LevelNumber + 1;
			WEStateManager::Restart();
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
			WEStateManager::SetNextState(DS_SELECTLEVEL);
		}
		if (WEIntersection::PointRect(mouse, s_data.next.pos,
			s_data.next.scale.x, s_data.next.scale.y))
		{
			LevelNumber = LevelNumber + 1;
			WEStateManager::Restart();
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
void WinHud::WinHudShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void WinHud::WinHudUnload(void)
{
	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(s_data.HudBoxTexture);
	WEGraphics::UnloadTexture(s_data.nextTexture);
	WEGraphics::UnloadTexture(s_data.quitTexture);
	WEGraphics::UnloadTexture(s_data.restartTexture);
	WEGraphics::UnloadTexture(s_data.selectTexture);
	WEGraphics::UnloadTexture(s_data.winTexture);
	WEGraphics::UnloadTexture(s_data.Star_ID);
}
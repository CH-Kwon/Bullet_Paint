/******************************************************************************/
/*!
file    SetHud.cpp
\author Chiho Kwon
\par    email: erpo0811@gmail.com
\par    class: GAM150
\date   2016/5/4

\breif
SetHud state is used to set hud(restart, level select button, button) to let
player know.
*/
/******************************************************************************/
#include "SetHud.h"

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
#define WE_MAX_TIME 5.f;

class Set
{
public:
	int restartTexture;
	int levelTexture;
	int colorTexture;
	int maxbulletTexture;
	int bulletTexture;
	
	Button restart;
	Button level;

	bool isFullScreen;
};
static Set s_data;

/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void SetHud::SetHudLoad(void)
{
	s_data.levelTexture = WEGraphics::LoadTexture("Textures\\level select.tga");
	s_data.restartTexture = WEGraphics::LoadTexture("Textures\\restart1.tga");
	s_data.colorTexture = WEGraphics::LoadTexture("Textures\\colorhud.tga");
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void SetHud::SetHudInit(void)
{
	//restart button
	s_data.restart.pos.x = 100;
	s_data.restart.pos.y = 230;
	s_data.restart.texture = s_data.restartTexture;
	s_data.restart.scale.x = 180;
	s_data.restart.scale.y = 120;

	//level select button
	s_data.level.pos.x = 100;
	s_data.level.pos.y = 80;
	s_data.level.texture = s_data.levelTexture;
	s_data.level.scale.x = 180;
	s_data.level.scale.y = 120;



	s_data.isFullScreen = false;

}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void SetHud::SetHudUpdate(float)
{ 
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	WEMtx44 transform;

	WEGraphics::SetToOrtho();

	/*Set the image to draw*/
	WEGraphics::SetTextureColor(255, 255, 255,255);

	
	WEGraphics::SetTexture(s_data.restartTexture);
	WEMtx44::MakeTransform(transform,
		s_data.restart.scale.x, s_data.restart.scale.y, 0.f,
		s_data.restart.pos.x, s_data.restart.pos.y, 0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.levelTexture);
	WEMtx44::MakeTransform(transform,
		s_data.level.scale.x, s_data.level.scale.y, 0.f,
		s_data.level.pos.x, s_data.level.pos.y, 0);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.colorTexture);
	WEMtx44::MakeTransform(transform, windowWidth/12,
	windowHeight/2.0f, 0, windowWidth/12, windowHeight/1.5f, 0);
	WEGraphics::Draw(transform);

	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	//WEGraphics::ConvertWorldToScreen(mouse.x, mouse.y);

	if (WEInput::IsTriggered(WE_MOUSE_LEFT))
	{
		if (WEIntersection::PointRect(mouse, s_data.restart.pos,
			s_data.restart.scale.x, s_data.restart.scale.y))
		{
			WEStateManager::Restart();
		}

		if (WEIntersection::PointRect(mouse, s_data.level.pos,
			s_data.level.scale.x, s_data.level.scale.y))
		{
			WEStateManager::SetNextState(DS_SELECTLEVEL);
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
void SetHud::SetHudShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void SetHud::SetHudUnload(void)
{
	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(s_data.levelTexture);
	WEGraphics::UnloadTexture(s_data.restartTexture);
	WEGraphics::UnloadTexture(s_data.colorTexture);
}
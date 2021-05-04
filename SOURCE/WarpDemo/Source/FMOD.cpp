/******************************************************************************/
/*!
file    FMOD.cpp
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date 2017/05/16

\breif
FMOD splash state.
*/
/******************************************************************************/
#include "FMOD.h"

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
	struct FmodData
	{
		int FmodTexture;
	};
	FmodData fm_data;
	unsigned char alpha;
}
/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void FMODLoad(void)
{
	fm_data.FmodTexture = WEGraphics::LoadTexture("Textures\\Fmod.tga");
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void FMODInit(void)
{
	alpha = 255;
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void FMODUpdate(float /*dt*/)
{
	--alpha;
	if (alpha == 0)
		WEStateManager::SetNextState(DS_MAIN);
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	WEGraphics::StartDraw();
	WEGraphics::SetToOrtho();
	WEGraphics::SetTextureColor(255, 255, 255, alpha);
	WEGraphics::SetTexture(fm_data.FmodTexture);
	WEGraphics::SetBackgroundColor(255.f, 255.f, 255.f);
	if (WEInput::IsAnyTriggered())
		WEStateManager::SetNextState(DS_MAIN);
	WEMtx44::MakeTransform(transform, (float)windowWidth, (float)windowHeight, 0,
		windowWidth / 2.0f, windowHeight / 2.0f, 0);
	WEGraphics::Draw(transform);

	WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void FMODShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void FMODUnload(void)
{
	WEGraphics::UnloadTexture(fm_data.FmodTexture);
}

/******************************************************************************/
/*!
file    DigipenLogo.cpp
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/3/29

\brief
DigipenLogo state is to show digipen logo at the first of game
*/
/******************************************************************************/
#include "DigipenLogo.h"

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
	struct DigipenLogoData
	{
		int DigipenTexture;
	};
	DigipenLogoData dl_data;
	unsigned char alpha;
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
void DigipenLogoLoad(void)
{
	dl_data.DigipenTexture = WEGraphics::LoadTexture("Textures\\Digipen.tga");
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.
*/
/******************************************************************************/
void DigipenLogoInit(void)
{
	alpha = 0;
	/*The amount of red in the logo texture*/
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.

*/
/******************************************************************************/
void DigipenLogoUpdate(float)
{
	++alpha;
	if(alpha == 255)
		WEStateManager::SetNextState(DS_FMOD);
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	WEGraphics::StartDraw();
	WEGraphics::SetToOrtho();
	WEGraphics::SetTextureColor(255,255,255,alpha);
	WEGraphics::SetTexture(dl_data.DigipenTexture);
	WEGraphics::SetBackgroundColor(255.f, 255.f, 255.f);
	if (WEInput::IsAnyTriggered())
		WEStateManager::SetNextState(DS_FMOD);
	WEMtx44::MakeTransform(transform, (float)windowWidth/1.5f, (float)windowHeight/2, 0,
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
void DigipenLogoShutdown(void)
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
void DigipenLogoUnload(void)
{
	WEGraphics::UnloadTexture(dl_data.DigipenTexture);
}

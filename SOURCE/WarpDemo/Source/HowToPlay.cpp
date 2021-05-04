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
	struct HowToPlay
	{
		int howtoplayTexture;
	};
	HowToPlay ht_data;
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
void HowToPlayLoad(void)
{
	ht_data.howtoplayTexture = WEGraphics::LoadTexture("Textures\\howtoplay.tga");
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.
*/
/******************************************************************************/
void HowToPlayInit(void)
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
void HowToPlayUpdate(float)
{

	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	if (WEInput::IsAnyTriggered())
		WEStateManager::SetNextState(DS_MAIN);

	WEGraphics::StartDraw();
	WEGraphics::SetToOrtho();
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEGraphics::SetTexture(ht_data.howtoplayTexture);
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
void HowToPlayShutdown(void)
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
void HowToPlayUnload(void)
{
	WEGraphics::UnloadTexture(ht_data.howtoplayTexture);
}

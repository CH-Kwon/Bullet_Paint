/******************************************************************************/
/*!
file    Credit.cpp
\author Chiho Kwon
\par    email: erpo0811@gmail.com
\par    class: GAM150
\date   2016/6/1

\breif
This state is used to show credit in main menu
*/
/******************************************************************************/
#include "Credit.h"

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
	struct Credit
	{
		int CreditTexture;
	};
	Credit cr_data;
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
void CreditLoad(void)
{
	cr_data.CreditTexture = WEGraphics::LoadTexture("Textures\\Credit.tga");
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init
state, I make sure to have an quit state even though for the demo I don't
do anything here.
*/
/******************************************************************************/
void CreditInit(void)
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
void CreditUpdate(float)
{

	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();

	if (WEInput::IsAnyTriggered())
		WEStateManager::SetNextState(DS_MAIN);

	WEGraphics::StartDraw();
	WEGraphics::SetToOrtho();
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEGraphics::SetTexture(cr_data.CreditTexture);
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
void CreditShutdown(void)
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
void CreditUnload(void)
{
	WEGraphics::UnloadTexture(cr_data.CreditTexture);
}

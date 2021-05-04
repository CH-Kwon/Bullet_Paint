/******************************************************************************/
/*!
file    ShowLevel.cpp
\author Chiho Kwon
\par    email: erpo0811@gmail.com
\par    class: GAM150
\date   2016/5/5

\breif
ShowLevel state is to show that what level player is doing
*/
/******************************************************************************/
#include "ShowLevel.h"

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
#define EASY_LEVEL 6
#define NORMAL_LEVEL 11
#define HARD_LEVEL 16
#define WE_MAX_TIME 5.f;
extern int LevelNumber;

class Show
{
public:
	int easyTexture;
	int normalTexture;
	int hardTexture;
	int level1_Texture;
	int level2_Texture;
	int level3_Texture;
	int level4_Texture;
	int level5_Texture;
	int level2_1_Texture;
	int level2_2_Texture;
	int level2_3_Texture;
	int level2_4_Texture;
	int level2_5_Texture;
	int level3_1_Texture;
	int level3_2_Texture;
	int level3_3_Texture;
	int level3_4_Texture;
	int level3_5_Texture;
	int bullet_Texture;
	int max_bullet_Texture;

	bool isFullScreen;
};
static Show s_data;
/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void ShowLevel::ShowLevelLoad(void)
{
	s_data.easyTexture = WEGraphics::LoadTexture("Textures\\easylevel.tga");
	s_data.normalTexture = WEGraphics::LoadTexture("Textures\\normallevel.tga");
	s_data.hardTexture = WEGraphics::LoadTexture("Textures\\hardlevel.tga");
	s_data.level1_Texture = WEGraphics::LoadTexture("Textures\\level1hud.tga");
	s_data.level2_Texture = WEGraphics::LoadTexture("Textures\\level2hud.tga");
	s_data.level3_Texture = WEGraphics::LoadTexture("Textures\\level3hud.tga");
	s_data.level4_Texture = WEGraphics::LoadTexture("Textures\\level4hud.tga");
	s_data.level5_Texture = WEGraphics::LoadTexture("Textures\\level5hud.tga");
	s_data.level2_1_Texture = WEGraphics::LoadTexture("Textures\\level2_1hud.tga");
	s_data.level2_2_Texture = WEGraphics::LoadTexture("Textures\\level2_2hud.tga");
	s_data.level2_3_Texture = WEGraphics::LoadTexture("Textures\\level2_3hud.tga");
	s_data.level2_4_Texture = WEGraphics::LoadTexture("Textures\\level2_4hud.tga");
	s_data.level2_5_Texture = WEGraphics::LoadTexture("Textures\\level2_5hud.tga");
	s_data.level3_1_Texture = WEGraphics::LoadTexture("Textures\\level3_1hud.tga");
	s_data.level3_2_Texture = WEGraphics::LoadTexture("Textures\\level3_2hud.tga");
	s_data.level3_3_Texture = WEGraphics::LoadTexture("Textures\\level3_3hud.tga");
	s_data.level3_4_Texture = WEGraphics::LoadTexture("Textures\\level3_4hud.tga");
	s_data.level3_5_Texture = WEGraphics::LoadTexture("Textures\\level3_5hud.tga");
	s_data.bullet_Texture = WEGraphics::LoadTexture("Textures\\bullet.tga");
	s_data.max_bullet_Texture = WEGraphics::LoadTexture("Textures\\maxbullet.tga");
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void ShowLevel::ShowLevelInit(void)
{
	//float windowWidth = (float)WEApplication::GetWidth();
	//float windowHeight = (float)WEApplication::GetHeight();

	s_data.isFullScreen = false;

}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void ShowLevel::ShowLevelUpdate(float)
{
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	WEMtx44 transform;

	WEGraphics::SetToOrtho();
	/*Set the image to draw*/
	WEGraphics::SetTextureColor(255, 255, 255, 255);

	if (LevelNumber < EASY_LEVEL)
	{
		WEGraphics::SetTexture(s_data.easyTexture);
		WEMtx44::MakeTransform(transform, windowWidth / 7,
			windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.05f, 0);
		WEGraphics::Draw(transform);

		if (LevelNumber == 1)
		{
			WEGraphics::SetTexture(s_data.level1_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 20, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 2)
		{
			WEGraphics::SetTexture(s_data.level2_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 3)
		{
			WEGraphics::SetTexture(s_data.level3_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 4)
		{
			WEGraphics::SetTexture(s_data.level4_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 5)
		{
			WEGraphics::SetTexture(s_data.level5_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}
	}
	else if (LevelNumber < NORMAL_LEVEL)
	{
		WEGraphics::SetTexture(s_data.normalTexture);
		WEMtx44::MakeTransform(transform, windowWidth / 6,
			windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.05f, 0);
		WEGraphics::Draw(transform);

		if (LevelNumber == 6)
		{
			WEGraphics::SetTexture(s_data.level2_1_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 7)
		{
			WEGraphics::SetTexture(s_data.level2_2_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 8)
		{
			WEGraphics::SetTexture(s_data.level2_3_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 9)
		{
			WEGraphics::SetTexture(s_data.level2_4_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 10)
		{
			WEGraphics::SetTexture(s_data.level2_5_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}
	}
	else if (LevelNumber < HARD_LEVEL)
	{
		WEGraphics::SetTexture(s_data.hardTexture);
		WEMtx44::MakeTransform(transform, windowWidth / 8,
			windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.05f, 0);
		WEGraphics::Draw(transform);

		if (LevelNumber == 11)
		{
			WEGraphics::SetTexture(s_data.level3_1_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 12)
		{
			WEGraphics::SetTexture(s_data.level3_2_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 13)
		{
			WEGraphics::SetTexture(s_data.level3_3_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 14)
		{
			WEGraphics::SetTexture(s_data.level3_4_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}

		if (LevelNumber == 15)
		{
			WEGraphics::SetTexture(s_data.level3_5_Texture);
			WEMtx44::MakeTransform(transform, windowWidth / 8,
				windowHeight / 16, 0, windowWidth / 2, windowHeight / 1.15f, 0);
			WEGraphics::Draw(transform);
		}
	}

	WEGraphics::SetTexture(s_data.bullet_Texture);
	WEMtx44::MakeTransform(transform,
		windowWidth / 12, windowHeight / 22, 0,
		windowWidth / 1.19f, windowHeight / 2.7f, 0.f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.max_bullet_Texture);
	WEMtx44::MakeTransform(transform,
		windowWidth / 8.5f, windowHeight / 22, 0,
		windowWidth / 1.17f, windowHeight / 2.2f, 0.f);
	WEGraphics::Draw(transform);
	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void ShowLevel::ShowLevelShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void ShowLevel::ShowLevelUnload(void)
{
	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(s_data.easyTexture);
	WEGraphics::UnloadTexture(s_data.normalTexture);
	WEGraphics::UnloadTexture(s_data.hardTexture);
	WEGraphics::UnloadTexture(s_data.level1_Texture);
	WEGraphics::UnloadTexture(s_data.level2_Texture);
	WEGraphics::UnloadTexture(s_data.level3_Texture);
	WEGraphics::UnloadTexture(s_data.level4_Texture);
	WEGraphics::UnloadTexture(s_data.level5_Texture);
	WEGraphics::UnloadTexture(s_data.level2_1_Texture);
	WEGraphics::UnloadTexture(s_data.level2_2_Texture);
	WEGraphics::UnloadTexture(s_data.level2_3_Texture);
	WEGraphics::UnloadTexture(s_data.level2_4_Texture);
	WEGraphics::UnloadTexture(s_data.level2_5_Texture);
	WEGraphics::UnloadTexture(s_data.level3_1_Texture);
	WEGraphics::UnloadTexture(s_data.level3_2_Texture);
	WEGraphics::UnloadTexture(s_data.level3_3_Texture);
	WEGraphics::UnloadTexture(s_data.level3_4_Texture);
	WEGraphics::UnloadTexture(s_data.level3_5_Texture);
	WEGraphics::UnloadTexture(s_data.bullet_Texture);
	WEGraphics::UnloadTexture(s_data.max_bullet_Texture);
}
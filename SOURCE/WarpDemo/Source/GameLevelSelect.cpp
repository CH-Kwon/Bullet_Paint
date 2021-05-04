/******************************************************************************/
/*!
file    GameLevel2.cpp
\author Chiho Kwon
\par    email: erpo0811@gmail.com
\par    class: GAM150
\date   2017/4/29
All content © 2017 DigiPen (USA) Corporation, all rights reserved.

The GameLevelSelect state is used to select levels in each mode.
*/
/******************************************************************************/
#include "GameLevelSelect.h"

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
/*Make a struct for my shared state data*/
namespace
{
	struct InitData
	{
		int level1Texture;
		int level2Texture;
		int level3Texture;
		int level4Texture;
		int level5Texture;
		int level2_1Texture;
		int level2_2Texture;
		int level2_3Texture;
		int level2_4Texture;
		int level2_5Texture;
		int level3_1Texture;
		int level3_2Texture;
		int level3_3Texture;
		int level3_4Texture;
		int level3_5Texture;
		int menuTexture;
		int selectTexture;
		int easyTexture;
		int hardTexture;
		int normalTexture;
		Button level1;
		Button level2;
		Button level3;
		Button level4;
		Button level5;
		Button level2_1;
		Button level2_2;
		Button level2_3;
		Button level2_4;
		Button level2_5;
		Button level3_1;
		Button level3_2;
		Button level3_3;
		Button level3_4;
		Button level3_5;
		Button select;
		Button easy;
		Button hard;
		Button normal;
	};
	struct GameLevelSelectData
	{
		bool isFullScreen;
	};

	/*Create a static variable for data so it can't be used in other files.*/
	InitData s_data;

	int Xcount;
	int Ycount;
	const int XposCount = 3;
	const int YposCount = 5;
	const int xSize = 75;
}

static GameLevelSelectData stateData;
int LevelNumber = 0;
/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void GameLevelSelectLoad(void)
{
	/*Load the only texture we need for this state*/
	s_data.level1Texture = WEGraphics::LoadTexture("Textures\\level1.tga");
	s_data.level2Texture = WEGraphics::LoadTexture("Textures\\level2.tga");
	s_data.level3Texture = WEGraphics::LoadTexture("Textures\\level3.tga");
	s_data.level4Texture = WEGraphics::LoadTexture("Textures\\level4.tga");
	s_data.level5Texture = WEGraphics::LoadTexture("Textures\\level5.tga");
	s_data.level2_1Texture = WEGraphics::LoadTexture("Textures\\level2_1.tga");
	s_data.level2_2Texture = WEGraphics::LoadTexture("Textures\\level2_2.tga");
	s_data.level2_3Texture = WEGraphics::LoadTexture("Textures\\level2_3.tga");
	s_data.level2_4Texture = WEGraphics::LoadTexture("Textures\\level2_4.tga");
	s_data.level2_5Texture = WEGraphics::LoadTexture("Textures\\level2_5.tga");
	s_data.level3_1Texture = WEGraphics::LoadTexture("Textures\\level3_1.tga");
	s_data.level3_2Texture = WEGraphics::LoadTexture("Textures\\level3_2.tga");
	s_data.level3_3Texture = WEGraphics::LoadTexture("Textures\\level3_3.tga");
	s_data.level3_4Texture = WEGraphics::LoadTexture("Textures\\level3_4.tga");
	s_data.level3_5Texture = WEGraphics::LoadTexture("Textures\\level3_5.tga");
	s_data.menuTexture = WEGraphics::LoadTexture("Textures\\selectlevel.tga");
	s_data.selectTexture = WEGraphics::LoadTexture("Textures\\Select.tga");
	s_data.easyTexture = WEGraphics::LoadTexture("Textures\\easylevel.tga");
	s_data.normalTexture = WEGraphics::LoadTexture("Textures\\normallevel.tga");
	s_data.hardTexture = WEGraphics::LoadTexture("Textures\\hardlevel.tga");


	/*All drawing in this state is in screen space*/
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void GameLevelSelectInit(void)
{
	WEDEBUG_CREATE_CONSOLE();
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	WEGraphics::SetBackgroundColor(0.0f, 0.f, 0.f);
	const float width = windowWidth / 6.3f;
	const float height = windowHeight / 7;
	Xcount = 0;
	Ycount = 0;


	//set level 1
	s_data.level1.pos.x = windowWidth / 5.5f;
	s_data.level1.pos.y = windowHeight / 1.4f;
	s_data.level1.texture = s_data.level1Texture;
	s_data.level1.scale.x = windowWidth / 10;
	s_data.level1.scale.y = windowHeight / 10;

	//set level 2
	s_data.level2.pos.x = windowWidth / 5.5f;
	s_data.level2.pos.y = s_data.level1.pos.y - height;
	s_data.level2.texture = s_data.level2Texture;
	s_data.level2.scale.x = windowWidth / 10;
	s_data.level2.scale.y = windowHeight / 10;

	//set level 3
	s_data.level3.pos.x = windowWidth / 5.5f;
	s_data.level3.pos.y = s_data.level2.pos.y - height;
	s_data.level3.texture = s_data.level3Texture;
	s_data.level3.scale.x = windowWidth / 10;
	s_data.level3.scale.y = windowHeight / 10;

	//set level 4
	s_data.level4.pos.x = windowWidth / 5.5f;
	s_data.level4.pos.y = s_data.level3.pos.y - height;
	s_data.level4.texture = s_data.level4Texture;
	s_data.level4.scale.x = windowWidth / 10;
	s_data.level4.scale.y = windowHeight / 10;

	//set level 5
	s_data.level5.pos.x = windowWidth / 5.5f;
	s_data.level5.pos.y = s_data.level4.pos.y - height;
	s_data.level5.texture = s_data.level5Texture;
	s_data.level5.scale.x = windowWidth / 10;
	s_data.level5.scale.y = windowHeight / 10;

	//set level 2_1
	s_data.level2_1.pos.x = windowWidth / 2 ;
	s_data.level2_1.pos.y = windowHeight / 1.4f;
	s_data.level2_1.texture = s_data.level1Texture;
	s_data.level2_1.scale.x = windowWidth / 10;
	s_data.level2_1.scale.y = windowHeight / 10;

	//set level 2_2
	s_data.level2_2.pos.x = windowWidth / 2;
	s_data.level2_2.pos.y = s_data.level2_1.pos.y - height;
	s_data.level2_2.texture = s_data.level1Texture;
	s_data.level2_2.scale.x = windowWidth / 10;
	s_data.level2_2.scale.y = windowHeight / 10;

	//set level2_3
	s_data.level2_3.pos.x = windowWidth / 2;
	s_data.level2_3.pos.y = s_data.level2_2.pos.y - height;
	s_data.level2_3.texture = s_data.level1Texture;
	s_data.level2_3.scale.x = windowWidth / 10;
	s_data.level2_3.scale.y = windowHeight / 10;

	//set level2_4
	s_data.level2_4.pos.x = windowWidth / 2;
	s_data.level2_4.pos.y = s_data.level2_3.pos.y - height;
	s_data.level2_4.texture = s_data.level1Texture;
	s_data.level2_4.scale.x = windowWidth / 10;
	s_data.level2_4.scale.y = windowHeight / 10;

	//set level2_5
	s_data.level2_5.pos.x = windowWidth / 2;
	s_data.level2_5.pos.y = s_data.level2_4.pos.y - height;
	s_data.level2_5.texture = s_data.level1Texture;
	s_data.level2_5.scale.x = windowWidth / 10;
	s_data.level2_5.scale.y = windowHeight / 10;

	//set level 3_1
	s_data.level3_1.pos.x = windowWidth / 2 + 2*width;
	s_data.level3_1.pos.y = windowHeight / 1.4f;
	s_data.level3_1.texture = s_data.level1Texture;
	s_data.level3_1.scale.x = windowWidth / 10;
	s_data.level3_1.scale.y = windowHeight / 10;

	//set level 3_2
	s_data.level3_2.pos.x = windowWidth / 2 + 2 * width;
	s_data.level3_2.pos.y = s_data.level2_1.pos.y - height;
	s_data.level3_2.texture = s_data.level1Texture;
	s_data.level3_2.scale.x = windowWidth / 10;
	s_data.level3_2.scale.y = windowHeight / 10;

	//set level 3_3
	s_data.level3_3.pos.x = windowWidth / 2 + 2 * width;
	s_data.level3_3.pos.y = s_data.level2_2.pos.y - height;
	s_data.level3_3.texture = s_data.level1Texture;
	s_data.level3_3.scale.x = windowWidth / 10;
	s_data.level3_3.scale.y = windowHeight / 10;

	//set level3_4
	s_data.level3_4.pos.x = windowWidth / 2 + 2 * width;
	s_data.level3_4.pos.y = s_data.level2_3.pos.y - height;
	s_data.level3_4.texture = s_data.level1Texture;
	s_data.level3_4.scale.x = windowWidth / 10;
	s_data.level3_4.scale.y = windowHeight / 10;

	//set level3_5
	s_data.level3_5.pos.x = windowWidth / 2 + 2 * width;
	s_data.level3_5.pos.y = s_data.level2_4.pos.y - height;
	s_data.level3_5.texture = s_data.level1Texture;
	s_data.level3_5.scale.x = windowWidth / 10;
	s_data.level3_5.scale.y = windowHeight / 10;

	//select button
	s_data.select.pos.x = windowWidth / 5.5f - xSize;
	s_data.select.pos.y = windowHeight / 1.4f;
	s_data.select.texture = s_data.selectTexture;
	s_data.select.scale.x = windowWidth / 12;
	s_data.select.scale.y = windowHeight / 12;

	//easy button
	s_data.easy.pos.x = s_data.level1.pos.x;
	s_data.easy.pos.y = windowHeight / 1.4f + height;
	s_data.easy.texture = s_data.easyTexture;
	s_data.easy.scale.x = windowWidth / 6;
	s_data.easy.scale.y = windowHeight / 11;

	//normal button
	s_data.normal.pos.x = s_data.level1.pos.x + 2 * width;
	s_data.normal.pos.y = windowHeight / 1.4f + height;
	s_data.normal.texture = s_data.normalTexture;
	s_data.normal.scale.x = windowWidth / 4;
	s_data.normal.scale.y = windowHeight / 11;

	//hard button
	s_data.hard.pos.x = s_data.level1.pos.x + 4 * width;
	s_data.hard.pos.y = windowHeight / 1.4f + height;
	s_data.hard.texture = s_data.hardTexture;
	s_data.hard.scale.x = windowWidth / 6;
	s_data.hard.scale.y = windowHeight / 11;

	stateData.isFullScreen = false;

}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void GameLevelSelectUpdate(float)
{
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	const float width = windowWidth / 6;
	const float height = windowHeight / 6;

	if (WEInput::IsTriggered(WE_F))
	{
		stateData.isFullScreen = !stateData.isFullScreen;
		WEApplication::SetFullScreen(stateData.isFullScreen);
	}

	WEGraphics::StartDraw();
	WEGraphics::SetToOrtho();

	/*Set the image to draw*/

	//draw background
	WEGraphics::SetTexture(s_data.menuTexture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform, (float)windowWidth, (float)windowHeight, 0,
		windowWidth / 2.0f, windowHeight / 2.0f, 0);
	WEGraphics::Draw(transform);

	//draw arrow to select each level
	WEGraphics::SetTexture(s_data.selectTexture);
	WEMtx44::MakeTransform(transform,
		s_data.select.scale.x, s_data.select.scale.y, 0.f,
		s_data.select.pos.x, s_data.select.pos.y, 0);
	WEGraphics::Draw(transform);

	//draw easy level1 texture
	WEGraphics::SetTexture(s_data.level1Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level1.scale.x, s_data.level1.scale.y, 0.f,
		s_data.level1.pos.x, s_data.level1.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw easy level2 texture
	WEGraphics::SetTexture(s_data.level2Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level2.scale.x, s_data.level2.scale.y, 0.f,
		s_data.level2.pos.x, s_data.level2.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw easy level3 texture
	WEGraphics::SetTexture(s_data.level3Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level3.scale.x, s_data.level3.scale.y, 0.f,
		s_data.level3.pos.x, s_data.level3.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw easy level4 texture
	WEGraphics::SetTexture(s_data.level4Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level4.scale.x, s_data.level4.scale.y, 0.f,
		s_data.level4.pos.x, s_data.level4.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw easy level5 texture
	WEGraphics::SetTexture(s_data.level5Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level5.scale.x, s_data.level5.scale.y, 0.f,
		s_data.level5.pos.x, s_data.level5.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw normal level1 texture
	WEGraphics::SetTexture(s_data.level2_1Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level2_1.scale.x, s_data.level2_1.scale.y, 0.f,
		s_data.level2_1.pos.x, s_data.level2_1.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw normal level2 texture
	WEGraphics::SetTexture(s_data.level2_2Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level2_2.scale.x, s_data.level2_2.scale.y, 0.f,
		s_data.level2_2.pos.x, s_data.level2_2.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw normal level3 texture
	WEGraphics::SetTexture(s_data.level2_3Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level2_3.scale.x, s_data.level2_3.scale.y, 0.f,
		s_data.level2_3.pos.x, s_data.level2_3.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw normal level4 texture
	WEGraphics::SetTexture(s_data.level2_4Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level2_4.scale.x, s_data.level2_4.scale.y, 0.f,
		s_data.level2_4.pos.x, s_data.level2_4.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw normal level5 texture
	WEGraphics::SetTexture(s_data.level2_5Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level2_5.scale.x, s_data.level2_5.scale.y, 0.f,
		s_data.level2_5.pos.x, s_data.level2_5.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw hard level1 texture
	WEGraphics::SetTexture(s_data.level3_1Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level3_1.scale.x, s_data.level3_1.scale.y, 0.f,
		s_data.level3_1.pos.x, s_data.level3_1.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw hard level2 texture
	WEGraphics::SetTexture(s_data.level3_2Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level3_2.scale.x, s_data.level3_2.scale.y, 0.f,
		s_data.level3_2.pos.x, s_data.level3_2.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw hard level3 texture
	WEGraphics::SetTexture(s_data.level3_3Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level3_3.scale.x, s_data.level3_3.scale.y, 0.f,
		s_data.level3_3.pos.x, s_data.level3_3.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw hard level4 texture
	WEGraphics::SetTexture(s_data.level3_4Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level3_4.scale.x, s_data.level3_4.scale.y, 0.f,
		s_data.level3_4.pos.x, s_data.level3_4.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw hard level5 texture
	WEGraphics::SetTexture(s_data.level3_5Texture);
	WEMtx44::MakeTransform(transform,
		s_data.level3_5.scale.x, s_data.level3_5.scale.y, 0.f,
		s_data.level3_5.pos.x, s_data.level3_5.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw easyLevel mode
	WEGraphics::SetTexture(s_data.easyTexture);
	WEMtx44::MakeTransform(transform,
		s_data.easy.scale.x, s_data.easy.scale.y, 0.f,
		s_data.easy.pos.x, s_data.easy.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw normalLevel mode
	WEGraphics::SetTexture(s_data.normalTexture);
	WEMtx44::MakeTransform(transform,
		s_data.normal.scale.x, s_data.normal.scale.y, 0.f,
		s_data.normal.pos.x, s_data.normal.pos.y, 0.f);
	WEGraphics::Draw(transform);

	//draw hardlevel mode
	WEGraphics::SetTexture(s_data.hardTexture);
	WEMtx44::MakeTransform(transform,
		s_data.hard.scale.x, s_data.hard.scale.y, 0.f,
		s_data.hard.pos.x, s_data.hard.pos.y, 0.f);
	WEGraphics::Draw(transform);
	

	//set the arrow to select level
	if (Xcount != XposCount - 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_RIGHT))
		{
			s_data.select.pos.x += (s_data.level2_1.pos.x) - (s_data.level1.pos.x);
			++Xcount;
		}
	}
	if (Xcount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_LEFT))
		{
			s_data.select.pos.x -= (s_data.level2_1.pos.x) - (s_data.level1.pos.x);
			--Xcount;
		}
	}
	if (Ycount != YposCount - 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_DOWN))
		{
			s_data.select.pos.y += (s_data.level2.pos.y) - (s_data.level1.pos.y);
			++Ycount;
		}
	}

	if (Ycount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_UP))
		{
			s_data.select.pos.y -= (s_data.level2.pos.y) - (s_data.level1.pos.y);
			--Ycount;
		}
	}

	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();

	extern int LevelNumber;
	if (WEInput::IsTriggered(WE_SPACE))
	{
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level1.pos,
			s_data.level1.scale.x, s_data.level1.scale.y))
		{
			LevelNumber = 1;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level2.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 2;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level3.pos,
			s_data.level3.scale.x, s_data.level3.scale.y))
		{
			LevelNumber = 3;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level4.pos,
			s_data.level4.scale.x, s_data.level4.scale.y))
		{
			LevelNumber = 4;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level5.pos,
			s_data.level5.scale.x, s_data.level5.scale.y))
		{
			LevelNumber = 5;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
	
		//////////////////Level2////////////////////////////
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level2_1.pos,
			s_data.level2_1.scale.x, s_data.level2_1.scale.y))
		{
			LevelNumber = 6;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level2_2.pos,
			s_data.level2_2.scale.x, s_data.level2_2.scale.y))
		{
			LevelNumber = 7;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level2_3.pos,
			s_data.level2_3.scale.x, s_data.level2_3.scale.y))
		{
			LevelNumber = 8;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level2_4.pos,
			s_data.level2_4.scale.x, s_data.level2_4.scale.y))
		{
			LevelNumber = 9;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level2_5.pos,
			s_data.level2_5.scale.x, s_data.level2_5.scale.y))
		{
			LevelNumber = 10;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		/////////////////////////level 3/////////////////////////////////////////
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level3_1.pos,
			s_data.level3_1.scale.x, s_data.level3_1.scale.y))
		{
			LevelNumber = 11;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level3_2.pos,
			s_data.level3_2.scale.x, s_data.level3_2.scale.y))
		{
			LevelNumber = 12;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level3_3.pos,
			s_data.level3_3.scale.x, s_data.level3_3.scale.y))
		{
			LevelNumber = 13;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level3_4.pos,
			s_data.level3_4.scale.x, s_data.level3_4.scale.y))
		{
			LevelNumber = 14;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
		if (WEIntersection::RectRect(s_data.select.pos, s_data.select.scale.x, s_data.select.scale.y, s_data.level3_5.pos,
			s_data.level3_5.scale.x, s_data.level3_5.scale.y))
		{
			LevelNumber = 15;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
	}

	// get mouse input to select level
	if (WEInput::IsTriggered(WE_MOUSE_LEFT))
	{
		WEVec2 mouse;
		WEInput::GetMouse(mouse);

		if (WEIntersection::PointRect(mouse, s_data.level1.pos,
			s_data.level1.scale.x, s_data.level1.scale.y))
		{
			LevelNumber = 1;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level2.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 2;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level3.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 3;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level4.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 4;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level5.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 5;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level2_1.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 6;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level2_2.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 7;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level2_3.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 8;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level2_4.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 9;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level2_5.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 10;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level3_1.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 11;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level3_2.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 12;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level3_3.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 13;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level3_4.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 14;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}

		if (WEIntersection::PointRect(mouse, s_data.level3_5.pos,
			s_data.level2.scale.x, s_data.level2.scale.y))
		{
			LevelNumber = 15;
			WEStateManager::SetNextState(DS_GAMELEV2);
		}
	}

	//set to full screen
	if (WEInput::IsTriggered(WE_F))
	{
		stateData.isFullScreen = !stateData.isFullScreen;
		WEApplication::SetFullScreen(stateData.isFullScreen);
	}
	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::SetNextState(DS_MAIN);
}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void GameLevelSelectShutdown(void)
{
	WEDEBUG_DESTROY_CONSOLE();
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void GameLevelSelectUnload(void)
{
	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(s_data.menuTexture);
	WEGraphics::UnloadTexture(s_data.level1Texture);
	WEGraphics::UnloadTexture(s_data.level2Texture);
	WEGraphics::UnloadTexture(s_data.level3Texture);
	WEGraphics::UnloadTexture(s_data.level4Texture);
	WEGraphics::UnloadTexture(s_data.level5Texture);
	WEGraphics::UnloadTexture(s_data.level2_1Texture);
	WEGraphics::UnloadTexture(s_data.level2_2Texture);
	WEGraphics::UnloadTexture(s_data.level2_3Texture);
	WEGraphics::UnloadTexture(s_data.level2_4Texture);
	WEGraphics::UnloadTexture(s_data.level2_5Texture);
	WEGraphics::UnloadTexture(s_data.level3_1Texture);
	WEGraphics::UnloadTexture(s_data.level3_2Texture);
	WEGraphics::UnloadTexture(s_data.level3_3Texture);
	WEGraphics::UnloadTexture(s_data.level3_4Texture);
	WEGraphics::UnloadTexture(s_data.level3_5Texture);
	WEGraphics::UnloadTexture(s_data.selectTexture);
	WEGraphics::UnloadTexture(s_data.easyTexture);
	WEGraphics::UnloadTexture(s_data.normalTexture);
	WEGraphics::UnloadTexture(s_data.hardTexture);
}
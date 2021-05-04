/******************************************************************************/
/*!
file    MainMenu.cpp
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/5/21

The MainMenu is used for Menu in game .
*/
/******************************************************************************/
#include "MainMenu.h"

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
#include "OBJ_M.h"
#include <cstdio>
#include "Sound.h"
#define TileSize 12
#define BulletVel 15
enum Colors
{
	C_NORMAL,	/*0*/
	C_RED,   /*1*/
	C_GREEN,  /*2*/
	C_BLUE,   /*3*/
	C_COUNT   /*4*/
};
enum Textures
{
	T_NORMAL, /* 0 */
	T_A,  /* 1 */
	T_C, /* 2 */
	T_D, /* 3 */
	T_E, /* 4 */
	T_I, /* 5 */
	T_N, /* 6 */
	T_O, /* 7 */
	T_P, /* 8 */
	T_R, /* 9 */
	T_S, /* 10 */
	T_T, /* 11 */
	T_X, /* 12 */
	T_COUNT /* 13 */
};
/*Make a struct for my shared state data*/
namespace
{
	struct InitData
	{
		int menuTexture;
		int s_Texture;
		int t_Texture;
		int a_Texture;
		int r_Texture;
		int q_Texture;
		int u_Texture;
		int i_Texture;
		int c_Texture;
		int e_Texture;
		int d_Texture;
		int arrowTexture;
		int selectTexture;
		int backTexture;
		int fullscreen_ID;
		int f_ID;
		int pressTexture;
	};
	struct MenuState1Data
	{
		bool isFullScreen;
	};
	/*Create a static variable for data so it can't be used in other files.*/
	InitData s_data;
	Ball Select;
	int P_Color;
	int Ycount;
	SoundSystemClass sound;
	SoundClass Shooting;
	SoundClass Back;
}
struct MenuObject
{
	unsigned colors[C_COUNT];
	int textures[T_COUNT];
	int xSize;
	int ySize;
	int tileText;
	float xPos;
	float yPos;
	ObjectManager * pObjMgr;
};
MenuObject data;

static MenuState1Data stateData;

/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void MenuStateLoad(void)
{
	/*Load the only texture we need for this state*/
	s_data.selectTexture = WEGraphics::LoadTexture("Textures\\arrowright.tga");
	s_data.backTexture = WEGraphics::LoadTexture("Textures\\menubackground.tga");
	data.textures[T_S] = WEGraphics::LoadTexture("Textures\\s.tga");
	data.textures[T_T] = WEGraphics::LoadTexture("Textures\\t.tga");
	data.textures[T_A] = WEGraphics::LoadTexture("Textures\\a.tga");
	data.textures[T_R] = WEGraphics::LoadTexture("Textures\\r.tga");
	data.textures[T_E] = WEGraphics::LoadTexture("Textures\\e.tga");
	data.textures[T_X] = WEGraphics::LoadTexture("Textures\\x.tga");
	data.textures[T_I] = WEGraphics::LoadTexture("Textures\\i.tga");
	data.textures[T_C] = WEGraphics::LoadTexture("Textures\\c.tga");
	data.textures[T_D] = WEGraphics::LoadTexture("Textures\\d.tga");
	data.textures[T_N] = WEGraphics::LoadTexture("Textures\\n.tga");
	data.textures[T_O] = WEGraphics::LoadTexture("Textures\\o.tga");
	data.textures[T_P] = WEGraphics::LoadTexture("Textures\\p.tga");
	data.textures[T_NORMAL] = WEGraphics::LoadTexture("Textures\\recc.tga");
	s_data.pressTexture = WEGraphics::LoadTexture("Textures\\Press.tga");
	s_data.arrowTexture = WEGraphics::LoadTexture("Textures\\arrowright.tga");
	s_data.f_ID = WEGraphics::LoadTexture("Textures\\f.tga");
	s_data.fullscreen_ID = WEGraphics::LoadTexture("Textures\\fullscreen.tga");
	/*All drawing in this state is in screen space*/
	sound.createSound(&Shooting, "Sound\\Shooting.wav");
	sound.createSound(&Back, "Sound\\BackGround.wav");
	sound.playSound(Back, true);
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void MenuStateInit(void)
{
	data.colors[C_NORMAL] = 0xFFFFFFFF;
	data.colors[C_RED] = 0xFF0000FF;
	data.colors[C_GREEN] = 0xFF00FF00;
	data.colors[C_BLUE] = 0xFFFF0000;
	P_Color = C_RED;
	Ycount = 0;
	WEGraphics::SetBackgroundColor(0.0f, 0.f, 0.f);

	WEVec2 tilePos;
	WEVec2 tileScale;

	FILE* pFile;
	WEDEBUG_CREATE_CONSOLE();
	fopen_s(&pFile, "Level//MainMenu.txt", "rt");
	WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!")
	fscanf_s(pFile, "%d", &data.xSize);
	fscanf_s(pFile, "%d", &data.ySize); 
	fscanf_s(pFile, "%f", &data.xPos);
	fscanf_s(pFile, "%f", &data.yPos); 
	data.pObjMgr = new ObjectManager(data.xSize, data.ySize);
	tilePos.x = data.xPos;
	tilePos.y = data.yPos;
	tileScale.x = TileSize;
	tileScale.y = TileSize;

	stateData.isFullScreen = false;
	/*****************************************************/
	// Player init
	WEVec2 playerPos;
	playerPos.x = tilePos.x;
	playerPos.y = tilePos.y;

	Select.color = data.colors[C_RED];
	Select.rotation = 0;
	Select.position.Set(playerPos.x, playerPos.y);
	Select.scale.Set(TileSize / 2, TileSize / 2);
	Select.vel.Set(0, 0);
	/*****************************************************/
	//Y-axis foot fedal init
	WEVec2 placePos;
	WEVec2 placeScale;
	placeScale.x = tileScale.x / 2;
	placeScale.y = tileScale.y / 2;
	/*****************************************************/
	for (int i = 0; i < data.ySize; ++i)
	{
		for (int l = 0; l < data.xSize; ++l)
		{
			fscanf_s(pFile, "%d", &data.tileText);
			tilePos.x += tileScale.x;
			data.pObjMgr->AddObject(tilePos, tileScale, data.textures[data.tileText], data.colors[C_NORMAL]);
			if (l == 0)
			{
				placePos.x = tilePos.x - TileSize;
				placePos.y = tilePos.y;
				data.pObjMgr->AddYPlace(placePos, placeScale, s_data.arrowTexture, data.colors[C_NORMAL]);
			}
		}
		tilePos.y -= tileScale.y;
		tilePos.x = data.xPos;
	}
	// Close the File
	fclose(pFile);
}

void CreateBullet(int Color)
{
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;
	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = Select.position;
	vel.x = 10;
	vel.y = 0;

	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, s_data.selectTexture, data.colors[Color]);
}

/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void MenuStateUpdate(float dt)
{
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	Ball* pYPlaceObj = data.pObjMgr->GetYPlaceObj();
	Object* pObjects = data.pObjMgr->GetObjects();
	Bullet* pBullet = data.pObjMgr->GetBullets();
	//Bullet Vel and Pos
	for (int i = 0; i < data.pObjMgr->GetBulletCount(); ++i)
	{
		pBullet[i].position += pBullet[i].vel * dt * BulletVel;
	}

	if (Ycount != data.ySize - 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_DOWN))
		{
			Select.position.y -= TileSize;
			++Ycount;
		}
	}

	if (Ycount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_UP))
		{
			Select.position.y += TileSize;
			--Ycount;
		}
	}

	int NextState = 0;
	for (int i = 0; i < data.ySize; ++i)
	{
		NextState = 0;
		for (int l = 0; l < data.xSize; ++l)
		{
			if (pObjects[i*data.ySize + l].color != data.colors[C_NORMAL])
			{
				if (i == 0)
				{
					++NextState;
					if ((pObjects[i*data.ySize + l].color == pYPlaceObj[0].color) && (NextState == data.xSize))
						WEStateManager::SetNextState(DS_SELECTLEVEL);
				}
			}
		}
	}

	NextState = 0;
	for (int l = 0; l < data.xSize; ++l)
	{
		if (pObjects[data.xSize + l].color != data.colors[C_NORMAL])
		{
			if (pObjects[data.xSize + l].color == pYPlaceObj[1].color)
				++NextState;
		}
		if (NextState == data.xSize)
			WEStateManager::SetNextState(DS_CREDIT);
	}

	NextState = 0;
	for (int l = 0; l < data.xSize; ++l)
	{
		if (pObjects[data.xSize * 2 + l].color != data.colors[C_NORMAL])
		{
			if (pObjects[data.xSize * 2 + l].color == pYPlaceObj[2].color)
				++NextState;
		}
		if (NextState == data.xSize)
			WEStateManager::Quit();
	}

	if (WEInput::IsTriggered(WE_1))
	{
		P_Color = C_RED;
	}
	if (WEInput::IsTriggered(WE_2))
	{
		P_Color = C_BLUE;
	}
	if (WEInput::IsTriggered(WE_3))
	{
		P_Color = C_GREEN;
	}
	/***********************************************************/
	/* Changing Color By Bullet */
	for (int i = 0; i < data.pObjMgr->GetBulletCount(); ++i)
	{
		for (int n = 0; n < data.pObjMgr->GetObjectCount(); ++n)
		{
			if (WEIntersection::CircleRect(pBullet[i].position, pBullet[i].scale.x / 2, pObjects[n].position, pObjects[n].scale.y, pObjects[n].scale.x))
			{
				pObjects[n].color = pBullet[i].color;
			}
		}
	}
	/***********************************************************/
	/* Changing pYPlace Tile */
	if (WEInput::IsTriggered(WE_SPACE))
	{
		for (int i = 0; i < data.pObjMgr->GetYPlaceObjCount(); ++i)
		{
			if (WEIntersection::CircleCircle(pYPlaceObj[i].position, pYPlaceObj[i].scale.x / 2, Select.position, Select.scale.x / 2))
			{
				pYPlaceObj[i].color = data.colors[P_Color];
			}
		}
	}
	/***********************************************************/
	if (WEInput::IsTriggered(WE_SPACE))
	{
		sound.playSound(Shooting, false);
		for (int i = 0; i < data.ySize; ++i)
		{
				CreateBullet(P_Color);
		}
	}

	WEGraphics::StartDraw();
	WEGraphics::SetToPerspective();

	WEGraphics::SetTexture(s_data.backTexture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform, (float)windowWidth / 5.5f, (float)windowHeight / 5.5f, 0, 0, 0, -1);
	WEGraphics::Draw(transform);

	/*Set the image to draw*/


	for (int i = 0; i < data.pObjMgr->GetObjectCount(); ++i)
	{
		WEGraphics::SetTexture(pObjects[i].texture);
		WEGraphics::SetTextureColor(pObjects[i].color);
		WEMtx44::MakeTransform(transform,
			pObjects[i].scale.x, pObjects[i].scale.y,
			0,
			pObjects[i].position.x, pObjects[i].position.y, 0.f);
		WEGraphics::Draw(transform);
	}

	for (int i = 0; i < data.pObjMgr->GetYPlaceObjCount(); ++i)
	{
		WEGraphics::SetTexture(pYPlaceObj[i].texture);
		WEGraphics::SetTextureColor(pYPlaceObj[i].color);
		WEMtx44::MakeTransform(transform,
			pYPlaceObj[i].scale.x, pYPlaceObj[i].scale.y,
			0,
			pYPlaceObj[i].position.x, pYPlaceObj[i].position.y, 0.f);
		WEGraphics::Draw(transform);
	}

	WEGraphics::SetTexture(s_data.selectTexture);
	WEGraphics::SetTextureColor(data.colors[P_Color]);
	WEMtx44::MakeTransform(transform,
		Select.scale.x, Select.scale.y,
		Select.rotation,
		Select.position.x, Select.position.y, 0.f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.f_ID);
	WEMtx44::MakeTransform(transform, windowWidth / 4,
		windowHeight / 4, 0, windowWidth / 3, windowHeight / 1.15f, 0.f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(s_data.fullscreen_ID);
	WEMtx44::MakeTransform(transform, windowWidth / 4,
		windowHeight / 4, 0, windowWidth / 4, windowHeight / 1.15f, 0.f);
	WEGraphics::Draw(transform);

	WEGraphics::SetToOrtho();

	WEGraphics::SetTexture(s_data.pressTexture);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform,
		windowWidth / 7, windowHeight/ 8 , 0, windowWidth / 2, windowHeight / 3,
		0);
	WEGraphics::Draw(transform);

	/*This must be called to after all drawing is completed*/
	WEGraphics::EndDraw();

	if (WEInput::IsTriggered(WE_N))
		WEStateManager::SetNextState(DS_SELECTLEVEL);
	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::Quit();

	if (WEInput::IsTriggered(WE_F))
	{
		stateData.isFullScreen = !stateData.isFullScreen;
		WEApplication::SetFullScreen(stateData.isFullScreen);
	}
}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void MenuStateShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void MenuStateUnload(void)
{
	/*We must unload the texture when we are done with the state*/
	WEGraphics::UnloadTexture(s_data.selectTexture);
	WEGraphics::UnloadTexture(s_data.menuTexture);
	WEGraphics::UnloadTexture(data.textures[T_S]);
	WEGraphics::UnloadTexture(data.textures[T_T]);
	WEGraphics::UnloadTexture(data.textures[T_A]);
	WEGraphics::UnloadTexture(data.textures[T_R]);
	WEGraphics::UnloadTexture(data.textures[T_E]);
	WEGraphics::UnloadTexture(data.textures[T_X]);
	WEGraphics::UnloadTexture(data.textures[T_I]);
	WEGraphics::UnloadTexture(data.textures[T_C]); 
	WEGraphics::UnloadTexture(data.textures[T_D]);
	WEGraphics::UnloadTexture(data.textures[T_N]);
	WEGraphics::UnloadTexture(data.textures[T_O]);
	WEGraphics::UnloadTexture(data.textures[T_P]);
	WEGraphics::UnloadTexture(data.textures[T_NORMAL]);
	WEGraphics::UnloadTexture(s_data.arrowTexture);
	WEGraphics::UnloadTexture(s_data.backTexture);
	WEGraphics::UnloadTexture(s_data.fullscreen_ID);
	WEGraphics::UnloadTexture(s_data.f_ID);
	WEGraphics::UnloadTexture(s_data.pressTexture);
	/*All drawing in this state is in screen space*/
	sound.releaseSound(Back);
	sound.releaseSound(Shooting);
}
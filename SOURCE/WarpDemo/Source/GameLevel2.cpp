/******************************************************************************/
/*!
file    GameLevel2.cpp
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/3/27
All content © 2017 DigiPen (USA) Corporation, all rights reserved.

The GameLevel2 state is used for reading every game Levels by Text file.
*/
/******************************************************************************/
#include "GameLevel2.h"

#include "WEDebugTools.h"
#include "WEGraphics.h"
#include "WEInput.h"
#include "WEIntersection.h"
#include "WEApplication.h"
#include "WEStateManager.h"
#include "WEMtx44.h"
#include "WEMath.h"
#include "WERandom.h"
#include "DemoStates.h"

#include "SetHud.h"
#include "WinHud.h"
#include "LoseHud.h"
#include "ShowLevel.h"
#include "Sound.h"
#include "OBJ_M.h"
#include "Star.h"
#include <cstdio>
#include <iostream>
#define TileSize 8

extern int LevelNumber;

namespace
{
	bool BulletGone;
	bool Winupdate; // Win Hud update
	bool Loseupdate; // Lose Hud update
	char* Level;
	Ball Player; // Player Init
	int Xcount; // X-axis foothold count
	int Ycount; // Y-axis foothold count
	int Check; // Check whether every tiles are same with answer tiles
	int P_Color; // player color
	bool ItemBullet; // To make sure Item works only once
	int BulletCount;
	int CheckRemain;
	SoundSystemClass sound;
	SoundClass Shooting;
	SoundClass BackGround;
	int s_Max; // Max for Star
	int s_Least; // Least for Star
	Star star1;
	Star star2;
	Star star3;
	int single_dig;
	int double_dig;
	int max_single;
	int max_double;
}
/* Arrow texture for foot fedal(?)*/
namespace Arrow
{
	int up;
	int down;
	int left;
	int right;
}

enum Colors
{
	C_NORMAL,	/*0*/
	C_RED,   /*1*/
	C_GREEN,  /*2*/
	C_BLUE,   /*3*/
	C_BLACK,  /*4*/
	C_WHITE,  /*5*/
	C_COUNT   /*6*/
};

enum Number
{
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten
};

struct ObjectData
{
	unsigned colors[C_COUNT];
	int Bullet_Texture;
	int Max_Bullet_Texture;
	int Ball_ID;
	int Item_ID;
	int Rect_ID;
	int Bullet_ID;
	int MaxBullet_ID;
	int Background_ID;
	int objectcount;
	int maxBullet;
	int xSize;
	int ySize;
	float xPos;
	float yPos;
	float ansXpos;
	float ansYpos;
	int ansColor;
	int tileColor;
	int itemNum; /* Number of Tile Where Item will be placed*/
	int itemAmount;/* Amount of item */
	ObjectManager * pObjMgr;
	ItemManager * pItemMgr;
	WEVec2 botLeft;
	WEVec2 topLeft;
	WEVec2 botRight;
	WEVec2 topRight;
	int Num[Ten];
};
ObjectData data;

void GameLevel2Load(void)
{
	WinHud::WinHudLoad();
	SetHud::SetHudLoad();
	LoseHUD::LoseHudLoad();
	ShowLevel::ShowLevelLoad();

	data.Num[Zero] = WEGraphics::LoadTexture("Textures\\0.tga");
	data.Num[One] = WEGraphics::LoadTexture("Textures\\1.tga");
	data.Num[Two] = WEGraphics::LoadTexture("Textures\\2.tga");
	data.Num[Three] = WEGraphics::LoadTexture("Textures\\3.tga");
	data.Num[Four] = WEGraphics::LoadTexture("Textures\\4.tga");
	data.Num[Five] = WEGraphics::LoadTexture("Textures\\5.tga");
	data.Num[Six] = WEGraphics::LoadTexture("Textures\\6.tga");
	data.Num[Seven] = WEGraphics::LoadTexture("Textures\\7.tga");
	data.Num[Eight] = WEGraphics::LoadTexture("Textures\\8.tga");
	data.Num[Nine] = WEGraphics::LoadTexture("Textures\\9.tga");
	sound.createSound(&Shooting,"Sound\\Shooting.wav" );
	sound.createSound(&BackGround, "Sound\\BackGround.wav");
	data.Ball_ID = WEGraphics::LoadTexture("Textures\\Player.tga");
	data.Item_ID = WEGraphics::LoadTexture("Textures\\item2.tga");
	data.Rect_ID = WEGraphics::LoadTexture("Textures\\recc.tga");
	Arrow::down = WEGraphics::LoadTexture("Textures\\arrowdown.tga");
	Arrow::left = WEGraphics::LoadTexture("Textures\\arrowleft.tga");
	Arrow::right = WEGraphics::LoadTexture("Textures\\arrowright.tga");
	Arrow::up= WEGraphics::LoadTexture("Textures\\arrowup.tga");
	data.Background_ID = WEGraphics::LoadTexture("Textures\\levelbag.tga");
	data.Bullet_ID = WEGraphics::LoadTexture("Textures\\bullet.tga");
	data.MaxBullet_ID = WEGraphics::LoadTexture("Textures\\maxbullet.tga");
	sound.playSound(BackGround, true);
}

void GameLevel2Init(void)
{
	/******************************************************************************/
	/* single, double digits for BulletCount Textures*/
	single_dig = 0;
	double_dig = 0;
	BulletGone = false;
	/******************************************************************************/
	/* Win & Lose Condition Init fuction call*/
	WinHud::WinHudInit();
	SetHud::SetHudInit();
	LoseHUD::LoseHudInit();
	ShowLevel::ShowLevelInit();
	Winupdate = false;
	Loseupdate = false;
	/******************************************************************************/
	WEDEBUG_CREATE_CONSOLE();
	Xcount = 0;
	Ycount = 0;
	Check = 0;
	BulletCount = 0;
	CheckRemain = 0;
	/******************************************************************************/
	/* Reads Text File */
	switch (LevelNumber)
	{
	case 1:
	{
		Level = "Level//Level.txt";
		break;
	}
	case 2:
	{
		Level = "Level//Level2.txt";
		break;
	}
	case 3:
	{
		Level = "Level//Level3.txt";
		break;
	}
	case 4:
	{
		Level = "Level//Level4.txt";
		break;
	}
	case 5:
	{
		Level = "Level//Level5.txt";
		break;
	}
	case 6:
	{
		Level = "Level//Level6.txt";
		break;
	}
	case 7:
	{
		Level = "Level//Level7.txt";
		break;
	}
	case 8:
	{
		Level = "Level//Level8.txt";
		break;
	}
	case 9:
	{
		Level = "Level//Level9.txt";
		break;
	}
	case 10:
	{
		Level = "Level//Level10.txt";
		break;
	}
	case 11:
	{
		Level = "Level//Level11.txt";
		break;
	}
	case 12:
	{
		Level = "Level//Level12.txt";
		break;
	}
	case 13:
	{
		Level = "Level//Level13.txt";
		break;
	}
	case 14:
	{
		Level = "Level//Level14.txt";
		break;
	}
	case 15:
	{
		Level = "Level//Level15.txt";
		break;
	}
	default: WEStateManager::SetNextState(DS_SELECTLEVEL);
	}
	/******************************************************************************/
	// Color Setting
	data.colors[C_NORMAL] = 0xFFFFFFFF;
	data.colors[C_RED] = 0xFF0000FF;
	data.colors[C_GREEN] = 0xFF00FF00;
	data.colors[C_BLUE] = 0xFFFF0000;
	data.colors[C_BLACK] = 0xFF000000;
	data.colors[C_WHITE] = 0x00000000;

	WEGraphics::SetBackgroundColor(255, 255, 255);
	/******************************************************************************/
	// Open the file
	FILE* pFile;
	fopen_s(&pFile, Level, "rt");
	WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!")
	// Tiles for game
	WEVec2 tilePos;
	WEVec2 tileScale;
	// Answer Tiles
	WEVec2 ans_Pos;
	WEVec2 ans_Scale;
	//Read Text File
	fscanf_s(pFile, "%d", &data.xSize); // X size of Tile
	fscanf_s(pFile, "%d", &data.ySize); // Y size of Tile
	fscanf_s(pFile, "%d", &data.maxBullet);
	fscanf_s(pFile, "%f", &data.xPos); // X position of Tile
	fscanf_s(pFile, "%f", &data.yPos); // Y position of Tile
	fscanf_s(pFile, "%f", &data.ansXpos); // X position of Answer Tile
	fscanf_s(pFile, "%f", &data.ansYpos); // Y position of Answer Tile
	tilePos.x = data.xPos;
	tilePos.y = data.yPos;
	tileScale.x = TileSize;
	tileScale.y = TileSize;
	ans_Scale.x = TileSize / 2;
	ans_Scale.y = TileSize / 2;
	ans_Pos.x = data.ansXpos;
	ans_Pos.y = data.ansYpos;
	/******************************************************************************/
	//Player Initialize
		WEVec2 playerPos;
		playerPos.x = tilePos.x;
		playerPos.y = tilePos.y + TileSize;

		WEVec2 playerVel;
		playerVel.x = 0;
		playerVel.y = 0;

		P_Color = C_RED;
		Player.color = data.colors[C_RED];
		Player.isclicked = false;
		Player.rotation = 0;
		Player.position.Set(playerPos.x, playerPos.y);
		Player.scale.Set(TileSize/2, TileSize/2);
		Player.vel.Set(playerVel.x, playerVel.y);
	/******************************************************************************/
	data.pObjMgr = new ObjectManager(data.xSize, data.ySize);
	WEVec2 placePos;
	WEVec2 placeScale;
	placeScale.x = tileScale.x / 2;
	placeScale.y = tileScale.y / 2;

	//Informations about Star for grading system
	fscanf_s(pFile, "%d", &s_Least);
	fscanf_s(pFile, "%d", &s_Max);
	star1.SetMaxMin(s_Max, s_Least);
	fscanf_s(pFile, "%d", &s_Least);
	fscanf_s(pFile, "%d", &s_Max);
	star2.SetMaxMin(s_Max, s_Least);
	fscanf_s(pFile, "%d", &s_Least);
	fscanf_s(pFile, "%d", &s_Max);
	star3.SetMaxMin(s_Max, s_Least);

	//Create Answer Puzzle
	for (int i = 0; i < data.ySize; ++i)
	{
			for (int l = 0; l < data.xSize; ++l)
			{
				fscanf_s(pFile, "%d", &data.ansColor); // Color of Answer Tile
				ans_Pos.x += ans_Scale.x;
				data.pObjMgr->AddAnsObj(ans_Pos, ans_Scale, data.Rect_ID, data.colors[data.ansColor]);
			}
			ans_Pos.y -= ans_Scale.y;
			ans_Pos.x = data.ansXpos;
	}

	 // Create Tile, and Place Where Player Can Move
	for (int i = 0; i < data.ySize; ++i)
	{
			for (int l = 0; l < data.xSize; ++l)
			{
				fscanf_s(pFile, "%d", &data.tileColor);
				tilePos.x += tileScale.x;
				data.pObjMgr->AddObject(tilePos, tileScale, data.Rect_ID, data.colors[data.tileColor]);
				if (i == 0)
				{
					placePos.x = tilePos.x;
					placePos.y = tilePos.y + TileSize;
					data.pObjMgr->AddXPlace(placePos, placeScale, Arrow::down, data.colors[C_NORMAL]);
				}
				if (i == data.ySize - 1)
				{
					placePos.x = tilePos.x;
					placePos.y = tilePos.y - TileSize;
					data.pObjMgr->AddXPlace(placePos, placeScale, Arrow::up, data.colors[C_NORMAL]);
				}
				if (l == 0)
				{
					placePos.x = tilePos.x - TileSize;
					placePos.y = tilePos.y;
					data.pObjMgr->AddYPlace(placePos, placeScale, Arrow::right, data.colors[C_NORMAL]);
				}
			}
			tilePos.y -= tileScale.y;
			tilePos.x = data.xPos;
	}
	
	Object* pObjects = data.pObjMgr->GetObjects();
	// Create Place Where Player Can Move
	for (int i = 0; i < data.ySize; ++i)
	{
			tilePos.x += tileScale.x;
			for (int l = 0; l < data.xSize; ++l)
			{
					if (l == data.xSize - 1)
					{
						placePos.x = tilePos.x + (TileSize * (data.xSize+1));
						placePos.y = tilePos.y - (TileSize * i);
						data.pObjMgr->AddYPlace(placePos, placeScale, Arrow::left, data.colors[C_NORMAL]);
					}
					tilePos.y = data.yPos;
					tilePos.x = data.xPos;
			}
	}
	// Item
	fscanf_s(pFile, "%d", &data.itemAmount);
	data.pItemMgr = new ItemManager(data.itemAmount);
	for (int i = 0; i < data.itemAmount; ++i)
	{
		fscanf_s(pFile, "%d", &data.itemNum);
		placePos = pObjects[data.itemNum].position;
		data.pItemMgr->AddItem(placePos, placeScale * 1.5f, data.Item_ID, data.colors[0]);
	}
	// Close the File
	fclose(pFile);
}

/*****************************************************/
/* Item Action */
void ItemBulletX_P(int itemNum)
{
	Item* pItems = data.pItemMgr->GetItem();
		WEVec2 pos;
		WEVec2 vel;
		WEVec2 scale;
		scale.x = TileSize / 2;
		scale.y = TileSize / 2;

		pos = pItems[itemNum].position;
		vel.x = 10;
		vel.y = 0;

		/*Add to the object manager*/
		data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, pItems[itemNum].color);
}
void ItemBulletX_N(int itemNum)
{
	Item* pItems = data.pItemMgr->GetItem();
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;
	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = pItems[itemNum].position;

	vel.x = -10;
	vel.y = 0;

	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, pItems[itemNum].color);
}
void ItemBulletY_P(int itemNum)
{
	Item* pItems = data.pItemMgr->GetItem();
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;
	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = pItems[itemNum].position;

	vel.x = 0;
	vel.y = 10;
	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, pItems[itemNum].color);
}
void ItemBulletY_N(int itemNum)
{
	Item* pItems = data.pItemMgr->GetItem();
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;

	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = pItems[itemNum].position;

	vel.x = 0;
	vel.y = -10;

	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, pItems[itemNum].color);
}
/*****************************************************************/
/*Player Shooting*/
void CreateBulletX_P(int Color)
{
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;
	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = Player.position;
	vel.x = 10;
	vel.y = 0;

	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, data.colors[Color]);
}
void CreateBulletX_N(int Color)
{
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;

	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = Player.position;

	vel.x = -10;
	vel.y = 0;

	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, data.colors[Color]);
}
void CreateBulletY_P(int Color)
{
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;
	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = Player.position;

	vel.x = 0;
	vel.y = 10;
	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, data.colors[Color]);
}
void CreateBulletY_N(int Color)
{
	WEVec2 pos;
	WEVec2 vel;
	WEVec2 scale;

	scale.x = TileSize / 2;
	scale.y = TileSize / 2;

	pos = Player.position;

	vel.x = 0;
	vel.y = -10;

	/*Add to the object manager*/
	data.pObjMgr->AddBullet(vel, pos, scale, data.Ball_ID, data.colors[Color]);
}
/* Item */
void ItemAction(int itemNum)
{
	ItemBulletY_N(itemNum);
	ItemBulletY_P(itemNum);
	ItemBulletX_N(itemNum);
	ItemBulletX_P(itemNum);
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void GameLevel2Update(float dt)
{
	Object* pObjects = data.pObjMgr->GetObjects();
	Object* pAnsObj = data.pObjMgr->GetAnsObj();
	Ball* pXPlaceObj = data.pObjMgr->GetXPlaceObj();
	Ball* pYPlaceObj = data.pObjMgr->GetYPlaceObj();
	Bullet* pBullet = data.pObjMgr->GetBullets();
	Item* pItems = data.pItemMgr->GetItem();
	WEMtx44 transform;
	float windowWidth = (float)WEApplication::GetWidth();
	float windowHeight = (float)WEApplication::GetHeight();
	/******************************************************************************/
	// Moving Player
	if (Xcount != data.xSize + 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_RIGHT))
		{
			if (Ycount != 0 && Ycount != data.ySize + 1)
			{
				Player.position.x += TileSize * (data.xSize + 1);
				Xcount = data.xSize + 1;
			}
			else
			{
				Player.position.x += TileSize;
				++Xcount;
			}
		}
	}
	if (Xcount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_LEFT))
		{
			if (Ycount != 0 && Ycount != data.ySize + 1)
			{
				Player.position.x -= TileSize*(data.xSize + 1);
				Xcount = 0;
			}
			else
			{
				Player.position.x -= TileSize;
				--Xcount;
			}
		}
	}
	if (Ycount != data.ySize + 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_DOWN))
		{
			if (Xcount != 0 && Xcount != data.xSize + 1)
			{
				Player.position.y -= TileSize*(data.ySize + 1);
				Ycount = data.ySize + 1;
			}
			else
			{
				Player.position.y -= TileSize;
				++Ycount;
			}
		}
	}
	if (Ycount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_UP))
		{
			if (Xcount != 0 && Xcount != data.xSize + 1)
			{
				Player.position.y += TileSize*(data.ySize + 1);
				Ycount = 0;
			}
			else
			{
				Player.position.y += TileSize;
				--Ycount;
			}
		}
	}
	/******************************************************************************/
	/* Bullet velocity and position change */
	for (int i = 0; i < data.pObjMgr->GetBulletCount(); ++i)
	{
		pBullet[i].position += pBullet[i].vel * dt  * 30;
	}
	// Changing Player Color By Pressing Buttons
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
				if (pObjects[n].color != data.colors[C_WHITE])
				{
					if (pObjects[n].color != data.colors[C_BLACK])
					{
						pObjects[n].color = pBullet[i].color;
						pObjects[n].isclicked = true;
					}
					else if (pObjects[n].color == data.colors[C_BLACK])
						data.pObjMgr->DeleteBullet(i);
				}
			}
		}
		for (int n = 0; n < data.pObjMgr->GetObjectCount(); ++n)
		{
			for (int k = 0; k < data.pItemMgr->GetItemCount(); ++k)
			{
				if (pItems[k].used == false)
				{
					if (pObjects[n].position == pItems[k].position && (pObjects[n].isclicked == true))
					{
						pItems[k].color = pObjects[n].color;
						ItemAction(k);
						pItems[k].used = true;
						pItems[k].color = data.colors[C_WHITE];
					}
				}
			}
		}
	}
	/***********************************************************************/
	// Changes Opposite place Color to Change Tile Color
	if (WEInput::IsTriggered(WE_SPACE))
	{
		for (int i = data.ySize - 1; i >= 0; --i)
		{
			if (WEIntersection::CircleCircle(pYPlaceObj[i + data.ySize].position,
				pYPlaceObj[i + data.ySize].scale.x / 2,
				Player.position,
				Player.scale.x / 2))
			{
				BulletCount++;
				--CheckRemain;
				CreateBulletX_N(P_Color);
				sound.playSound(Shooting, false);
			}
				if (WEIntersection::CircleCircle(pXPlaceObj[i + data.xSize].position,
					pXPlaceObj[i + data.xSize].scale.x / 2,
					Player.position,
					Player.scale.x / 2))
				{
					BulletCount++;
					--CheckRemain;
					CreateBulletY_P(P_Color);
					sound.playSound(Shooting, false);
				}
		}
	}
	// Change Color of Vertical and Horizontal Tile
	if (WEInput::IsTriggered(WE_SPACE))
	{
		for (int i = 0; i < data.ySize; ++i)
		{
			if (WEIntersection::CircleCircle(Player.position, Player.scale.x / 2,
				pYPlaceObj[i].position, pYPlaceObj[i].scale.x / 2))
			{
				BulletCount++;
				CreateBulletX_P(P_Color);
				sound.playSound(Shooting, false);
			}
			if (WEIntersection::CircleCircle(Player.position, Player.scale.x / 2,
				pXPlaceObj[i].position, pXPlaceObj[i].scale.x / 2))
			{
				BulletCount++;
				CreateBulletY_N(P_Color);
				sound.playSound(Shooting, false);
			}
		}
	}

	/******************************************************************************/
	WEGraphics::StartDraw();/*We must call this before drawing anything*/
	WEGraphics::SetToPerspective();/*Draw in world space*/
	/* Draw Tiles */

	WEGraphics::SetTexture(data.Background_ID);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform, (float)windowWidth / 5.5f, (float)windowHeight / 5.5f, 0, 0, 0, -1);
	WEGraphics::Draw(transform);
	/* Bullet Amount Drawing */
	float Z  = 0;


	if (BulletCount >= Ten)
	{
 		single_dig = BulletCount % Ten;
		double_dig = BulletCount / Ten;
	}
	else
	{
		single_dig = BulletCount;
		double_dig = 0;
	}

	if (data.maxBullet >= Ten)
	{
		max_single = data.maxBullet % Ten;
		max_double = data.maxBullet / Ten;
	}
	else
	{
		max_single = data.maxBullet;
		max_double = 0;
	}

	for (int i = 0; i < data.pObjMgr->GetObjectCount(); ++i)
	{
		Z = 0;
		if (pObjects[i].color == data.colors[C_WHITE])
			Z = -2;
		WEGraphics::SetTexture(pObjects[i].texture);
		WEGraphics::SetTextureColor(pObjects[i].color);
		WEMtx44::MakeTransform(transform,
			pObjects[i].scale.x, pObjects[i].scale.y,
			0,
			pObjects[i].position.x, pObjects[i].position.y, Z);
		WEGraphics::Draw(transform);
	}

	/* Draw Answer Tiles */
	for (int i = 0; i < data.pObjMgr->GetAnsObjCount(); ++i)
	{
		Z = 0;
		if (pAnsObj[i].color == data.colors[C_WHITE])
			Z = -2;
		WEGraphics::SetTexture(pAnsObj[i].texture);
		WEGraphics::SetTextureColor(pAnsObj[i].color);
		WEMtx44::MakeTransform(transform,
			pAnsObj[i].scale.x, pAnsObj[i].scale.y,
			0,
			pAnsObj[i].position.x, pAnsObj[i].position.y, Z);
		WEGraphics::Draw(transform);
	}

	/* Draw X-axis Place */
	for (int i = 0; i < data.pObjMgr->GetXPlaceObjCount(); ++i)
	{
		WEGraphics::SetTexture(pXPlaceObj[i].texture);
		WEGraphics::SetTextureColor(pXPlaceObj[i].color);
		WEMtx44::MakeTransform(transform,
			pXPlaceObj[i].scale.x, pXPlaceObj[i].scale.y,
			0,
			pXPlaceObj[i].position.x, pXPlaceObj[i].position.y, 0.f);
		WEGraphics::Draw(transform);
	}

	/* Draw Y-axis Place */
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

	/* Draw Item */
	for (int i = 0; i < data.pItemMgr->GetItemCount(); ++i)
	{
		if (pItems[i].used == false)
		{
			WEGraphics::SetTexture(pItems[i].texture);
			WEGraphics::SetTextureColor(pItems[i].color);
			WEMtx44::MakeTransform(transform,
				pItems[i].scale.x, pItems[i].scale.y,
				0,
				pItems[i].position.x, pItems[i].position.y, 0.f);
			WEGraphics::Draw(transform);
		}
	}
	
	/* Draw Bullets */
	for (int i = 0; i < data.pObjMgr->GetBulletCount(); ++i)
	{
		WEGraphics::SetTexture(pBullet[i].texture);
		WEGraphics::SetTextureColor(pBullet[i].color);
		WEMtx44::MakeTransform(transform,
			pBullet[i].scale.x, pBullet[i].scale.y,
			0,
			pBullet[i].position.x, pBullet[i].position.y, -2.f);
		WEGraphics::Draw(transform);
	}

	/* Draw Player */
	WEGraphics::SetTexture(data.Ball_ID);
	WEGraphics::SetTextureColor(data.colors[P_Color]);
	WEMtx44::MakeTransform(transform,
		Player.scale.x, Player.scale.y,
		Player.rotation,
		Player.position.x, Player.position.y, 0.f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(data.Num[double_dig]);
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	WEMtx44::MakeTransform(transform,
		TileSize / 2, TileSize / 2, 0,
		90 , -15, 2.f); 
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(data.Num[single_dig]);
	WEMtx44::MakeTransform(transform,
		TileSize / 2, TileSize / 2, 0,
		95, -15, 2.f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(data.Num[max_double]);
	WEMtx44::MakeTransform(transform,
		TileSize / 2, TileSize / 2, 0,
		90, -6 , 2.f);
	WEGraphics::Draw(transform);

	WEGraphics::SetTexture(data.Num[max_single]);
	WEMtx44::MakeTransform(transform,
		TileSize / 2, TileSize / 2, 0,
		95, -6, 2.f);
	WEGraphics::Draw(transform);

	/* Check How many Stars player get */
	if (Winupdate)
	{
		star1.StarAmount(BulletCount);
		star2.StarAmount(BulletCount);
		star3.StarAmount(BulletCount);
	}

	/*Win & Lose Hud Update function call*/
	if (Winupdate)
		WinHud::WinHudUpdate(dt);
	if(Loseupdate)
		LoseHUD::LoseHudUpdate(dt);

	SetHud::SetHudUpdate(dt);
	ShowLevel::ShowLevelUpdate(dt);

	WEGraphics::EndDraw(); /* End Drawing */
	/******************************************************************************/
	WEGraphics::GetWorldBotLeft(data.botLeft);
	WEGraphics::GetWorldTopLeft(data.topLeft);
	WEGraphics::GetWorldBotRight(data.botRight);
	WEGraphics::GetWorldTopRight(data.topRight);

	for (int i = 0; i < data.pObjMgr->GetBulletCount(); ++i)
	{
		if (pBullet[i].vel.x > 0 && (pBullet[i].position.x > data.botRight.x))
			BulletGone = true;
		else if (pBullet[i].vel.x < 0 && (pBullet[i].position.x < data.botLeft.x))
			BulletGone = true;
		else if (pBullet[i].vel.y < 0 && (pBullet[i].position.y < data.botLeft.y))
			BulletGone = true;
		else if (pBullet[i].vel.y > 0 && (pBullet[i].position.y > data.topLeft.y))
			BulletGone = true;
		else
			BulletGone = false;
	}
		// Game Lose condition
		if (Winupdate != true)
		{
			if (data.maxBullet <= BulletCount && BulletGone)
				Loseupdate = true;
		}
	// Game Win condition
	Check = 0;
	
		for (int i = 0; i < data.pObjMgr->GetObjectCount(); ++i)
		{
			if (pAnsObj[i].color == pObjects[i].color)
				Check++;
		}
		if (Loseupdate != true)
		{
			if (Check == data.xSize * data.ySize && BulletGone)
				Winupdate = true;
		}

	/******************************************************************************/
		/* KeyBoard */
	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::SetNextState(DS_SELECTLEVEL);
	if (WEInput::IsTriggered(WE_R))
		WEStateManager::Restart();

}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void GameLevel2Shutdown(void)
{
	LoseHUD::LoseHudShutdown();
	WinHud::WinHudShutdown();
	SetHud::SetHudShutdown();
	ShowLevel::ShowLevelShutdown();
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void GameLevel2Unload(void)
{
	SetHud::SetHudUnload();
	LoseHUD::LoseHudUnload();
	WinHud::WinHudUnload();
	ShowLevel::ShowLevelUnload();
	WEGraphics::UnloadTexture(data.Rect_ID);
	WEGraphics::UnloadTexture(data.Item_ID);
	WEGraphics::UnloadTexture(data.Ball_ID);
	WEGraphics::UnloadTexture(data.Background_ID);
	WEGraphics::UnloadTexture(Arrow::down);
	WEGraphics::UnloadTexture(Arrow::left);
	WEGraphics::UnloadTexture(Arrow::right);
	WEGraphics::UnloadTexture(Arrow::up);
	WEGraphics::UnloadTexture(data.Bullet_ID);
	WEGraphics::UnloadTexture(data.MaxBullet_ID);
	sound.releaseSound(Shooting);
	sound.releaseSound(BackGround);
	for (int i = 0; i < Ten; ++i)
	{
		WEGraphics::UnloadTexture(data.Num[i]);
	}
}


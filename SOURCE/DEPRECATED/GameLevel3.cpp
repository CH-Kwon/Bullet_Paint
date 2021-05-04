#include "GameLevel3.h"

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

#include "Actions.h"
#include "OBJ_M.h"
#include <cstdio>
#include <iostream>
class ObjectManager;
#define TileSize 10

namespace
{
	char* Level;
	Ball Player;
	const bool PlayerInit = true;
	int Xcount;
	int Ycount;
	int P_Color = 0; // player color
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
struct ObjectData1
{
	unsigned colors[C_COUNT];
	int Ball_ID;
	int Rect_ID;
	int objectcount;
	int xSize;
	int ySize;
	float xPos;
	float yPos;
	float ansXpos;
	float ansYpos;
	const int size = xSize * ySize;
	int ansColor;
	int tileColor;
	int itemNum; /* Number of Tile Where Item will be placed*/
	int itemAmount;
	ObjectManager * pObjMgr;
	ItemManager * pItemMgr;
};
ObjectData1 data;

void GameLevel3Load(void)
{
	data.Ball_ID = WEGraphics::LoadTexture("Textures\\Ball.tga");
	data.Rect_ID = WEGraphics::LoadTexture("Textures\\Rect.tga");

}

void GameLevel3Init(void)
{
	WEDEBUG_CREATE_CONSOLE();
	Xcount = 0;
	Ycount = 0;
	Level = "Level//Level2.txt";

	WEGraphics::SetBackgroundColor(255, 255, 255);

	// Color Setting
	data.colors[C_NORMAL] = 0xFFFFFFFF;
	data.colors[C_RED] = 0xFF0000FF;
	data.colors[C_GREEN] = 0xFF00FF00;
	data.colors[C_BLUE] = 0xFFFF0000;
	data.colors[C_BLACK] = 0xFF000000;
	data.colors[C_WHITE] = 0x00000000;
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

	//Player Initialize
	if (PlayerInit)
	{
		WEVec2 playerPos;
		playerPos.x = tilePos.x;
		playerPos.y = tilePos.y + TileSize;

		WEVec2 playerVel;
		playerVel.x = 0;
		playerVel.y = 0;

		Player.color = data.colors[C_NORMAL];
		Player.isclicked = false;
		Player.rotation = 0;
		Player.position.Set(playerPos.x, playerPos.y);
		Player.scale.Set(TileSize / 2, TileSize / 2);
		Player.vel.Set(playerVel.x, playerVel.y);
	}
	data.pObjMgr = new ObjectManager(data.xSize, data.ySize);
	WEVec2 placePos;
	WEVec2 placeScale;
	placeScale.x = tileScale.x / 2;
	placeScale.y = tileScale.y / 2;

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

	// Create Place Where Player Can Move
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
				data.pObjMgr->AddXPlace(placePos, placeScale, data.Ball_ID, data.colors[5]);
			}
			if (i == data.ySize - 1)
			{
				placePos.x = tilePos.x;
				placePos.y = tilePos.y - TileSize;
				data.pObjMgr->AddXPlace(placePos, placeScale, data.Ball_ID, data.colors[5]);
			}
			if (l == 0)
			{
				placePos.x = tilePos.x - TileSize;
				placePos.y = tilePos.y;
				data.pObjMgr->AddYPlace(placePos, placeScale, data.Ball_ID, data.colors[5]);
			}
		}
		tilePos.y -= tileScale.y;
		tilePos.x = data.xPos;
	}

	//tilePos.x = data.xPos;
	//tilePos.y = data.yPos;
	Object* pObjects = data.pObjMgr->GetObjects();
	// Create Place Where Player Can Move
	for (int i = 0; i < data.ySize; ++i)
	{
		tilePos.x += tileScale.x;
		for (int l = 0; l < data.xSize; ++l)
		{
			if (l == data.xSize - 1)
			{
				placePos.x = tilePos.x + (TileSize * (data.xSize + 1));
				placePos.y = tilePos.y - (TileSize * i);
				data.pObjMgr->AddYPlace(placePos, placeScale, data.Ball_ID, data.colors[5]);
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
		data.pItemMgr->AddItem(placePos, placeScale, data.Ball_ID, data.colors[0]);
	}
	// Close the File
	fclose(pFile);
}

void GameLevel3Update(float /*dt*/)
{
	Object* pObjects = data.pObjMgr->GetObjects();
	Object* pAnsObj = data.pObjMgr->GetAnsObj();
	Ball* pXPlaceObj = data.pObjMgr->GetXPlaceObj();
	Ball* pYPlaceObj = data.pObjMgr->GetYPlaceObj();
	Item* pItems = data.pItemMgr->GetItem();
	// WEDEBUG_PRINT("%lf %lf", pXPlaceObj[1].position.x, pXPlaceObj[1].position.y);
	WEMtx44 transform;
	//WEVec2 mouse;
	//WEInput::GetMouse(mouse);
	//WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);

	// Moving Player
	if (Xcount != data.xSize + 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_RIGHT))
		{
			Player.position.x += TileSize;
			++Xcount;
		}
	}
	if (Xcount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_LEFT))
		{
			Player.position.x -= TileSize;
			--Xcount;
		}
	}
	if (Ycount != data.ySize + 1)
	{
		if (WEInput::IsTriggered(WE_ARROW_DOWN))
		{
			Player.position.y -= TileSize;
			++Ycount;
		}
	}
	if (Ycount != 0)
	{
		if (WEInput::IsTriggered(WE_ARROW_UP))
		{
			Player.position.y += TileSize;
			--Ycount;
		}
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
	if (WEInput::IsTriggered(WE_4))
	{
		P_Color = C_BLACK;
	}

	//Changing Color of XPlaceObj To Change Color of Tiles
	if (WEInput::IsTriggered(WE_SPACE))
	{
		for (int i = 0; i < data.pObjMgr->GetXPlaceObjCount(); ++i)
		{
			if (WEIntersection::CircleCircle(pXPlaceObj[i].position, pXPlaceObj[i].scale.x / 2,
				Player.position, Player.scale.x / 2))
			{
				pXPlaceObj[i].color = data.colors[P_Color];
			}
		}
		for (int i = 0; i < data.pObjMgr->GetYPlaceObjCount(); ++i)
		{
			if (WEIntersection::CircleCircle(pYPlaceObj[i].position,
				pYPlaceObj[i].scale.x / 2,
				Player.position,
				Player.scale.x / 2))
			{
				pYPlaceObj[i].color = data.colors[P_Color];
			}
		}
	}

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
				for (int l = data.xSize - 1; l >= 0; --l)
				{
					if (pObjects[i* data.xSize + l].color != data.colors[C_BLACK])
						pObjects[i*data.xSize + l].color = pYPlaceObj[i + data.ySize].color;
					if (pObjects[i* data.xSize + l].color == data.colors[C_BLACK])
						l = 0;
				}
			}
			if (WEIntersection::CircleCircle(pXPlaceObj[i + data.xSize].position,
				pXPlaceObj[i + data.xSize].scale.x / 2,
				Player.position,
				Player.scale.x / 2))
			{
				for (int l = data.xSize - 1; l >= 0; --l)
				{
					if (pObjects[l* data.xSize + i].color != data.colors[C_BLACK])
					{
						pObjects[l*data.xSize + i].color = pXPlaceObj[i + data.xSize].color;
						/* boom item */
						//for (int n = 0; n < data.pItemMgr->GetItemCount(); ++n)
						//{
						//	if (pXPlaceObj[i + data.xSize].position.y == pItems[n].position.y)
						//	{
						//		pObjects[i* data.xSize + l].color = pXPlaceObj[i + data.xSize].color;
						//		pItems[n].used = true;
						//	}
						//}
					}
					if (pObjects[l*data.xSize + i].color == data.colors[C_BLACK])
						l = 0;
				}
			}
		}
	}

	/* boom item*/
	//for (int i = 0; i < data.pObjMgr->GetYPlaceObjCount() * 2; ++i)
	//{
	//	for (int n = 0; n < data.pItemMgr->GetItemCount(); ++n)
	//		if (pYPlaceObj[i].position.x == pItems[n].position.x)
	//		{
	//			pYPlaceObj[i].color = 
	//			pItems[n].used = true;
	//		}
	//}


	// Change Color of Vertical and Horizontal Tile
	if (WEInput::IsTriggered(WE_SPACE))
	{
		for (int i = 0; i < data.ySize; ++i)
		{
			if (WEIntersection::CircleCircle(Player.position, Player.scale.x / 2,
				pYPlaceObj[i].position, pYPlaceObj[i].scale.x / 2))
			{
				for (int l = 0; l < data.xSize; ++l)
				{
					if (pObjects[i* data.xSize + l].color != data.colors[C_BLACK])
						pObjects[i*data.xSize + l].color = pYPlaceObj[i].color;
					if (pObjects[i* data.xSize + l].color == data.colors[C_BLACK])
						i = data.xSize;
				}
			}
			if (WEIntersection::CircleCircle(Player.position, Player.scale.x / 2,
				pXPlaceObj[i].position, pXPlaceObj[i].scale.x / 2))
			{
				for (int l = 0; l < data.xSize; ++l)
				{
					if (pObjects[l* data.xSize + i].color != data.colors[C_BLACK])
						pObjects[l*data.xSize + i].color = pXPlaceObj[i].color;
					if (pObjects[l*data.xSize + i].color == data.colors[C_BLACK])
						l = data.xSize;
				}
			}
		}
	}

	WEGraphics::SetToPerspective();/*Draw in world space*/

	WEGraphics::StartDraw();/*We must call this before drawing anything*/

							/* Draw Tiles */
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

	/* Draw Answer Tiles */
	for (int i = 0; i < data.pObjMgr->GetAnsObjCount(); ++i)
	{
		WEGraphics::SetTexture(pAnsObj[i].texture);
		WEGraphics::SetTextureColor(pAnsObj[i].color);
		WEMtx44::MakeTransform(transform,
			pAnsObj[i].scale.x, pAnsObj[i].scale.y,
			0,
			pAnsObj[i].position.x, pAnsObj[i].position.y, 0.f);
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

	/* Draw Player */
	WEGraphics::SetTexture(data.Ball_ID);
	WEGraphics::SetTextureColor(data.colors[P_Color]);
	WEMtx44::MakeTransform(transform,
		Player.scale.x, Player.scale.y,
		Player.rotation,
		Player.position.x, Player.position.y, 0.f);
	WEGraphics::Draw(transform);


	WEGraphics::EndDraw(); /* End Drawing */

	for (int i = 0; i < data.pObjMgr->GetObjectCount(); ++i)
	{
		if (pAnsObj[i].color == pObjects[i].color)
			WEStateManager::GetNextState();
	}
}

void GameLevel3Shutdown(void)
{
}

void GameLevel3Unload(void)
{
	WEGraphics::UnloadTexture(data.Rect_ID);
	WEGraphics::UnloadTexture(data.Ball_ID);
}


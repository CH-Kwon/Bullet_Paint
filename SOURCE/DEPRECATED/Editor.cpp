#include "OMDemo.h"

#include "WEDebugTools.h"
#include "WEApplication.h"
#include "WEStateManager.h"
#include "WEInput.h"
#include "WEGraphics.h"
#include "WEMath.h"
#include "WERandom.h"
#include "WEIntersection.h"

#include "ObjectManager.h"

#include <cstdio> /*sprintf, fopen, fclose, FILE*/
#include <iostream>
#include <fstream>
namespace
{
  /*State constants*/
  /*Camera Info*/
  const float CAMERA_X = 0.f;
  const float CAMERA_Y = 0.f;
  const float CAMERA_Z = 60.f;
  const float CAMERA_ROT = 0.f;

  //Button size
  const float BUTTON_HEIGHT = 64.f;
  const float BUTTON_WIDTH = 128.f;
  int C_color = 0;
  bool CLICK_CHECK = true;
  int		xsize = 0;
  int		ysize = 0;
  int		grid = 0;
  /*Color Info*/
  enum Colors
  {
    C_NORMAL, /*0*/
    C_RED,    /*1*/
    C_BLUE,   /*2*/
    C_BLACK,  /*3*/
	C_GREEN,  /*4*/
	C_WHITE,  /*5*/
    C_COUNT   /*6*/
  };

  /*Text Info*/
  const float TEXT_HEIGHT = 16;
  const float TEXT_START  = 5;
  const int MAX_BUFFER  = 20;

struct OMDemoData
{
  unsigned colors[C_COUNT];
  WEVec2   botLeft;
  WEVec2   topLeft;
  WEVec2   botRight;
  int      heartID;
  int      exitID;
  int      reloadID;
  int      createID;
  int      createMaxID;

  //file data
  char     buffer[MAX_BUFFER];
  float    minScale;
  float    maxScale;
  int      maxObjects;

  //Our object Manager 
  ObjectManager* pObjMgr;
};
OMDemoData data;

/******************************************************************************/
/*!
Used to create a random object in the object Manager
*/
/******************************************************************************/
void CreateObject(int count)
{
	WEVec2 pos;
	pos.x = -60;
	pos.y = 40;
	int objx_count = 1;
	count = 0;
	WEVec2 obj_scale;
	obj_scale.x = 10;
	obj_scale.y = 10;
	for (int i = 0; i < ysize; ++i)
	{
		pos.y -= obj_scale.y;
		pos.x = -60;
		for (int l = 0; l < xsize; ++l)
		{
			float obj_rot = 0;
				pos.x += obj_scale.x;
			++objx_count;
			/*Add to the object manager*/
			data.pObjMgr->AddObject(pos, obj_rot,
				obj_scale,
				data.heartID,
				data.colors[C_NORMAL]);
		}
	}
}
/******************************************************************************/
/*!
Loads my object properties from a file

\param fileName
The file to read text from.

\attention
There is no error checking done on the file.
*/
/******************************************************************************/
void LoadFile(const char* fileName)
{
  FILE* pFile = 0;
  fopen_s(&pFile, fileName, "rt");
  WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
  fscanf_s(pFile, "%d", &data.maxObjects);
  fclose(pFile);
}
/******************************************************************************/
/*!
Calls quit on the StateManager, used as a Button Action.
*/
/******************************************************************************/
void ExitAction(void)
{
  WEStateManager::Quit();
}
/******************************************************************************/
/*!
Calls restart on the StateManager, used as a Button Action.
*/
/******************************************************************************/
void ReloadAction(void)
{
  WEStateManager::Restart();
}
/******************************************************************************/
/*!
Creates a single game object, used as a Button Action
*/
/******************************************************************************/
void CreateObjectAction(void)
{
	++xsize;
	++ysize;
	CreateObject(grid);
}
}//end unnamed namespace




/******************************************************************************/
/*!
Load my resources and sets values that wont need to change ever.
*/
/******************************************************************************/
void OMDemoLoad(void)
{ 
  
  /*For this demo these don't need to change*/
  WEGraphics::SetCamera(CAMERA_X, CAMERA_Y, CAMERA_Z, CAMERA_ROT);
  WEGraphics::SetBackgroundColor(1.f, 1.f, 1.f);/*White background*/

  data.heartID     = WEGraphics::LoadTexture("Textures//Heart.tga");
  data.exitID      = WEGraphics::LoadTexture("Textures//Exit.tga");
  data.reloadID    = WEGraphics::LoadTexture("Textures//Reload.tga");
  data.createID    = WEGraphics::LoadTexture("Textures//Create.tga");
  data.createMaxID = WEGraphics::LoadTexture("Textures//CreateMax.tga");
 

  data.colors[C_NORMAL] = 0xFFFFFFFF; /*This is the regular texture color*/
  data.colors[C_RED]    = 0xFF0000FF;
  data.colors[C_BLUE]   = 0xFFFF0000;
  data.colors[C_BLACK]  = 0xFF000000;
  data.colors[C_GREEN] = 0xFF00FF00;
  data.colors[C_WHITE] = 0x0000000;
}
/******************************************************************************/
/*!
Just initialize the values here.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void OMDemoInit(void)
{
  /*We might reload and change the number of max objects*/
  LoadFile("ObjectProperties.txt");
  grid = xsize * ysize;
  data.pObjMgr = new ObjectManager(data.maxObjects, 4);
  float screenWidth = (float)WEApplication::GetWidth();
  //Add My Buttons
  WEVec2 pos;
  WEVec2 scale;

  scale.x = BUTTON_WIDTH;
  scale.y = BUTTON_HEIGHT;

  pos.x = BUTTON_WIDTH / 2;
  pos.y = BUTTON_HEIGHT / 2;
  data.pObjMgr->AddButton(pos, scale, data.reloadID, ReloadAction);
  pos.x = screenWidth * .25f + BUTTON_WIDTH / 2;
  pos.y = BUTTON_HEIGHT / 2;
  data.pObjMgr->AddButton(pos, scale, data.createID, CreateObjectAction);
  pos.x = screenWidth * .75f - BUTTON_WIDTH / 2;
  pos.y = BUTTON_HEIGHT / 2;
  data.pObjMgr->AddButton(pos, scale, data.createMaxID, CreateObjectAction);
  pos.x = screenWidth - BUTTON_WIDTH / 2;
  pos.y = BUTTON_HEIGHT / 2;
  data.pObjMgr->AddButton(pos, scale, data.exitID, ExitAction);
}
/******************************************************************************/
/*!
This is the update.  All of the input and game logic is here for this state.

\param pGameData
A pointer to the shared gameData.

\param dt
*/
/******************************************************************************/
void OMDemoUpdate(float /*dt*/)
{

  WEMtx44 transform;
  WEVec2 mouse;
  WEInput::GetMouse(mouse);
  WEGraphics::GetWorldBotLeft(data.botLeft);
  WEGraphics::GetWorldTopLeft(data.topLeft);
  WEGraphics::GetWorldBotRight(data.botRight);

  /*Check inputs**************************************************************/
  if (WEInput::IsTriggered(WE_MOUSE_LEFT))
  {
    for (int i = 0; i < data.pObjMgr->GetButtonCount(); ++i)
    {
      //Get pointer for less typing
      Button* pButtons = data.pObjMgr->GetButtons();
      if (WEIntersection::PointRect(mouse, pButtons[i].position,
        pButtons[i].scale.x,
        pButtons[i].scale.y))
      {
        pButtons[i].action();
      }
    }
  }


  /*Check inputs**************************************************************/

  /*Update Game Behavior******************************************************/
  WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);
  Object* pObjects = data.pObjMgr->GetObjects();
  for(int i = 0; i < data.pObjMgr->GetObjectCount(); ++i)
  {
	  if (WEIntersection::PointRect(mouse, pObjects[i].position, pObjects[i].scale.x, pObjects[i].scale.y))
	  {
		  if (WEInput::IsTriggered(WE_MOUSE_LEFT))
		  {
			  pObjects[i].isclicked = true;
			  pObjects[i].color = data.colors[C_GREEN];
		  }
		  if (WEInput::IsTriggered(WE_MOUSE_RIGHT))
		  {
			  pObjects[i].isclicked = false;
		  }
	  }
    if(pObjects[i].position.x > data.botRight.x)
      data.pObjMgr->DeleteObject(pObjects[i].objectID);
  }
  sprintf_s(data.buffer, MAX_BUFFER, "Object Count: %d", 
    data.pObjMgr->GetObjectCount());
  /*Update Game Behavior******************************************************/
  
  /*Draw objects**************************************************************/
  WEGraphics::SetToPerspective();/*Draw in world space*/
  
  WEGraphics::StartDraw();/*We must call this before drawing anything*/


	  for (int i = 0; i < data.pObjMgr->GetObjectCount(); ++i)
	  {
		  if (pObjects[i].isclicked)
		  {
			  if (WEInput::IsTriggered(WE_1))
				  pObjects[i].color = data.colors[C_RED];
			  if (WEInput::IsTriggered(WE_2))
				  pObjects[i].color = data.colors[C_BLUE];
			  if (WEInput::IsTriggered(WE_3))
				  pObjects[i].color = data.colors[C_BLACK];
			  if (WEInput::IsTriggered(WE_4))
				  pObjects[i].color = data.colors[C_WHITE];
		  }
	  }

  for(int i = 0; i < data.pObjMgr->GetObjectCount(); ++i)
  {
    WEGraphics::SetTexture(pObjects[i].texture);
    WEGraphics::SetTextureColor(pObjects[i].color);
    WEMtx44::MakeTransform(transform,
      pObjects[i].scale.x, pObjects[i].scale.y,
      pObjects[i].rotation,
      pObjects[i].position.x, pObjects[i].position.y, 0.f);
    WEGraphics::Draw(transform);
  }
  std::ofstream outfile("GameLevel.txt");
  if (outfile.is_open())
  {
	  outfile << xsize << " " << ysize << std::endl;
	  for (int i = 0; i < grid + 1; ++i)
	  {
		  //if (pObjects[i].color == 0)
		  // outfile << pObjects[i].color << " " << pObjects[i].position.x << " " << pObjects[i].position.y << std::endl;
		  //else
		  outfile << std::hex << pObjects[i].color << " " << std::dec << pObjects[i].position.x << " " << pObjects[i].position.y << std::endl;
	  }
  }
  /*Draw Hud******************************************************************/
  WEGraphics::SetToOrtho();/*Draw in screen space*/
  WEGraphics::SetTextureColor(data.colors[C_NORMAL]);

  Button* pButtons = data.pObjMgr->GetButtons();

  for(int i = 0; i < data.pObjMgr->GetButtonCount(); ++i)
  {
    WEGraphics::SetTexture(pButtons[i].texture);

    WEMtx44::MakeTransform(transform,
      pButtons[i].scale.x, pButtons[i].scale.y,
      0.f,
      pButtons[i].position.x, pButtons[i].position.y, 0.f);

    WEGraphics::Draw(transform);
  }
  WEGraphics::EndDraw();/*We must call this after all drawing*/


}
/******************************************************************************/
/*!
Clear the ObjectManager pointer
*/
/******************************************************************************/
void OMDemoShutdown(void)
{
  delete data.pObjMgr;
  data.pObjMgr = 0;
}
/******************************************************************************/
/*!
Unload my textures
*/
/******************************************************************************/
void OMDemoUnload(void)
{
  WEGraphics::UnloadTexture(data.heartID);
  WEGraphics::UnloadTexture(data.exitID);
  WEGraphics::UnloadTexture(data.reloadID);
  WEGraphics::UnloadTexture(data.createID);
  WEGraphics::UnloadTexture(data.createMaxID);
}
#include "Cool.h"

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

#include "GameTypes.h"
#include "Actions.h"
#include <iostream>

enum Colors
{
	C_NORMAL, /*0*/
	C_RED,    /*1*/
	C_BLUE,   /*2*/
	C_BLACK,  /*3*/
	C_WHITE, /*4*/
	C_COUNT   /*5*/
};

namespace {
	const float TEXT_HEIGHT = 16;
	const float TEXT_START = 5;
	const int MAX_BUFFER = 20;
	const int max_object = 10;
	const int N = 3;
	Object obj[max_object];
	Object R_tile[N];
	Object C_tile[N];
	Object Ans_tile[max_object - 1];
	float winH;
	float winW;
	int B_Color = 0;
	int Click_Color = 0;
	BOOLEAN Clicked = false;
	float timeCount = 0;
	const float maxTime = 1.f;
}
struct ObjectData
{
	unsigned colors[C_COUNT];
	int Ball_ID;
	int Rect_ID;
	int objectcount;
	char Score[10];
	char Remain[10];
	char Max[10];
	int set_score1 = 0;
	int set_score2 = 0;
};
static ObjectData data;
void CoolLoad(void) {
	data.Ball_ID = WEGraphics::LoadTexture("Textures\\Ball.tga");
	data.Rect_ID = WEGraphics::LoadTexture("Textures\\Rect.tga");
}
void CoolInit(void)
{
	WEDEBUG_CREATE_CONSOLE();
	data.colors[C_NORMAL] = 0xFFFFFFFF;
	data.colors[C_RED] = 0xFF0000FF;
	data.colors[C_BLUE] = 0xFFFF0000;
	data.colors[C_BLACK] = 0xFF000000;
	data.colors[C_WHITE] = 0x00000000;

	data.Max;
	data.Remain;
	data.Score;
	data.set_score1 = 0;
	data.set_score2 = 0;

	//Get WindowData
	float x = -50;
	float y = -20;
	int i = 0;
	int count = 1;
  winH = (float)WEApplication::GetHeight();
  winW  = (float)WEApplication::GetWidth();
  WEGraphics::SetBackgroundColor(255,255,255);
  for (data.objectcount = 0; data.objectcount < max_object-1; ++data.objectcount)
  {
	  Ans_tile[data.objectcount].u_color = data.colors[C_RED];
	  Ans_tile[data.objectcount].isActive = false;
	  Ans_tile[data.objectcount].life = 0;
	  Ans_tile[data.objectcount].scale.Set(10, 10);
	  Ans_tile[data.objectcount].texture = data.Rect_ID;
	  obj[data.objectcount].u_color = data.colors[C_NORMAL];
	  obj[data.objectcount].isActive = false;
	  obj[data.objectcount].life = 0;
	  obj[data.objectcount].vel.Set(0, 0);
	  obj[data.objectcount].force.Set(0, 0);
	  obj[data.objectcount].scale.Set(10, 10);
	  obj[data.objectcount].texture = data.Rect_ID;
	  if (count%3 == 1)
	  {
		  y += 10;
		  x = -10;
	  }
	  else
		  x += 10;
	  obj[data.objectcount].pos.Set(x, y);
	  Ans_tile[data.objectcount].pos.Set(x +85, y + 40);
	  ++count;
	  if (data.objectcount%4==0)
	  {
		  float a = x + i ;
		  float b = y - i ;
		  C_tile[i].u_color = data.colors[C_NORMAL];
		  C_tile[i].pos.Set(a, -20);
		  C_tile[i].scale.Set(5, 5);
		  C_tile[i].isActive = false;
		  C_tile[i].texture = data.Ball_ID;
		  R_tile[i].u_color = data.colors[C_NORMAL];
		  R_tile[i].pos.Set(-20, b);
		  R_tile[i].scale.Set(5, 5);
		  R_tile[i].isActive = false;
		  R_tile[i].texture = data.Ball_ID;
		  ++i;	
	  }
  }
  obj[9].u_color = 0;
  obj[9].life = 0;
  obj[9].isActive = false;
  obj[9].pos.Set(0, 0);
  obj[9].scale.Set(5, 5);
  obj[9].vel.Set(0, 0);
  obj[9].force.Set(0, 0);
  obj[9].texture = data.Ball_ID;
  Ans_tile[4].u_color = data.colors[C_BLUE];
}
void CoolUpdate(float  dt)
{
	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::Quit();
	WEVec2 mouse;
	WEInput::GetMouse(mouse);
	WEGraphics::ConvertScreenToWorld(mouse.x, mouse.y);
	WEMtx44 transform;
	if (WEInput::IsTriggered(WE_1))
	{
		B_Color = C_RED;
		Clicked = true;
	}
	if (WEInput::IsTriggered(WE_2))
	{
		B_Color = C_BLUE;
		Clicked = true;
	}
	if (WEInput::IsTriggered(WE_3))
	{
		B_Color = C_BLACK;
		Clicked = true;
	}
		if(WEInput::IsTriggered(WE_MOUSE_LEFT))
		{
			for (int i = 0; i < N; ++i)
			{
				if (WEIntersection::CircleCircle(mouse, obj[9].scale.x / 2.0f, C_tile[i].pos, C_tile[i].scale.x / 2.0f))
				{
					if (Clicked)
						++data.set_score1;
					C_tile[i].u_color = data.colors[B_Color];
					for (int l = 0; l <N; ++l/*data.objectcount = 0; data.objectcount < max_object - 1; ++data.objectcount*/)
					{
						obj[i+N*l].u_color = C_tile[i].u_color;
							/*if (data.objectcount % 3 == 0)	       obj[data.objectcount].u_color = C_tile[0].u_color;
							if (data.objectcount % 3 == 1)  obj[data.objectcount].u_color = C_tile[1].u_color;
							if (data.objectcount % 3 == 2)	obj[data.objectcount].u_color = C_tile[2].u_color;	*/
					}
				} 
			}
			if (WEInput::IsTriggered(WE_MOUSE_LEFT))
			{
				for (int i = 0; i < N; ++i)
				{
					if (WEIntersection::CircleCircle(mouse, obj[9].scale.x / 2.0f, R_tile[i].pos, R_tile[i].scale.x / 2.0f))
					{
						if (Clicked)
							data.set_score2++;
						R_tile[i].u_color = data.colors[B_Color];
						for(int l = 0; l < N; ++l)
							obj[i*N+l].u_color = R_tile[i].u_color;
					}
				}
			}
		}
		sprintf_s(data.Score, "%d", (data.set_score1) + (data.set_score2));
		sprintf_s(data.Remain,"%d", 5 - (data.set_score1 + data.set_score2));
		sprintf_s(data.Max,   "%d", 5);
        
		if (data.set_score1 + data.set_score2 == 5)
			WEStateManager::SetNextState(DS_GAMEOVER);

		timeCount += dt;
		int check = 0;
		for (data.objectcount = 0; data.objectcount < max_object - 1; ++data.objectcount)
		{
			if (obj[data.objectcount].u_color == Ans_tile[data.objectcount].u_color)
				++check;
			if(check == 9)
				WEStateManager::SetNextState(DS_GAMEWIN);
		}
	WEGraphics::StartDraw();/*We must call this before drawing anything*/
	WEGraphics::SetToPerspective();
	WEGraphics::SetTexture(data.Rect_ID);
	WEGraphics::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	for (data.objectcount = 0; data.objectcount < max_object-1; ++data.objectcount)
	{
		WEGraphics::SetTextureColor(obj[data.objectcount].u_color);
		WEMtx44::MakeTransform(transform,
			obj[data.objectcount].scale.x,
			obj[data.objectcount].scale.y,
			0.0f,
			obj[data.objectcount].pos.x,
			obj[data.objectcount].pos.y, 
			1.0f);

		WEGraphics::Draw(transform);
	}
	for (data.objectcount = 0; data.objectcount < max_object - 1; ++data.objectcount)
	{
		WEGraphics::SetTextureColor(Ans_tile[data.objectcount].u_color);
		WEMtx44::MakeTransform(transform,
			Ans_tile[data.objectcount].scale.x,
			Ans_tile[data.objectcount].scale.y,
			0.0f,
			Ans_tile[data.objectcount].pos.x,
			Ans_tile[data.objectcount].pos.y,
			1.0f);
		WEGraphics::Draw(transform);
	}
	WEGraphics::SetTexture(data.Ball_ID);
	WEGraphics::SetTextureColor(data.colors[B_Color]);
		WEMtx44::MakeTransform(transform,
			obj[9].scale.x,
			obj[9].scale.y,
			0.0f,
			mouse.x,
			mouse.y,
			2.0f);
		WEGraphics::Draw(transform);
		WEGraphics::SetTexture(data.Ball_ID);
		for (int i = 0; i < N; ++i)
		{
			WEGraphics::SetTextureColor(R_tile[i].u_color);
			WEMtx44::MakeTransform(transform,
				R_tile[i].scale.x,
				R_tile[i].scale.y,
				0.0f,
				R_tile[i].pos.x,
				R_tile[i].pos.y,
				1.0f);
			WEGraphics::Draw(transform);
		}
		for (int i = 0; i < N; ++i)
		{
			WEGraphics::SetTextureColor(C_tile[i].u_color);
			WEMtx44::MakeTransform(transform,
				C_tile[i].scale.x,
				C_tile[i].scale.y,
				0.0f,
				C_tile[i].pos.x,
				C_tile[i].pos.y,
				1.0f);
			WEGraphics::Draw(transform);
		}
		WEGraphics::SetTextureColor(data.colors[C_BLACK]);
		WEGraphics::WriteText("Max Count : ", 70, 20);
		WEGraphics::WriteText(data.Max, 95, 20);

		WEGraphics::SetTextureColor(data.colors[C_BLACK]);
		WEGraphics::WriteText("Remain : ", 70, 0);
		WEGraphics::WriteText(data.Remain, 95, 0);

		WEGraphics::SetTextureColor(data.colors[C_BLACK]);
		WEGraphics::WriteText("Click Count : ", 70, 10);
		WEGraphics::WriteText(data.Score, 95, 10);

		WEGraphics::EndDraw();
}
void CoolShutdown(void)
{
}
void CoolUnload(void)
{
	WEGraphics::UnloadTexture(data.Rect_ID);
	WEGraphics::UnloadTexture(data.Ball_ID);
}
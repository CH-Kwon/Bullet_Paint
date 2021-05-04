/******************************************************************************/
/*!
\file   Main.c
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

This is file contains the main function to make a basic window. 
*/
/******************************************************************************/

/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/
#if defined(DEBUG) | defined(_DEBUG) 
#define CRTDBG_MAP_ALLOC 
#include <cstdlib>  
#include <crtdbg.h> 
#endif 
/******************************************************************************/
#include <windows.h> /*WinMain*/ 

/*Include the engine functions*/
#include "WEApplication.h"
#include "WEStateManager.h"
#include "WEState.h"
#include "WEGameData.h"

/*My GameStates*/
#include "DigipenLogo.h"
#include "FMOD.h"
#include "Credit.h"
#include "MainMenu.h"
#include "GameLevelSelect.h"
#include "GameLevel2.h"
#include "WinHud.h"


/******************************************************************************/
/*!
The user must add states to their game After initializing the Application, and 
before updating the Application.

\attention
To make switching states easier, I add the states in the order they are listed
in the DemoStates enum.
*/
/******************************************************************************/
void DemoAddStates(void)
{
  WEState state;

  state.Load = DigipenLogoLoad;
  state.Init = DigipenLogoInit;
  state.Update = DigipenLogoUpdate;
  state.Shutdown = DigipenLogoShutdown;
  state.Unload = DigipenLogoUnload;

  int startState = WEStateManager::AddState(state);
  WEStateManager::SetStartState(startState);

  state.Load = FMODLoad;
  state.Init = FMODInit;
  state.Update = FMODUpdate;
  state.Unload = FMODUnload;
  state.Shutdown = FMODShutdown;

  WEStateManager::AddState(state);

  state.Load = CreditLoad;
  state.Init = CreditInit;
  state.Update = CreditUpdate;
  state.Unload = CreditUnload;
  state.Shutdown = CreditShutdown;

  WEStateManager::AddState(state);

  state.Load = MenuStateLoad;
  state.Init = MenuStateInit;
  state.Update = MenuStateUpdate;
  state.Unload = MenuStateUnload;
  state.Shutdown = MenuStateShutdown;

  WEStateManager::AddState(state);

  state.Load = GameLevelSelectLoad;
  state.Init = GameLevelSelectInit;
  state.Update = GameLevelSelectUpdate;
  state.Unload = GameLevelSelectUnload;
  state.Shutdown = GameLevelSelectShutdown;

  WEStateManager::AddState(state);

  state.Load = GameLevel2Load;
  state.Init = GameLevel2Init;
  state.Update = GameLevel2Update;
  state.Unload = GameLevel2Unload;
  state.Shutdown = GameLevel2Shutdown;

  WEStateManager::AddState(state);
}

/******************************************************************************/
/*!

\brief
The main function for a windowed program.

\param instance 
An identifier for the process.  This is used for various windows things.

\param prev
This is not used anymore, we can ignore it.

\param comamndLine
A string that is comes from the typed command line.  In games we usually don't
care.

\param show 
A variable stating if the window is visible, we always want it visible.

\return
An Error code.  Just return 0;
*/
/******************************************************************************/
#pragma warning(suppress: 28251)
int WINAPI WinMain(HINSTANCE instance,
                   HINSTANCE /*prev*/, 
                   LPSTR /*commandLine*/, 
                   int /*show*/)
{
  /*This code will help find memory leaks in your code you should add
  this to main.*/
#if defined(DEBUG) | defined(_DEBUG)
  /* This will call _CrtDumpMemoryLeaks() on program exit.*/
  _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
  /*To show memory leaks in the output window */
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

  /* If you have a leak, there is a number in curly braces next to the error.
     Put that number in this function and check the call stack to see when and
     where the allocation happened. Set it to -1 to have it not break.*/
  _CrtSetBreakAlloc(-1);
#endif

  /*Declare my InitStruct*/
  WEInitData initStruct;
  /*Create my game data initial values*/
  WEGameData gameData = { 0 };

  /*Set up my InitStruct*/
  initStruct.instance   = instance;
  initStruct.width      = 1280;
  initStruct.height     = 720;
  initStruct.title      = "Bullet Paint";
  initStruct.fps        = 60;
  initStruct.fullScreen = true;

  /*Information about your specific gamedata */
  initStruct.pGData       = &gameData;
  initStruct.gameDataSize = sizeof(WEGameData);

  /*Pass InitStruct to Function.  This function must be called first!!!*/
  WEApplication::Init(initStruct);
  /*Function to add all of my game states*/
  DemoAddStates();
  /*Start running the game*/
  WEApplication::Update();
  /*This function must be called after the window has closed!!!*/
  WEApplication::Shutdown();

  return 0;
}	


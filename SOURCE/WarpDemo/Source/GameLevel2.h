#ifndef GAMELEVEL2_H
#define GAMELEVEL2_H
/******************************************************************************/
/*!
file    GameLevel2.h
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/3/27
All content © 2017 DigiPen (USA) Corporation, all rights reserved.

The GameLevel2 state is used for reading every game Levels by Text file.
*/
/******************************************************************************/
void GameLevel2Load(void); 
void GameLevel2Init(void);  
void GameLevel2Update(float dt);
void GameLevel2Shutdown(void);
void GameLevel2Unload(void);
#endif
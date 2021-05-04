/******************************************************************************/
/*!
\file   WEDefaultState.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2015/12/6

Default State incase the user didn't add there own states
*/
/******************************************************************************/
#ifndef INITSTATE_H
#define INITSTATE_H


void DefaultLoad(void);
void DefaultInit(void);
void DefaultUpdate(float dt);
void DefaultShutdown(void);
void DefaultUnload(void);


#endif /* INITSTATE_H */
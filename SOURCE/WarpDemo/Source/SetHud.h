/******************************************************************************/
/*!
file    SetHud.h
\author Chiho Kwon
\par    email: erpo0811@gmail.com
\par    class: GAM150
\date   2016/5/4

\breif
SetHud state is used to set hud(restart, level select button, button) to let
player know
*/
/******************************************************************************/
#ifndef SET_H
#define SET_H

class SetHud
{
public:
	static void SetHudLoad(void);
	static void SetHudInit(void);
	static void SetHudUpdate(float);
	static void SetHudShutdown(void);
	static void SetHudUnload(void);
};


#endif /* SPLASHSTATE_H */


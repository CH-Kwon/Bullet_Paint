/******************************************************************************/
/*!
file    LoseHud.h
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/5/27

\breif
The WinHud is used for Win condition HUD.
*/
/******************************************************************************/
#ifndef WIN_H
#define WIN_H

class WinHud
{
public:
	static void WinHudLoad(void);
	static void WinHudInit(void);
	static void WinHudUpdate(float);
	static void WinHudShutdown(void);
	static void WinHudUnload(void);
};


#endif /* SPLASHSTATE_H */


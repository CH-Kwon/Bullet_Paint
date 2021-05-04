/******************************************************************************/
/*!
file    LoseHud.h
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/5/31

\breif
The LoseHud is really used for Lose condition HUD.
*/
/******************************************************************************/
#ifndef LOSEHUD_H
#define LOSEHUD_H

class LoseHUD
{
public:
	static void LoseHudLoad(void);
	static void LoseHudInit(void);
	static void LoseHudUpdate(float);
	static void LoseHudShutdown(void);
	static void LoseHudUnload(void);
};

#endif // !LOSEHUD_H

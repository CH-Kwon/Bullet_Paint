/******************************************************************************/
/*!
file    ShowLevel.h
\author Chiho Kwon
\par    email: erpo0811@gmail.com
\par    class: GAM150
\date   2016/5/5

\breif
ShowLevel state is to show that what level player is doing
*/
/******************************************************************************/
#ifndef SHOWLEVEL_H
#define SHOWLEVEL_H

//class of showlevel to use in game playing.
class ShowLevel
{
public:
	static void ShowLevelLoad(void);
	static void ShowLevelInit(void);
	static void ShowLevelUpdate(float);
	static void ShowLevelShutdown(void);
	static void ShowLevelUnload(void);
};


#endif /* SPLASHSTATE_H */


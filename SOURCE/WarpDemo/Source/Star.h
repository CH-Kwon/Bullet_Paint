/******************************************************************************/
/*!
file    Star.h
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date 2017 06/ 01

\breif
Star System Header file
*/
/******************************************************************************/
#ifndef  STAR_H
#define STAR_H

class Star
{
public:
	Star();
	void SetMaxMin(int max, int min);
	static int StarCount();
	void StarAmount(int Bullet);
private:
	int _bulletmin;
	int _bulletmax;
	static int _starCount;
	static int count;
	bool once;
};


#endif // ! STAR_H


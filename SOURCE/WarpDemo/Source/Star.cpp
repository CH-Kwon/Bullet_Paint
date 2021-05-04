/******************************************************************************/
/*!
\file   Star.cpp
\author kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    GAM150
\date   2017/06/02

This is file contains the function for grading system.
*/
/******************************************************************************/
#include "Star.h"
int Star::_starCount;
int Star::count;
/******************************************************************************/
/*!
Star class consturctor
*/
/******************************************************************************/
Star::Star()
{
	_bulletmax = 0;
	_bulletmin = 0;
	_starCount = 0;
	once = true;
}
/******************************************************************************/
/*!
Star class Set function
*/
/******************************************************************************/
void Star::SetMaxMin(int max, int min)
{
	_bulletmax = max;
	_bulletmin = min;
	once = true;
	_starCount = 3;
	count = 0;
}
/******************************************************************************/
/*!
Star class get function
*/
/******************************************************************************/
int Star::StarCount()
{
	return _starCount;
}
/******************************************************************************/
/*!
Function that checks how many stars player gets.
*/
/******************************************************************************/
void Star::StarAmount(int Bullet)
{
	if (once)
	{
		++count;
		if (_bulletmax >= Bullet && _bulletmin <= Bullet)
		{

			if (count == 1)
			{
				_starCount = 3;
			}
			else if (count == 2)
				_starCount = 2;
			else
				_starCount = 1;
		}
		once = false;
	}
}

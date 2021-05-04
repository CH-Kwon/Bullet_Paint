#ifndef GAMETYPES_H
#define GAMETYPES_H

#include "WEVec2.h"

typedef void(*Action)(void);

#define ALPHA  0
#define RED    1
#define BLUE   2
#define GREEN  3
#define COLORS 4

struct Color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
struct Button
{
  WEVec2 pos;
  WEVec2 scale;
  WEVec2 texPos;
  Action action;
  int texture;
};

struct Object
{
  WEVec2 pos;
  WEVec2 vel;
  WEVec2 scale;
  WEVec2 force;
  float  life;
  bool isActive;
  Color color;
  unsigned u_color;
  int texture;
};
struct Ball
{
	WEVec2 pos;
	WEVec2 scale;
	unsigned u_color;
	int texture;
};


#endif
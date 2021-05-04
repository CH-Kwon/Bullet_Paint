/******************************************************************************/
/*!
file    OBJ_M.H
\author Kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    class: GAM150
\date   2017/5/27

ObjectManager Header file.
\breif Declaration of fuction for ObjectManaging
*/
/******************************************************************************/
#ifndef OBJ_M_H
#define OBJ_M_H

#include "WEVec2.h"
/******************************************************************************/
/*!
\par
struct Object
struct Ball
struct Bullet
struct Item
\date

\breif
Object for Tiles, Ball for Player and item, Bullet for Shooting
*/
/******************************************************************************/
struct Object
{
	WEVec2 position;
	WEVec2 scale;
	int texture;
	unsigned color;
	bool isclicked;
};
struct Ball
{
	WEVec2 vel;
	WEVec2 position;
	WEVec2 scale;
	float rotation;
	int texture;
	unsigned color;
	bool isclicked;
};
struct Bullet
{
	WEVec2 vel;
	WEVec2 position;
	WEVec2 scale;
	int texture;
	int objectID;
	unsigned color;
	bool isCollided;
};
class ObjectManager
{
public:
	ObjectManager(int _xsize, int _ysize);
	~ObjectManager();

	Object* GetObjects(void);
	Object* GetAnsObj(void);
	Ball* GetXPlaceObj(void);
	Ball* GetYPlaceObj(void);
	Bullet* GetBullets(void);
	int GetObjectCount(void) const;
	int GetAnsObjCount(void) const;
	int GetXPlaceObjCount(void) const;
	int GetYPlaceObjCount(void) const;
	int GetBulletCount(void) const;

	void AddObject(
		const WEVec2& pos,
		const WEVec2& scale,
		int texture,
		unsigned color
	);
	void AddAnsObj(
		const WEVec2& pos,
		const WEVec2& scale,
		int texture,
		unsigned color
	);
	void AddXPlace(
		const WEVec2& pos,
		const WEVec2& scale,
		int texture,
		unsigned color
	);
	void AddYPlace(
		const WEVec2& pos,
		const WEVec2& scale,
		int texture,
		unsigned color
	);
	void AddBullet(
		const WEVec2& vel,
		const WEVec2& position,
		const WEVec2& scale,
		int texture,
		unsigned color
	);
	void DeleteBullet (int objectID);
private:
	Object *m_object;
	Object *m_ansTile;
	Ball *m_Xplace;
	Ball *m_Yplace;
	Bullet *m_bullet;
	int xsize;
	int ysize;
	int m_maxTile;
	int m_maxBullet;
	int m_XmaxPlace;
	int m_YmaxPlace;
	int m_objectcount;
	int m_ansTilecount;
	int m_Xplacecount;
	int m_Yplacecount;
	int m_bulletcount;
};

struct Item
{
	WEVec2 position;
	WEVec2 scale;
	int texture;
	unsigned color;
	bool used;
};

class ItemManager
{
public:
	ItemManager(int _itemAmount);
	~ItemManager();
	Item* GetItem(void);
	int GetItemCount(void) const;

	void AddItem(
		const WEVec2& pos,
		const WEVec2& scale,
		int texture,
		unsigned color
		);
private:
	Item *m_item;
	int m_itemcount;
	int itemAmount;
};

#endif
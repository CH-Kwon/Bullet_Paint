/******************************************************************************/
/*!
\file   OBJ_M.cpp
\author kyungook.park
\par    email: qkrruddn6680@gmail.com
\par    GAM150
\date   2017/06/04

This is file contains the functions that manage objects.
*/
/******************************************************************************/
#include "OBJ_M.h"
#include "WEDebugTools.h"
/******************************************************************************/
/*!
ObjectManager class consturctor
*/
/******************************************************************************/
ObjectManager::ObjectManager(int _xsize, int _ysize)
{
	m_maxTile = _xsize * _ysize;
	m_XmaxPlace = (_xsize * 2) ;
	m_YmaxPlace = (_ysize * 2);
	m_maxBullet = 300;
	m_object = new Object[m_maxTile];
	m_ansTile = new Object[m_maxTile];
	m_Xplace = new Ball[m_XmaxPlace];
	m_Yplace = new Ball[m_YmaxPlace];
	m_bullet = new Bullet[m_maxBullet];
	m_Xplacecount = 0;
	m_Yplacecount = 0;
	m_objectcount = 0;
	m_ansTilecount = 0;
	m_bulletcount = 0;
}
/******************************************************************************/
/*!
ObjectManager class desturctor
*/
/******************************************************************************/
ObjectManager::~ObjectManager()
{
	delete[] m_object;
	delete[] m_ansTile;
	delete[] m_Xplace;
	delete[] m_Yplace;
	delete[] m_bullet;
}
/******************************************************************************/
/*!
ObjectManager class get Functions
*/
/******************************************************************************/
/* \breif/ return m_object */
Object * ObjectManager::GetObjects(void)
{
	return m_object;
}
/* \breif/ return m_ansTile */
Object * ObjectManager::GetAnsObj(void)
{
	return m_ansTile;
}
/* \breif/ return m_Xplace */
Ball * ObjectManager::GetXPlaceObj(void)
{
	return m_Xplace;
}
/* \breif/ return m_Yplace*/
Ball * ObjectManager::GetYPlaceObj(void)
{
	return m_Yplace;
}
/* \breif/ return m_bullet */
Bullet * ObjectManager::GetBullets(void)
{
	return m_bullet;
}
/* \breif/ return m_objectcount */
int ObjectManager::GetObjectCount(void) const
{
	return m_objectcount;
}
/* \breif/ return m_ansTilecount*/
int ObjectManager::GetAnsObjCount(void) const
{
	return m_ansTilecount;
}
/* \breif/ return m_Xplacecount*/
int ObjectManager::GetXPlaceObjCount(void) const
{
	return m_Xplacecount;
}
/* \breif/ return m_Yplacecount*/
int ObjectManager::GetYPlaceObjCount(void) const
{
	return m_Yplacecount;
}
/* \breif/ return m_bulletcount */
int ObjectManager::GetBulletCount(void) const
{
	return m_bulletcount;
}
/******************************************************************************/
/*!
ObjectManager class function that adds Objects
*/
/******************************************************************************/
void ObjectManager::AddObject(const WEVec2 & pos, const WEVec2 & scale, int texture, unsigned color)
{
	if (m_objectcount < m_maxTile)
	{
		m_object[m_objectcount].position = pos;
		m_object[m_objectcount].scale = scale;
		m_object[m_objectcount].texture = texture;
		m_object[m_objectcount].color = color;
		m_object[m_objectcount].isclicked = false;
		++m_objectcount;
	}
}
/******************************************************************************/
/*!
	Add function
	\breif
	Add Answer Objects
*/
/******************************************************************************/
void ObjectManager::AddAnsObj(const WEVec2 & pos, const WEVec2 & scale, int texture, unsigned color)
{
	if (m_ansTilecount < m_maxTile)
	{
		m_ansTile[m_ansTilecount].position = pos;
		m_ansTile[m_ansTilecount].scale = scale;
		m_ansTile[m_ansTilecount].texture = texture;
		m_ansTile[m_ansTilecount].color = color;
		m_ansTile[m_ansTilecount].isclicked = false;
		++m_ansTilecount;
	}
}
/******************************************************************************/
/*!
Add function
\breif
Add X-axis foot fedals
*/
/******************************************************************************/
void ObjectManager::AddXPlace(const WEVec2 & pos, const WEVec2 & scale, int texture, unsigned color)
{
	if (m_Xplacecount < m_XmaxPlace)
	{
		m_Xplace[m_Xplacecount].position = pos;
		m_Xplace[m_Xplacecount].scale = scale;
		m_Xplace[m_Xplacecount].texture = texture;
		m_Xplace[m_Xplacecount].color = color;
		m_Xplace[m_Xplacecount].isclicked = false;
		m_Xplace[m_Xplacecount].vel.x = 0;
		m_Xplace[m_Xplacecount].vel.y = 0;
		++m_Xplacecount;
	}
}
/******************************************************************************/
/*!
Add function
\breif
Add Y-axis foot fedals
*/
/******************************************************************************/
void ObjectManager::AddYPlace(const WEVec2 & pos, const WEVec2 & scale, int texture, unsigned color)
{
	if (m_Yplacecount < m_YmaxPlace)
	{
		m_Yplace[m_Yplacecount].position = pos;
		m_Yplace[m_Yplacecount].scale = scale;
		m_Yplace[m_Yplacecount].texture = texture;
		m_Yplace[m_Yplacecount].color = color;
		m_Yplace[m_Yplacecount].isclicked = false;
		m_Yplace[m_Yplacecount].vel.x = 0;
		m_Yplace[m_Yplacecount].vel.y = 0;
		++m_Yplacecount;
	}
}
/******************************************************************************/
/*!
Add function
\breif
Add Bullets
*/
/******************************************************************************/
void ObjectManager::AddBullet(const WEVec2 & vel, const WEVec2 & position, const WEVec2 & scale, int texture, unsigned color)
{
		m_bullet[m_bulletcount].objectID = m_bulletcount;
		m_bullet[m_bulletcount].vel = vel;
		m_bullet[m_bulletcount].position = position;
		m_bullet[m_bulletcount].scale = scale;
		m_bullet[m_bulletcount].texture = texture;
		m_bullet[m_bulletcount].color = color;
		m_bullet[m_bulletcount].isCollided = false;
		++m_bulletcount;
}
/******************************************************************************/
/*!
Delete function
\breif
Deletes bullet
*/
/******************************************************************************/
/* Delete functions */
void ObjectManager::DeleteBullet(int objectID)
{
	--m_bulletcount;
	m_bullet[objectID].color = m_bullet[m_bulletcount].color;
	m_bullet[objectID].position = m_bullet[m_bulletcount].position;
	m_bullet[objectID].vel = m_bullet[m_bulletcount].vel;
	m_bullet[objectID].scale = m_bullet[m_bulletcount].scale;
	m_bullet[objectID].texture = m_bullet[m_bulletcount].texture;
}
/******************************************************************************/
/*!
ItemManager class consturctor
*/
/******************************************************************************/
ItemManager::ItemManager(int _itemAmount)
{
	itemAmount = _itemAmount;
	m_item = new Item[itemAmount];
	m_itemcount = 0;
}
/******************************************************************************/
/*!
ItemManager class desturctor
*/
/******************************************************************************/
ItemManager::~ItemManager()
{
	delete[] m_item;
}
/******************************************************************************/
/*!
ItemManager class get Functions
*/
/******************************************************************************/
Item * ItemManager::GetItem(void)
{
	return m_item;
}

int ItemManager::GetItemCount(void) const
{
	return m_itemcount;
}
/******************************************************************************/
/*!
ItemManager class function that adds item in game.
*/
/******************************************************************************/
void ItemManager::AddItem(const WEVec2 & pos, const WEVec2 & scale, int texture, unsigned color)
{
	if (m_itemcount< itemAmount)
	{
		m_item[m_itemcount].position = pos;
		m_item[m_itemcount].scale = scale;
		m_item[m_itemcount].texture = texture;
		m_item[m_itemcount].color = color;
		m_item[m_itemcount].used = false;
		++m_itemcount;
	}
}

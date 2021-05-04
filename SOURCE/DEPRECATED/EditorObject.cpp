
#include "ObjectManager.h"
#include "WEDebugTools.h"
ObjectManager::ObjectManager(int maxObjects, int maxButtons)
{
	m_button = new  Button[maxButtons];
	m_object = new Object[maxObjects];
	m_objectcount = 0;
	m_buttoncount = 0;
	m_maxButtons = maxButtons;
	m_maxObjects = maxObjects;
}
ObjectManager::~ObjectManager(void)
{
	delete[] m_button;
	delete[] m_object;
}
Object * ObjectManager::GetObjects(void)
{
	return m_object;
}
int ObjectManager::GetObjectCount(void) const
{
	return m_objectcount;
}
void ObjectManager::DeleteObject(int objectID)
{	
		--m_objectcount;
		m_object[objectID].color = m_object[m_objectcount].color;
		m_object[objectID].objectID = objectID;
		m_object[objectID].position = m_object[m_objectcount ].position;
		m_object[objectID].rotation = m_object[m_objectcount].rotation;
		m_object[objectID].scale = m_object[m_objectcount].scale;
		m_object[objectID].texture = m_object[m_objectcount].texture;
}
void ObjectManager::AddObject(const WEVec2 & pos, float rotation, const WEVec2& scale, int texture, unsigned color)
{
	if (m_objectcount < m_maxObjects)
	{
		m_object[m_objectcount].objectID = m_objectcount;
		m_object[m_objectcount].position = pos;
		m_object[m_objectcount].rotation = rotation;
		m_object[m_objectcount].scale = scale;
		m_object[m_objectcount].texture = texture;
		m_object[m_objectcount].color = color;
		m_object[m_objectcount].isclicked = false;
		++m_objectcount;
	}
}
Button * ObjectManager::GetButtons(void)
{
	return m_button;
}
int ObjectManager::GetButtonCount(void) const
{
	return m_buttoncount;
}
void ObjectManager::DeleteButton(int buttonID)
{
		--m_buttoncount;
		m_button[buttonID].position = m_button[m_buttoncount].position;
		m_button[buttonID].action = m_button[m_buttoncount].action;
		m_button[buttonID].buttonID = m_button[m_buttoncount].buttonID;
		m_button[buttonID].scale = m_button[m_buttoncount].scale;
		m_button[buttonID].texture = m_button[m_buttoncount].texture;
	  
}
void ObjectManager::AddButton(const WEVec2 & pos, const WEVec2 & scale, int texture, Action action)
{
	if (m_buttoncount < m_maxButtons)
	{
		m_button[m_buttoncount].position = pos;
		m_button[m_buttoncount].scale = scale;
		m_button[m_buttoncount].texture = texture;
		m_button[m_buttoncount].action = action;
		++m_buttoncount;
	}
}


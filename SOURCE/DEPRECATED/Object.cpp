#include "Object.h"
#include "WEDebugTools.h"
ObjectM::ObjectM(int maxObjects)
{
	m_object = new Object[maxObjects];
	m_objectcount = 0;
	m_buttoncount = 0;
	m_maxObjects = maxObjects;
}
ObjectM::~ObjectM(void)
{
	delete[] m_object;
}
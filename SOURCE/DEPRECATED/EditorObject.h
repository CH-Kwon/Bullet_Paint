
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "WEVec2.h"


struct Object //!< Object's informations
{
  WEVec2   position;          //!< Object's position
  float    rotation;          //!< Object's rotation
  WEVec2    scale;             //!< Object's scale
  int      objectID;          //!< Object's ID
  int      texture;           //!< Object's texture
  unsigned color;             //!< Object's color
  bool isclicked;
};



typedef void(*Action)(void);  //!< Button's action


struct Button //!< Button's informations
{
  WEVec2   position;      //!< Button's position
  WEVec2   scale;         //!< Button's scale
  int      buttonID;      //!< Button's ID
  int      texture;       //!< Button's texture
  Action   action;        //!< Button's action
};

/******************************************************************************/
/*!
  \class ObjectManager

    Operations include:

    - Allocate the objects and buttons.
    - Return objects, buttons, objectcount, buttoncount.
    - Add the objecrs and buttons to each array.
*/
/******************************************************************************/
class ObjectManager
{
public:
	ObjectManager(int maxObjects, int maxButtons);
  ~ObjectManager(void);

  Object* GetObjects(void);
  int GetObjectCount(void) const;

  void DeleteObject(int objectID);

  void AddObject(
    const WEVec2& pos,
    float rotation,
    const WEVec2& scale,
    int texture,
    unsigned color);

  Button* GetButtons(void);
  int GetButtonCount(void) const;

  void DeleteButton(int buttonID);

  void AddButton(
    const WEVec2& pos,
    const WEVec2& scale,
    int texture,
    Action action);
private:

  Button *m_button;     //!< Array of Buttons
  Object *m_object;     //!< Array of Objects
  int m_objectcount;    //!< Number of Objects
  int m_buttoncount;    //!< Number of Buttons
  int m_maxObjects;     //!< maximum of Objects
  int m_maxButtons;     //!< maximum of Buttons
};


#endif /* OBJECTMANAGER_H */

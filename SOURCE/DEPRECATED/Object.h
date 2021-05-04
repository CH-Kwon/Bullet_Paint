#include "WEVec2.h"
struct Object
{
	WEVec2   position;          //!< Object's position
	WEVec2   velocity;          //!< Object's velocity
	float    rotation;          //!< Object's rotation
	float    rotationVel;       //!< Object's rotationVelocity
	float    scale;             //!< Object's scale
	int      objectID;          //!< Object's ID
	int      texture;           //!< Object's texture
	unsigned color;             //!< Object's color
};
struct Button //!< Button's informations
{
	WEVec2   position;      //!< Button's position
	WEVec2   scale;         //!< Button's scale
	int      buttonID;      //!< Button's ID
	int      texture;       //!< Button's texture
};
class ObjectM
{
public:
	ObjectM(int maxObjects);
	~ObjectM(void);

	Object* GetObjects(void);
	int GetObjectCount(void) const;

	void DeleteObject(int objectID);

	void AddObject(
		const WEVec2& pos,
		const WEVec2& Vel,
		float rotation,
		float rotationVel,
		float scale,
		int texture,
		unsigned color);





private:

	Button *m_button;     //!< Array of Buttons
	Object *m_object;     //!< Array of Objects
	int m_objectcount;    //!< Number of Objects
	int m_buttoncount;    //!< Number of Buttons
	int m_maxObjects;     //!< maximum of Objects
	int m_maxButtons;     //!< maximum of Buttons
};
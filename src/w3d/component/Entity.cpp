#include "w3d/component/Entity.h"

namespace W3D::Components
{

	Entity::Entity(EntityID _id, EntityManager* _eManager, ComponentManager* _cManager) :ID(_id), eManager(_eManager), cManager(_cManager)
	{

	}

	bool operator==(Entity e1, Entity e2)
	{
		return e1.ID == e2.ID;
	}

}

#include "core/Component.h"

void Component::init(cID _id, Entity* _controllingEntity, EntityManager* _eManager, ComponentManager* _cManager)
{
	ID = _id;
	controllingEntity = _controllingEntity;
	eManager = _eManager;
	cManager = _cManager;
}

cID Component::getID()
{
	return ID;
}

Component::Component()
{
	controllingEntity = nullptr;
	eManager = nullptr;
	cManager = nullptr;
	ID = 0;
}

void Component::update() {}
void Component::start() {}
void Component::finalize() {}

Entity* Component::getControllingEntity()
{
	return controllingEntity;
}

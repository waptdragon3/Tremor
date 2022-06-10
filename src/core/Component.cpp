#include "core/Component.h"

void Component::init(cID _id, cType _type, Entity* _controllingEntity, EntityManager* _eManager, ComponentManager* _cManager)
{
	ID = _id;
	type = _type;
	controllingEntity = _controllingEntity;
	eManager = _eManager;
	cManager = _cManager;
}

cID Component::getID()
{
	return ID;
}

cType Component::getType()
{
	return type;
}

Component::Component()
{
	controllingEntity = nullptr;
	eManager = nullptr;
	cManager = nullptr;
	type = cType::Invalid;
	ID = 0;
}

void Component::update() {}
void Component::start() {}
void Component::finalize() {}
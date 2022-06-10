#include "core/Component.h"



Component::Component(cID _id, cType _type, Entity* _controllingEntity, EntityManager* _eManager, ComponentManager* _cManager)
	:ID(_id), type(_type), controllingEntity(_controllingEntity), eManager(_eManager), cManager(_cManager) {}

void Component::update() {}
void Component::start() {}

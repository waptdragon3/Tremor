#pragma once

typedef unsigned int eID;
class EntityManager;
class ComponentManager;


struct Entity
{
private:
	const EntityManager* eManager;
	const ComponentManager* cManager;
	Entity(eID _id, EntityManager* _eManager, ComponentManager* _cManager);
	friend class EntityManager;
public:
	const eID ID;
	bool enabled = true;
	Entity() = delete;
};

bool operator==(Entity e1, Entity e2);
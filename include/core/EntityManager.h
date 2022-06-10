#pragma once
#include "core/DynamicList.h"
#include "core/Entity.h"

class EntityManager
{
private:
	DynamicList<Entity*> entities;
	DynamicList<Entity*> entitiesToRemove;
	DynamicList<Entity*> entitiesToAdd;
	eID nextID;
	ComponentManager* cManager;

public:
	//Creates an Entity and adds it to the "entitiesToAdd" list
	Entity* makeEntity();
	//adds an entity to the "entitiesToRemove" list
	void removeEntity(Entity* e);
	//Shouldnt be needed, but just in case
	//Retrieves an existing entity by its ID
	Entity* getEntity(eID id);
	void update();

	uint32_t numEntities();
	
private:
	//removes all entities in the "entitiesToRemove" list, and adds all in the "entitiesToAdd" list
	//removes all components from entities in the "entitiesToRemove" list
	void flushChanges();
	void setCManager(ComponentManager* _cManager);

	EntityManager();
	~EntityManager();

	friend class MainManager;
};
#pragma once
#include "core/DynamicList.h"
#include "core/Component.h"

#include "EntityManager.h"

class ComponentManager
{
private:
	DynamicList<Component*> components;
	DynamicList<Component*> componentsToRemove;
	DynamicList<Component*> componentsToAdd;
	cID nextID;
	EntityManager* eManager;

public:
	//Creates a component of type "type" on entity "entity" and adds it to the "componentsToAdd" list
	Component* makeComponent(cType type, Entity* entity);

	//adds a component to the "componentsToRemove" list
	void removeComponent(Component* c);

	//Shouldnt be needed, but just in case
	//Retrieves an existing component by its ID
	Component* getComponent(cID id);

	//calls the "update" function on all active components
	void update();



	//returns a list of all components of type "type"
	DynamicList<Component*> getAllComponentsOfType(cType type);

	//returns the component of type "type" attached to entity "entity". if the component does not exist, it returns nullptr
	Component* getComponentTypeOnEntity(cType type, Entity* entity);

	//returns all components attached to entity "entity"
	DynamicList<Component*> getAllComponentsOnEntity(Entity* entity);

private:
	//removes all components in the "componentsToRemove" list, and adds all in the "componentsToAdd" list
	void flushChanges();
	void setEManager(EntityManager* _eManager);

	ComponentManager();
	~ComponentManager();

	friend class MainManager;
};
#include "core/ComponentManager.h"

#include "core/TransformCmpt.h"


Component* ComponentManager::makeComponent(cType type, Entity* entity)
{
	Component* c = nullptr;
	switch (type)
	{
	case cType::Invalid:
		break;
	case cType::Transform:
		c = new TransformCmpt::Component(nextID, type, entity, eManager, this);
		break;
	default:
		break;
	}
	if (c == nullptr) return nullptr;

	componentsToAdd.addItem(c);
    return c;
}

void ComponentManager::removeComponent(Component* c)
{
	componentsToRemove.addItem(c);
}

Component* ComponentManager::getComponent(cID id)
{
	for (unsigned int i = 0; i < components.length(); i++)
	{
		Component* c = components[i];
		if (c->ID == id)
			return c;
	}
	return nullptr;
}

void ComponentManager::update()
{
	for (unsigned int i = 0; i < components.length(); i++)
	{
		Component* c = components[i];
		if (c->enabled)
			c->update();
	}
}

DynamicList<Component*> ComponentManager::getAllComponentsOfType(cType type)
{
	DynamicList<Component*> cmpts;
	for (unsigned int i = 0; i < components.length(); i++)
	{
		Component* c = components[i];
		if (c->type == type)
			cmpts.addItem(c);
	}
	return cmpts;
}

Component* ComponentManager::getComponentTypeOnEntity(cType type, Entity* entity)
{
	for (unsigned int i = 0; i < components.length(); i++)
	{
		Component* c = components[i];
		if (c->type == type && c->controllingEntity->ID == entity->ID)
			return c;
	}

	return nullptr;
}

DynamicList<Component*> ComponentManager::getAllComponentsOnEntity(Entity* entity)
{
	DynamicList<Component*> cmpts;
	for (unsigned int i = 0; i < components.length(); i++)
	{
		Component* c = components[i];
		if (c->controllingEntity->ID == entity->ID)
			cmpts.addItem(c);
	}
	return cmpts;
}

void ComponentManager::flushChanges()
{
	//add all components in the "componentsToAdd" list
	for (unsigned int i = 0; i < componentsToAdd.length(); i++)
	{
		Component* c = componentsToAdd[i];
		components.addItem(c);
	}
	//clear "componentsToAdd" list
	componentsToAdd.clear();

	//remove all components in the "componentsToRemove" list
	for (unsigned int i = 0; i < componentsToRemove.length(); i++)
	{
		Component* c = componentsToRemove[i];

		//find index of c
		bool found = false;
		uint32_t index = 0;
		for (unsigned int j = 0; j < components.length(); j++)
		{
			Component* c2 = components[j];
			if (c->ID == c2->ID)
			{
				found = true;
				index = j;
				break;
			}
		}
		//if we found the component
		if (found)
		{
			components.removeIndex(index);
		}

		delete c;
	}
	//clear "componentsToRemove" list
	componentsToRemove.clear();

}

void ComponentManager::setEManager(EntityManager* _eManager)
{
	eManager = _eManager;
}

ComponentManager::ComponentManager() :eManager(nullptr), nextID(unsigned int(0)) {}

ComponentManager::~ComponentManager()
{
	//go through all lists and clear memory
	for (int i = 0; i < components.length(); i++)
	{
		Component* c = components[i];
		delete c;
	}

	for (int i = 0; i < componentsToAdd.length(); i++)
	{
		Component* c = componentsToAdd[i];
		delete c;
	}

	for (int i = 0; i < componentsToRemove.length(); i++)
	{
		Component* c = componentsToRemove[i];
		delete c;
	}

	components.clear();
	componentsToAdd.clear();
	componentsToRemove.clear();
}

#include "w3d/component/EntityManager.h"
#include "w3d/component/ComponentManager.h"

namespace W3D::Components
{

	Entity* EntityManager::makeEntity()
	{
		Entity* e = new Entity(nextID, this, cManager);
		entitiesToAdd.addItem(e);
		nextID++;
		return e;
	}

	void EntityManager::removeEntity(Entity* e)
	{
		entitiesToRemove.addItem(e);
	}

	Entity* EntityManager::getEntity(EntityID id)
	{
		for (unsigned int i = 0; i < entities.length(); i++)
		{
			Entity* e = entities[i];
			if (e->ID == id)
				return e;
		}
		return nullptr;
	}

	void EntityManager::update()
	{
	}

	uint32_t EntityManager::numEntities()
	{
		return entities.length();
	}

	void EntityManager::flushChanges()
	{
		//remove all components from the "entitiesToRemove" list
		for (unsigned int i = 0; i < entitiesToRemove.length(); i++)
		{
			Entity* e = entitiesToRemove[i];
			cManager->removeComponentsFromEntity(e);
		}

		//add all entities in the "entitiesToAdd" list
		for (unsigned int i = 0; i < entitiesToAdd.length(); i++)
		{
			Entity* e = entitiesToAdd[i];
			entities.addItem(e);
		}
		//clear "entitiesToAdd" list
		entitiesToAdd.clear();

		//remove all entities in the "entitiesToRemove" list
		for (unsigned int i = 0; i < entitiesToRemove.length(); i++)
		{
			Entity* e = entitiesToRemove[i];

			//find index of e
			bool found = false;
			uint32_t index = 0;
			for (unsigned int j = 0; j < entities.length(); j++)
			{
				Entity* e2 = entities[j];
				if (e->ID == e2->ID)
				{
					found = true;
					index = j;
					break;
				}
			}
			//if we found the entity
			if (found)
			{
				entities.removeIndex(index);
			}

			delete e;
		}
		//clear "entitiesToRemove" list
		entitiesToRemove.clear();
	}

	void EntityManager::setCManager(ComponentManager* _cManager)
	{
		cManager = _cManager;
	}

	EntityManager::EntityManager():cManager(nullptr), nextID(unsigned int (0)) {}

	EntityManager::~EntityManager()
	{
		//go through all lists and clear memory
		for (unsigned int i = 0; i < entities.length(); i++)
		{
			Entity* c = entities[i];
			delete c;
		}

		for (unsigned int i = 0; i < entitiesToAdd.length(); i++)
		{
			Entity* c = entitiesToAdd[i];
			delete c;
		}

		for (unsigned int i = 0; i < entitiesToRemove.length(); i++)
		{
			Entity* c = entitiesToRemove[i];
			delete c;
		}

		entities.clear();
		entitiesToAdd.clear();
		entitiesToRemove.clear();
	}

}
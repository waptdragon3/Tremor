#include "core/ComponentManager.h"

namespace W3D::Components
{

	void ComponentManager::removeComponent(Component* c)
	{
		auto it = componentLists.begin();
		while (it != componentLists.end())
		{
			it->second->removeComponent(c);
		}
	}

	void ComponentManager::update()
	{
		auto it = componentLists.begin();
		while (it != componentLists.end())
		{
			it->second->update();
			it++;
		}
	}

	void ComponentManager::flushChanges()
	{
		auto it = componentLists.begin();
		while (it != componentLists.end())
		{
			it->second->flushChanges();
			it++;
		}

	}

	void ComponentManager::setEManager(EntityManager* _eManager)
	{
		eManager = _eManager;
	}

	void ComponentManager::removeComponentsFromEntity(Entity* e)
	{
		auto it = componentLists.begin();
		while (it != componentLists.end())
		{
			it->second->removeComponentsFromEntity(e);
			it++;
		}
	}

	ComponentManager::ComponentManager() :eManager(nullptr), nextID(unsigned int(1)) {}

	ComponentManager::~ComponentManager()
	{
		auto it = componentLists.begin();
		while (it != componentLists.end())
		{
			delete (it->second);
			it++;
		}
	}

}
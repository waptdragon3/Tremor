#pragma once
#include "core/EntityManager.h"
#include "core/ComponentManager.h"

namespace W3D::Components
{
	class MainManager
	{
	private:
		EntityManager eManager;
		ComponentManager cManager;
	public:
		MainManager();

		EntityManager* getEManager();
		ComponentManager* getCManager();

		//calls EntityManager::update and ComponentManager::update and then EntityManager::flushChanges and ComponentManager::flushChanges
		void update();
	};
}
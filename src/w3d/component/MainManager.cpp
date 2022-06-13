#include "w3d/component/MainManager.h"

namespace W3D::Components
{

	MainManager::MainManager()
	{
		eManager.setCManager(&cManager);

		cManager.setEManager(&eManager);
	}

	EntityManager* MainManager::getEManager()
	{
		return &eManager;
	}

	ComponentManager* MainManager::getCManager()
	{
		return &cManager;
	}

	void MainManager::update()
	{
		eManager.update();
		cManager.update();

		eManager.flushChanges();
		cManager.flushChanges();
	}

}
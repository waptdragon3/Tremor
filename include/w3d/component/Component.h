#pragma once
#include <typeindex>

namespace W3D::Components
{

	using ComponentID = unsigned long long;
	class EntityManager;
	class ComponentManager;
	struct Entity;

	struct Component
	{
	protected:
		EntityManager* eManager;
		ComponentManager* cManager;
		Entity* controllingEntity;
	private:
		friend class ComponentManager;

		void init(ComponentID _id, Entity* _controllingEntity, EntityManager* _eManager, ComponentManager* _cManager);

		ComponentID ID;
	public:
		ComponentID getID();

		Component();
		//called once per frame
		virtual void update();
		//called when the component is added to the scene
		virtual void start();
		//called just before the component id destroyed
		virtual void finalize();

		Entity* getControllingEntity();

		bool enabled = true;
	};
}
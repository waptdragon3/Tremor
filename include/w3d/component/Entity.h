#pragma once

namespace W3D::Components
{

	using EntityID = unsigned long long;
	class EntityManager;
	class ComponentManager;


	struct Entity
	{
	private:
		const EntityManager* eManager;
		const ComponentManager* cManager;
		Entity(EntityID _id, EntityManager* _eManager, ComponentManager* _cManager);
		friend class EntityManager;
	public:
		const EntityID ID;
		bool enabled = true;
		Entity() = delete;
	};

	bool operator==(Entity e1, Entity e2);
}
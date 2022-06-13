#pragma once
#include "w3d/DynamicList.h"
#include "w3d/component/Component.h"

#include "EntityManager.h"
#include <unordered_map>
#include <typeindex>

namespace W3D::Components
{
	class IComponentStorage
	{
	private:

	public:
		virtual void update() = 0;
		virtual Component* makeComponent() = 0;
		virtual void removeComponent(Component* c) = 0;
		virtual void flushChanges() = 0;
		virtual Component* getComponentOnObject(Entity* e) = 0;
		virtual void removeComponentsFromEntity(Entity* e) = 0;
	};


	template <typename T>
	class ComponentStorage : public IComponentStorage
	{
	private:
		DynamicList<Component*> components;
		DynamicList<Component*> componentsToRemove;
		DynamicList<Component*> componentsToAdd;
		friend class ComponentManager;
	public:
		void update() override
		{
			for (unsigned int i = 0; i < components.length(); i++)
			{
				Component* c = components[i];
				if (c->enabled)
					c->update();
			}
		}
		Component* makeComponent() override
		{
			T* t = new T();
			Component* c = dynamic_cast<Component*>(t);
			if (c == nullptr)
			{
				delete t;
				return nullptr;
			}
			componentsToAdd.addItem(c);
			return c;
		}
		void removeComponent(Component* c) override
		{
			componentsToRemove.addItem(c);
		}
		void flushChanges() override
		{
			//add all components in the "componentsToAdd" list
			for (unsigned int i = 0; i < componentsToAdd.length(); i++)
			{
				Component* c = componentsToAdd[i];
				c->start();
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
					if (c->getID() == c2->getID())
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

				c->finalize();
				delete c;
			}
			//clear "componentsToRemove" list
			componentsToRemove.clear();
		}
		Component* getComponentOnObject(Entity* e) override
		{
			for (unsigned int i = 0; i < components.length(); i++)
			{
				Component* c = components[i];
				if (c->getControllingEntity()->ID == e->ID)
				{
					return c;
				}
			}
			for (unsigned int i = 0; i < componentsToAdd.length(); i++)
			{
				Component* c = components[i];
				if (c->getControllingEntity()->ID == e->ID)
				{
					return c;
				}
			}
			return nullptr;
		}

		void removeComponentsFromEntity(Entity* e) override
		{
			for (unsigned int i = 0; i < components.length(); i++)
			{
				Component* c = components[i];
				if (c->getControllingEntity()->ID == e->ID)
				{
					removeComponent(c);
				}
			}
		}

		~ComponentStorage()
		{
			for (int i = 0; i < components.length(); i++)
			{
				Component* c = components[i];
				delete c;
			}
			components.clear();

			for (int i = 0; i < componentsToAdd.length(); i++)
			{
				Component* c = componentsToAdd[i];
				delete c;
			}
			componentsToAdd.clear();

			for (int i = 0; i < componentsToRemove.length(); i++)
			{
				Component* c = componentsToRemove[i];
				delete c;
			}
			componentsToRemove.clear();
		}
	};


	class ComponentManager
	{
	private:
		std::unordered_map<std::type_index, IComponentStorage*> componentLists;
		ComponentID nextID;
		EntityManager* eManager;

	public:
		//Creates a component of type "type" on entity "entity" and adds it to the "componentsToAdd" list
		template <typename T>
		T* makeComponent(Entity* entity);

		//adds a component to the "componentsToRemove" list
		void removeComponent(Component* c);

		//calls the "update" function on all active components
		void update();



		//returns a list of all components of type "type"
		template <typename T>
		DynamicList<T*> getAllComponentsOfType();

		//returns the component of type "type" attached to entity "entity". if the component does not exist, it returns nullptr
		template <typename T>
		T* getComponentTypeOnEntity(Entity* entity);

		void removeComponentsFromEntity(Entity* e);

	private:
		//removes all components in the "componentsToRemove" list, and adds all in the "componentsToAdd" list
		void flushChanges();
		void setEManager(EntityManager* _eManager);

		ComponentManager();
		~ComponentManager();

		friend class MainManager;
	};

	template<typename T>
	T* ComponentManager::makeComponent(Entity* entity)
	{
		//ensure that T is a child of Component
		if (!std::is_base_of<Component, T>())
		{
			throw std::exception("Invalid type");
		}

		std::type_index type = typeid(T);
		auto find = componentLists.find(type);

		//if type doesnt already exists create it
		if (find == componentLists.end())
		{
			componentLists[type] = new ComponentStorage<T>();
			find = componentLists.find(type);
		}

		Component* c = find->second->makeComponent();
		c->init(nextID, entity, eManager, this);
		nextID++;

		T* t = dynamic_cast<T*>(c);

		return t;

		return nullptr;
	}

	template<typename T>
	DynamicList<T*> ComponentManager::getAllComponentsOfType()
	{
		//ensure that T is a child of Component
		if (!std::is_base_of<Component, T>())
		{
			throw std::exception("Invalid type");
		}

		std::type_index type = typeid(T);
		auto find = componentLists.find(type);

		DynamicList<T*> list;
		if (find != componentLists.end())
		{
			IComponentStorage* _cList = find->second;
			ComponentStorage<T>* cList = dynamic_cast<ComponentStorage<T>*>(_cList);
			if (cList != nullptr)
			{
				list.resize(cList->components.length());
				for (int i = 0; i < cList->components.length(); i++)
				{
					T* t = dynamic_cast<T*>(cList->components[i]);
					if (t != nullptr)
					{
						list.addItem(t);
					}
				}
			}
		}

		return list;
	}

	template<typename T>
	T* ComponentManager::getComponentTypeOnEntity(Entity* entity)
	{
		//ensure that T is a child of Component
		if (!std::is_base_of<Component, T>())
		{
			throw std::exception("Invalid type");
		}

		std::type_index type = typeid(T);
		auto find = componentLists.find(type);
		if (find != componentLists.end())
		{
			Component* c = find->second->getComponentOnObject(entity);
			return dynamic_cast<T*>(c);
		}
		else
		{
			return nullptr;
		}
	}
}
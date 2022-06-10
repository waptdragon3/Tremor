#pragma once

typedef unsigned int cID;
class EntityManager;
class ComponentManager;
struct Entity;

enum class cType
{
	Invalid = 0,
	Transform = 1
};

struct Component
{
private:
	const EntityManager* eManager;
	const ComponentManager* cManager;
	const Entity* controllingEntity;
	Component(cID _id, cType _type, Entity* _controllingEntity, EntityManager* _eManager, ComponentManager* _cManager);
	friend class ComponentManager;

public:
	const cID ID;
	const cType type;
	Component() = delete;
	//called once per frame
	virtual void update();
	//called when the component is added to the scene
	virtual void start();

	bool enabled = true;
};
#pragma once

typedef unsigned int cID;
class EntityManager;
class ComponentManager;
struct Entity;

enum class cType
{
	Invalid = 0,
	Transform = 1,
	Cube = 2,
	BAF
};

struct Component
{
protected:
	EntityManager* eManager;
	ComponentManager* cManager;
	Entity* controllingEntity;
private:
	friend class ComponentManager;

	void init(cID _id, cType _type, Entity* _controllingEntity, EntityManager* _eManager, ComponentManager* _cManager);

	cID ID;
	cType type;
public:
	cID getID();
	cType getType();

	Component();
	//called once per frame
	virtual void update();
	//called when the component is added to the scene
	virtual void start();
	//called just before the component id destroyed
	virtual void finalize();

	bool enabled = true;
};
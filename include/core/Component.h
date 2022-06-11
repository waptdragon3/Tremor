#pragma once
#include <typeindex>

typedef unsigned int cID;
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

	void init(cID _id, Entity* _controllingEntity, EntityManager* _eManager, ComponentManager* _cManager);

	cID ID;
public:
	cID getID();

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
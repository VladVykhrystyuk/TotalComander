#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>

class Component
{
public:
	virtual void set_parent(Component*) = 0;
	virtual Component* get_parent() = 0;
	virtual void print() = 0;
	virtual void enter() = 0;
	virtual ~Component() = default;
	virtual std::string get_path() = 0;
};

#endif
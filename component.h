#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <string>


class GameObject;


class Component{
private:
	std::string name;
public:
	GameObject* obj;
	virtual ~Component() = 0;
};


#endif

#ifndef __SCRIPTS_H__
#define __SCRIPTS_H__

#include <vector>
#include <iostream>
#include "component.h"

class ScriptController{
private:
	std::vector<Component*> scripts;
public:
	void appendScript(Component* script);
	void removeScript(Component* script);
	void update();
};



class Script: public Component{
public:
	virtual void execute() = 0;
};


#endif

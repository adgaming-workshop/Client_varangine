#include "game_object.h"

GameObject::~GameObject(){
	Client::getInstance()->render_controller.removeObject(this);
	for (auto i = this->components.begin(); i != this->components.end(); i++){
		Client::getInstance()->script_controller.removeScript(i->second);
		Client::getInstance()->physics_controller.removeCollider(i->second);
		delete i->second;
	}
}

void GameObject::remove(){
	this->is_deleted = true;
}

void GameObject::removeAllComponents(){
	auto beg = this->components.begin();
	auto end = this->components.end();
	for(auto i = beg; i != end; i++){
		delete i->second;
		this->components.erase(i);
	}
	std::cout << "from removeAllComponents" << std::endl;
}

void GameObject::init(std::string player_name){
	this->player_name = player_name;
}

std::string GameObject::getPlayerName(){
	return this->player_name;
}

vector2f::vector2f(float x, float y){
	this->x = x;
	this->y = y;
}

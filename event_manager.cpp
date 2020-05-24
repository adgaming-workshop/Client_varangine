#include "event_manager.h"

Scaner::Scaner(sf::RenderWindow* window){
	this->window = window;
}

sf::Event Scaner::getEvent(){
	return this->event;
}

bool Scaner::scan(){
	return this->window->pollEvent(this->event);
};


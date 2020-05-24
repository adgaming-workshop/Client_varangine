#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <SFML/Graphics.hpp>

class Scaner{
public:
	Scaner(sf::RenderWindow* window);
	Scaner();
	bool scan();
	sf::Event getEvent();
private:
	sf::Event event;
	sf::RenderWindow* window;
};

#endif

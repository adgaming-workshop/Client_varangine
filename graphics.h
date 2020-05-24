#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SFML/Graphics.hpp>
#include <string>
#include "component.h"


class RenderController{
public:
	sf::RenderWindow window;
	void drawAll();
	void appendObject(GameObject* obj);
	void removeObject(GameObject* obj);
	void makeWindow(); 
	void setWindowSize(float x, float y);
	void setTitle(std::string title);
	void setLayersCount(int N);
	int getLayersCount();
	void sort();
private:
	int layers_count = 1;
	std::string title = "default_1";
	float size_x = 800;
	float size_y = 600;
	std::vector<GameObject*> rend_objects;

};


class Renderer :public Component{
private:
	sf::Texture texture;
	sf::Image image;
	sf::Sprite sprite;
	float frame = 0;
	float speed = 0;
	float w = 0;
	float h = 0;
public:
	void makeAnimation(float x, float y, float w, float h, int count, float speed);
	int count = 1;
	int cord_x = 0;
	float cord_y = 0;
	bool animated = false;
	void update();
	int layer = 1;
	void setLayer(int n);
	void makeSprite(std::string file_name);
	void setPosOfSprite(sf::Vector2f vec);
	sf::Sprite getSprite();
	~Renderer() override;
};


#endif

#include "graphics.h"
#include "game_object.h"


void RenderController::drawAll(){
	float x,y;
	auto beg = this->rend_objects.begin();
	auto end = this->rend_objects.end();
	for (auto it = beg; it != end; it++){
		x = this->size_x/2 + (*it)->x;
		y = this->size_y/2 - (*it)->y;
		(*it)->getComponent<Renderer>()->setPosOfSprite(sf::Vector2f(x, y));
		if((*it)->getComponent<Renderer>()->animated)
			(*it)->getComponent<Renderer>()->update();
		this->window.draw((*it)->getComponent<Renderer>()->getSprite());
		
	}
}

void RenderController::appendObject(GameObject* obj){
	this->rend_objects.push_back(obj);
}

void RenderController::removeObject(GameObject* obj){
	auto beg = this->rend_objects.begin();
	auto end = this->rend_objects.end();
	auto it_rm_obj = find(beg, end, obj);
	if (it_rm_obj != this->rend_objects.end())
		this->rend_objects.erase(it_rm_obj);
}

void RenderController::makeWindow(){
	this->window.create(sf::VideoMode(this->size_x, this->size_y), this->title);
}



Renderer:: ~Renderer(){};

void Renderer::makeSprite(std::string file_name){
	if(!this->image.loadFromFile(file_name)){
		std::cout << "Ошибка" << std::endl;
	}
	this->texture.loadFromImage(image);
	this->sprite.setTexture(this->texture);
	sf::Vector2f origin (sprite.getTextureRect().width * sprite.getScale().x, sprite.getTextureRect().height * sprite.getScale().y);
	origin *= 0.5f;
	this->sprite.setOrigin(origin);

}

void Renderer::setPosOfSprite(sf::Vector2f vec){
	this->sprite.setPosition(vec);
}

sf::Sprite Renderer::getSprite(){
	return this->sprite;
}

void RenderController::setWindowSize(float x, float y){
	this->size_x = x;
	this->size_y = y;
}

void RenderController::setTitle(std::string title){
	this->title = title;
}

void Renderer::setLayer(int n){
	this->layer = n;
	Client::getInstance()->render_controller.sort();
}

void RenderController::setLayersCount(int N){
	this->layers_count = N;
}

int RenderController::getLayersCount(){
	return this->layers_count;
}

bool comp(GameObject* obj_1, GameObject* obj_2){
	return obj_1->getComponent<Renderer>()->layer > obj_2->getComponent<Renderer>()->layer;
}

void RenderController::sort(){
	auto beg = this->rend_objects.begin();
	auto end = this->rend_objects.end();
	std::sort(beg, end, comp);
}

void Renderer::update(){
	this->frame += this->speed;
	if(this->frame >= this->count)
		this->frame -= this->count;
	this->sprite.setTextureRect(sf::IntRect(this->cord_x + int(this->frame) * this->w, this->cord_y, this->w, this->h));
}

void Renderer::makeAnimation(float x, float y, float w, float h, int count, float speed){
	this->cord_x = x;
	this->cord_y = y;
	this->w = w;
	this->h = h;
	this->count = count;
	this->speed = speed;
	this->sprite.setOrigin(sf::Vector2f(w/2, h/2));
	this->animated = true;
	this->sprite.setTextureRect(sf::IntRect(this->cord_x + this->w, this->cord_y, this->w, this->h));
}
	







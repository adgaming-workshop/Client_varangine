#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "data_storage.h"
#include "event_manager.h"
#include "graphics.h" 
#include "physics.h"
#include "scripts.h"

//Нужно дописать получение данных с сервера об отрисовываемых объектах.
//Приложение-клиент отправляет на сервер данные о событиях
//(нажатие клавишь клавиатуры).
//Получение данных о положении курсора мыши надо дописать.
class Client{
private:
	static Client* instance;  //Singleton
	Client(){};
	Client(const Client&){};
	Client& operator=(Client&){};
	void deleteInstance();

	Scaner scaner  = Scaner(&render_controller.window);
	std::string name;

	sf::TcpSocket socket;  //Отправка данных на сервер
	sf::Packet events_pack;
	sf::Packet registration_pack;
	void makePack();
	void sendRegistrationPack();
	void connect();
	void send();
	void unregistrate();

	sf::TcpSocket updates; //Получение обновленных данных с сервера
	sf::Packet updates_pack;
	sf::TcpListener listener;
	void makeListener();
	void recieveUpdates();
	bool extractData();
public:
	DataStorage data_storage; //Данные для отображения на экране
	RenderController render_controller;
	ScriptController script_controller;
	PhysicsController physics_controller; // В клиентском приложении не используется
	static Client* getInstance();
	void setName(std::string name);
	void runApp();
};
	

#endif

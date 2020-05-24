#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>
#include "game_object.h"
#include "data_storage.h"
#include "event_manager.h"
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

	DataStorage data_storage; //Данные для отображения на экране
	RenderController render_controller;
	ScriptController script_controller;
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
	static Client* getInstance();
	void setName(std::string name);
	void runApp();
};
	

#endif

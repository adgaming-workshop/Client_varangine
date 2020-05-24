#include "client_app.h"
#include "game_object.h"

Client* Client::getInstance(){
	if (!instance){
		instance = new Client;
		return instance;
	}
	else
		return instance;
}	

//Перегрузим операторы << и >> для формирования пакетов данных


sf::Packet& operator<< (sf::Packet& PACKET, const DataStorage& data_storage){
	for (auto obj: data_storage.getAllObjects()){
		PACKET << obj->x << obj->y;  
		PACKET << obj->velocity.x << obj->velocity.y;  
		PACKET << obj->accel.x << obj->accel.y;  
	}
	return PACKET;
}

sf::Packet& operator>> (sf::Packet& PACKET, DataStorage& data_storage){
	for (auto obj: data_storage.getAllObjects()){
		PACKET >> obj->x >> obj->y;  
		PACKET >> obj->velocity.x >> obj->velocity.y;  
		PACKET >> obj->accel.x >> obj->accel.y;  
	}
	return PACKET;
}

void Client::deleteInstance(){
	delete instance;
	instance = 0;
}

void Client::setName(std::string name){
	this->name = name;
}

void Client::connect(){
        if(this->socket.connect("127.0.0.1", 53000) != sf::Socket::Done){
                std::cout << "Connnection failed" << std::endl;
        }
}

void Client::makePack(){
	this->events_pack.clear();
	this->events_pack << this->data_storage;
}

void Client::send(){
	this->makePack();
	this->connect();
	sf::Socket::Status status = this->socket.send(this->events_pack);
        if (status != sf::Socket::Done)
        	std::cout << "Message has not been sent!" << std::endl;
        this->socket.disconnect();
}

void Client::runApp(){
	std::string name;
	std::cin >> name;
	this->setName(name); // регистрация клиента на сервере	
	this->makeListener();

	this->render_controller.makeWindow();
        while (this->render_controller.window.isOpen()){        //window cтоит сделать private в Renderer и написать ф-цию getWindow
		sf::Event event;
		while (this->render_controller.window.pollEvent(event)){
                        if (event.type == sf::Event::Closed)
                                this->render_controller.window.close();
                }
		this->script_controller.update();	
		this->physics_controller.update();
		this->send(); //Каждый кадр нажатия клавиш отправляются на сервер.
		this->recieveUpdates();
		this->render_controller.window.clear();
		this->render_controller.drawAll();
        }
	this->unregistrate(); //Сообщение серверу, что необходимо удалить данные клиента.
        Client::deleteInstance();
}	

void Client::sendRegistrationPack(){
	this->registration_pack << this->name << this->data_storage;
	this->connect();
	sf::Socket::Status status = this->socket.send(this->registration_pack);
        if (status != sf::Socket::Done)
        	std::cout << "Message has not been sent!" << std::endl;
        this->socket.disconnect();
	this->registration_pack.clear();
}

void Client::unregistrate(){ // В пакет список с координатами объектов. Координаты первого объекта имееют значение INT_MAX.
	this->connect();
	sf::Socket::Status status = this->socket.send(this->registration_pack);
        if (status != sf::Socket::Done)
        	std::cout << "Message has not been sent!" << std::endl;
        this->socket.disconnect();
	this->registration_pack.clear();
	std::cout << "Application has been stoped" << std::endl;
}

void Client::makeListener(){
	if (this->listener.listen(53000) != sf::Socket::Done){
                std::cout << "Can't bind the port" << std::endl;
                return;
        }
}

void Client::recieveUpdates(){
	if (this->listener.accept(this->socket) != sf::Socket::Done) {
            	std::cout << "Can not accept connection" << std::endl;
		return;
        }
	for(;;){
                sf::Socket::Status status = this->socket.receive(this->updates_pack);

            	if (status == sf::Socket::Done)
                	if(! this->extractData())
                       		std::cout << "Data extracted unsuccessfully" << std::endl;
            	
            	if (status == sf::Socket::Disconnected){
                	std::cout << "Client disconnected" << std::endl;
                	break;
            	}
        }
}

bool Client::extractData(){
	if(this->updates_pack >> this->data_storage)
		return true;
	return false;
}

Client* Client::instance = 0;

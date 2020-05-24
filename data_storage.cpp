#include "data_storage.h"
#include "game_object.h"

#include<iostream>
#include<string>

void DataStorage::createObject(std::string object_name)
{
    if (getObject(object_name) == nullptr)
    {
        GameObject* obj = new GameObject;
        obj->name = object_name;
        this->objects.push_back(obj);
    }
}

void DataStorage::deleteObject(std::string object_name)
{
    GameObject* obj = getObject(object_name);
    if(obj != nullptr)
    {
	auto beg = this->objects.begin();
	auto end = this->objects.end();
	auto it_rm_obj = find(beg, end, obj);
        delete *it_rm_obj;
        this->objects.erase(it_rm_obj);
    }
}   

GameObject* DataStorage::getObject(std::string object_name)
{	
	int j =0;
	for (auto i = this->objects.begin(); i != this->objects.end(); i++){
		if ((*i)->name == object_name){
			return *i;
		}
		j++;
	}
	return nullptr;
}

void DataStorage::update(){
	for (auto i = this->objects.begin(); i != this->objects.end(); i++){
		if((*i)->is_deleted){
			this->deleteObject((*i)->name);
		}
	}
}

DataStorage::~DataStorage(){
	for (auto i = this->objects.begin(); i != this->objects.end(); i++){
		delete *i;
	}
}

std::vector<GameObject*> DataStorage::getAllObjects() const{
	return this->objects;
}

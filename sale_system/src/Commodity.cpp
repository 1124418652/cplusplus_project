#include <iostream>
#include "Commodity.h"

int Commodity::kinds = 0;
void Commodity::addKinds(int kinds)
{
	Commodity::kinds = kinds;
}

Commodity::Commodity(char name[], float costPrice, float price)
{
	kinds++;
	this->costPrice = costPrice;
	this->price = price;
	this->ID = kinds;
	this->stock = 0;
	strcpy(this->name, name);
}

Commodity::Commodity(int ID, char name[], float costPrice, float price, int stock)
{
	this->ID = ID;
	strcpy(this->name, name);
	this->costPrice = costPrice;
	this->price = price;
	this->stock = stock;
}

int Commodity::getID(){
	return ID;
}

int Commodity::getStock(){
	return stock;
}

float Commodity::getCostPrice(){
	return costPrice;
}

float Commodity::getPrice(){
	return price;
}

char* Commodity::getName(){
	return name;
}

void Commodity::updateStock(int n){
	this->stock += n;
}
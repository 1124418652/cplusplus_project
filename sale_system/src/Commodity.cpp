#include <iostream>
#include "Commodity.h"

int Commodity::kinds = 0;
Commodity::Commodity(char name[], float costPrice, float price)
{
	kinds++;
	this->costPrice = costPrice;
	this->price = price;
	this->ID = kinds;
	this->stock = 0;
	memset(this->name, 0, 30);
	strncpy(this->name, name, 30);
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
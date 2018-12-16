#ifndef _COMMODITY_H
#define _COMMODITY_H

/*
商品类
实例化后的每一个对象表示一类商品
*/
class Commodity
{
public:
	Commodity(char name[], float costPrice, float price);   // 添加新品时使用的构造函数
	Commodity(int ID, char name[], float costPrice, float price, int stock);
	int getID();
	int getStock();
	float getCostPrice();
	float getPrice();
	char* getName();
	void updateStock(int n);
	static void addKinds(int kinds);
private:
	int static kinds;    // 商品种类（static成员是所有对象共享的，可以用来记录类别数）
	int ID;              // 商品ID
	int stock;           // 库存量
	float costPrice;     // 成本价
	float price;         // 售价
	char name[30];       // 商品名称
};

#endif
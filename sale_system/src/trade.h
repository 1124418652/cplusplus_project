#include <list>
#include "Commodity.h"

#ifndef _TRADE_H
#define _TRADE_H

/*
Trade类的作用是处理并保存数据
*/
class Trade
{
	struct record{
		char name[30];
		int count;
		char sTime[70];
		record(char* name, int count, char* time)
		{
			strcpy(this->name, name);
			this->count = count;
			strcpy(this->sTime, time);
		}
	};
private:
	std::list<Commodity> dataList;
	std::list<record> sellRecord;
	std::list<record> buyRecord;
public:
	bool getInformation(int index);    // 获取并输出商品信息
	void getIndex();         // 获取并输出商品目录
	bool init();             // 从本地文件获取商品信息
	void save();             // 将商品信息保存到本地文件中
	bool buy(int ID, int count);     // 购买商品的操作与数据检查
	bool sell(int ID, int count);    // 卖出商品的操作与数据检查
	void addNew(char name[], float costPrice, float price);
	void getSellRecord();    // 获取商品卖出记录
	void getBuyRecord();     // 获取商品购入记录
};

#endif
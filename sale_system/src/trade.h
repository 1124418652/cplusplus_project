#include <list>
#include "Commodity.h"

#ifndef _TRADE_H
#define _TRADE_H

/*
Trade��������Ǵ�����������
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
	bool getInformation(int index);    // ��ȡ�������Ʒ��Ϣ
	void getIndex();         // ��ȡ�������ƷĿ¼
	bool init();             // �ӱ����ļ���ȡ��Ʒ��Ϣ
	void save();             // ����Ʒ��Ϣ���浽�����ļ���
	bool buy(int ID, int count);     // ������Ʒ�Ĳ��������ݼ��
	bool sell(int ID, int count);    // ������Ʒ�Ĳ��������ݼ��
	void addNew(char name[], float costPrice, float price);
	void getSellRecord();    // ��ȡ��Ʒ������¼
	void getBuyRecord();     // ��ȡ��Ʒ�����¼
};

#endif
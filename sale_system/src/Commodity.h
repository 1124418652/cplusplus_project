#ifndef _COMMODITY_H
#define _COMMODITY_H

/*
��Ʒ��
ʵ�������ÿһ�������ʾһ����Ʒ
*/
class Commodity
{
public:
	Commodity(char name[], float costPrice, float price);
	int getID();
	int getStock();
	float getCostPrice();
	float getPrice();
	char* getName();
	void updateStock(int n);
private:
	int static kinds;    // ��Ʒ���ࣨstatic��Ա�����ж�����ģ�����������¼�������
	int ID;              // ��ƷID
	int stock;           // �����
	float costPrice;     // �ɱ���
	float price;         // �ۼ�
	char name[30];       // ��Ʒ����
};

#endif
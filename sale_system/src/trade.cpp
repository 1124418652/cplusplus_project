#include "trade.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

bool Trade::buy(int ID, int count)
{
	for (std::list<Commodity>::iterator iter = dataList.begin();
		 iter != dataList.end(); ++iter)
	{
		if (iter->getID() == ID)
		{
			iter->updateStock(count);
			return true;
		}
	}
	return false;
}

bool Trade::sell(int ID, int count)
{
	for (std::list<Commodity>::iterator iter = dataList.begin();
		 iter != dataList.end(); ++iter)
	{
		if (iter->getID() == ID && iter->getStock() - count >= 0)
		{
			iter->updateStock(-count);
			return true;
		}
	}
	return false;
}

void Trade::addNew(char name[], float costPrice, float price)
{
	dataList.push_back(Commodity(name, costPrice, price));
}

bool Trade::init()
{
	std::ifstream file("../doc/stock.txt");
	if (file.good())     // ����stock.txt�ļ�
	{
		char titles[CAP][TLEN] = {"ID:", "NAME:", "COST:", "PRICE:", "STOCK:"};
		char saves[CAP][ALEN] = {"", "", "", "", ""};
		int tIndex = 0;  // �ļ���ÿ�����ݵ�����        
		char buf[128];
		int kinds = 0;
		for (int i = 0; i < 3; ++i)      // �ļ��е�ǰ����Ϊ�ĵ����⣬����ʱ���Ա���
		{
			file.getline(buf, 128);
		}
		while (!file.eof())
		{
			char temp[TLEN] = "";
			for (int i = 0; i < TLEN && !file.eof(); ++i)   // ��һ��ѭ��ȡ����
			{
				file.get(temp[i]);       // ���ļ�������ȡһ���ַ���temp������
				if (0 == strcmp(temp, titles[tIndex]))
				{
					for (int j = 0; j < ALEN && !file.eof(); ++j)   // �ڶ���ѭ��ȡ��Ӧ����ֵ
					{
						char c;
						file.get(c);
						if ('\t' != c && '\n' != c) // c�Ȳ���ֵ�ķָ���Ҳ�����зָ�   
							saves[tIndex][j] = c;
						else if ('\n' != c)    // c��ֵ�ָ�
						{
							if (tIndex > 4)    // ����ļ�����һ���г���5��ֵ��˵���ļ��д�
								return false;
							tIndex ++;
							//saves[tIndex][j] = '\0';
							break;
						}
						else     // c���зָ���
						{
							dataList.push_back(Commodity(atoi(saves[0]), saves[1],
								atof(saves[2]), atof(saves[3]), atoi(saves[4])));
							tIndex = 0;
							kinds ++;
							break;
						}
						if (j == ALEN - 1)
							return false;     // ֵ������Ĭ�ϳ��ȣ��ַ���������һλΪ������\0��
					}
					break;
				}
				if (i == TLEN - 1)
					return false;      // û��ƥ�䵽��Ӧ������
			}
		}
		Commodity::addKinds(kinds);
		file.close();
		return true;
	}
	return false;
}

void Trade::save()    // ��trade�����е���Ʒ��Ϣ���浽�����ļ���
{
	std::ofstream ofile;
	ofile.open("../doc/stock.txt");    // ��Ĭ�ϵ�truncģʽ��
	if (ofile.good())
	{
		ofile << "\t===============================================\n";
		ofile << "\t             ***** ��Ʒ��Ϣ *****              \n";
		ofile << "\t===============================================\n";
		for (std::list<Commodity>::iterator iter = dataList.begin(); 
			 iter != dataList.end(); ++iter)
		{
			ofile << "ID:" << iter->getID()
				<< "\tNAME:" << iter->getName()
				<< "\tCOST:" << iter->getCostPrice()
				<< "\tPRICE:" << iter->getPrice()
				<< "\tSTOCK:" << iter->getStock() << "\n";
		}
		std::cout << "�����ļ��ɹ�" << std::endl; 
	}
	else
	{
		std::cout << "�����ļ�ʧ��" << std::endl;
	}
	ofile.close();
}

void Trade::getIndex()
{
	for (std::list<Commodity>::iterator iter = dataList.begin();
		 iter != dataList.end(); ++iter)
	{
		std::cout << std::setw(10) << "ID" << std::setw(10) <<"NAME" << std::setw(15) <<"COSTPRICE" 
				 << std::setw(10) << "PRICE" << std::setw(10) << "STOCK" << std::endl;
		std::cout << std::setw(10) << iter->getID() << std::setw(10)
			<< iter->getName() << std::setw(15)
			<< iter->getCostPrice() << std::setw(10)
			<< iter->getPrice() << std::setw(10)
			<< iter->getStock() << "\n";
	  }
}

bool Trade::getInformation(int index)
{
	for (std::list<Commodity>::iterator iter = dataList.begin();
		 iter != dataList.end(); iter++)
	{
		if (index == iter->getID())
		{
			std::cout << std::setw(10) << "ID" << std::setw(10) << "NAME" 
				<< std::setw(10) << "STOCK" << std::endl;
			
			std::cout << std::setw(10) << iter->getID() << std::setw(10)
				<< iter->getName() << std::setw(10)
				<<iter->getStock() << "\n" << std::endl;
			return true;
		}
	}
	return false;
}
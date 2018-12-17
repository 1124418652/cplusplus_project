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
	if (file.good())     // 存在stock.txt文件
	{
		char titles[CAP][TLEN] = {"ID:", "NAME:", "COST:", "PRICE:", "STOCK:"};
		char saves[CAP][ALEN] = {"", "", "", "", ""};
		int tIndex = 0;  // 文件中每行数据的索引        
		char buf[128];
		int kinds = 0;
		for (int i = 0; i < 3; ++i)      // 文件中的前三行为文档标题，读入时忽略标题
		{
			file.getline(buf, 128);
		}
		while (!file.eof())
		{
			char temp[TLEN] = "";
			for (int i = 0; i < TLEN && !file.eof(); ++i)   // 第一层循环取名字
			{
				file.get(temp[i]);       // 从文件流中提取一个字符到temp数组中
				if (0 == strcmp(temp, titles[tIndex]))
				{
					for (int j = 0; j < ALEN && !file.eof(); ++j)   // 第二层循环取对应的数值
					{
						char c;
						file.get(c);
						if ('\t' != c && '\n' != c) // c既不是值的分隔，也不是行分隔   
							saves[tIndex][j] = c;
						else if ('\n' != c)    // c是值分隔
						{
							if (tIndex > 4)    // 如果文件中有一行有超过5个值，说明文件有错
								return false;
							tIndex ++;
							//saves[tIndex][j] = '\0';
							break;
						}
						else     // c是行分隔符
						{
							dataList.push_back(Commodity(atoi(saves[0]), saves[1],
								atof(saves[2]), atof(saves[3]), atoi(saves[4])));
							tIndex = 0;
							kinds ++;
							break;
						}
						if (j == ALEN - 1)
							return false;     // 值超出了默认长度（字符数组的最后一位为结束符\0）
					}
					break;
				}
				if (i == TLEN - 1)
					return false;      // 没有匹配到对应的名字
			}
		}
		Commodity::addKinds(kinds);
		file.close();
		return true;
	}
	return false;
}

void Trade::save()    // 将trade对象中的商品信息保存到本地文件中
{
	std::ofstream ofile;
	ofile.open("../doc/stock.txt");    // 以默认的trunc模式打开
	if (ofile.good())
	{
		ofile << "\t===============================================\n";
		ofile << "\t             ***** 商品信息 *****              \n";
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
		std::cout << "存入文件成功" << std::endl; 
	}
	else
	{
		std::cout << "存入文件失败" << std::endl;
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
#include "trade.h"
#include <fstream>

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

bool Trade::init()
{
	std::ifstream file("../doc/stock.txt");
	if (file.good())     // ´æÔÚstock.txtÎÄ¼ş
	{
		char titles[CAP][TLEN] = {"ID:", "NAME:", "COST:", "PRICE:", "STOCK:"};
		char saves[CAP][ALEN];
		int tIndex = 0;
	}
	return false;
}
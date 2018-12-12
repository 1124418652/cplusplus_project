#include "trade.h"
#include <fstream>

bool Trade::buy(int ID, int count)
{
	for (auto iter = dataList.begin();
		 iter != dataList.end(); ++iter)
	{
		if (iter->getID() == ID)
		{
			iter->updateStock(count);
			return true;
		}
	}
}
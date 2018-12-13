#include <iostream>
#include "Commodity.h"
#include "trade.h"

#define CONSOLE_WIDTH 100
#define CONSOLE_HEIGHT 40
#define SYS_TITLE "销售系统"
using namespace std;

static void drawMainMenu()
{
	char console_set[80];
	char title[20];
	sprintf(console_set, "mode con lines=%d cols=%d", CONSOLE_HEIGHT, CONSOLE_WIDTH);
	sprintf(title, "title %s", SYS_TITLE);
	system("cls");
	system(console_set);
	system(title);
	printf("\t||=======================================||\n");
	printf("\t||           欢迎使用销售系统            ||\n");
	printf("\t||=======================================||\n");
	printf("\t||           1 -   购进商品              ||\n");
	printf("\t||           2 -   卖出商品              ||\n");
	printf("\t||           3 -   添加新品              ||\n");
	printf("\t||           4 -   查看商品信息          ||\n");
	printf("\t||           5 -   查看采购记录          ||\n");
	printf("\t||           6 -   查看销售记录          ||\n");
	printf("\t||           7 -   退出                  ||\n");
	printf("\t||=======================================||\n");
}

int main(int argc, char* argv[])
{
	Trade myTrade;
	if (!myTrade.init())
	{
		myTrade = Trade();
	}
	return 0;
}
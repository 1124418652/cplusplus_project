#include <iostream>
#include "Commodity.h"
#include "trade.h"

#define CONSOLE_WIDTH 100
#define CONSOLE_HEIGHT 40
#define SYS_TITLE "销售系统"
using namespace std;

static void conSet()
{
	char console_set[80];
	char title[20];
	sprintf(console_set, "mode con lines=%d cols=%d", CONSOLE_HEIGHT, CONSOLE_WIDTH);
	sprintf(title, "title %s", SYS_TITLE);
	system("cls");
	system(console_set);
	system(title);
}

static void drawMainMenu()
{
	system("cls");
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

static void drawIndex()
{
	system("cls");
	printf("\t=====================================================\n");
	printf("\t              ******  商品目录  ******               \n");
	printf("\t=====================================================\n");
}

static void drawLine()
{
	printf("\t=====================================================\n");
}

void operate()
{
	cout << "按任意键继续" << endl;
	getchar();
	system("cls");
}

void toBuy(int& ID, int& count);
void toSell(int& ID, int& count);

int main(int argc, char* argv[])
{
	conSet();
	Trade myTrade;
	if (!myTrade.init())
	{
		myTrade = Trade();      // 如果init返回值为false，则myTrade拷贝为新的对象
	}
	bool quitFlag = false;
	while(!quitFlag)
	{
		drawMainMenu();
		cout << "请输入您的选项:";
		int selection;
		cin >> selection;
		int ID;
		int count;
		switch (selection)
		{
		case 1:
			drawIndex();
			myTrade.getIndex();
			drawLine();
			toBuy(ID, count);
			if (!myTrade.getInformation(ID))
			{
				std::cout << "没有该商品，请先添加新商品" << std::endl;
				system("pause");
				break;
			}
			if (myTrade.buy(ID, count))
			{
				printf("成功购入%d件商品%d。\n", count, ID);
				system("pause");
			}
			else
			{
				cout << "购入商品失败" << endl;
			}
			break;
		case 2:
			drawIndex();
			myTrade.getIndex();
			drawLine();
			toSell(ID, count);
			if (!myTrade.getInformation(ID))
			{
				cout << "没有该商品，无法卖出" << endl;
				system("pause");
				break;
			}
			if (myTrade.sell(ID, count))
			{
				printf("成功卖出%d件商品%d。\n", count, ID);
				system("pause");
			}
			else
			{
				cout << "卖出商品失败" << endl;
			}
			break;
		case 3:
			char name[30];
			float costPrice;
			float price;
			getchar();
			cout << "请输入新品名称:";
			cin.getline(name, 29);
			cout << "请输入采购成本价:";
			cin >> costPrice;
			cout << "请输入售价:";
			cin >> price;
			myTrade.addNew(name, costPrice, price);
			cout << "成功添加新品" << endl;
			system("pause");
			break;
		case 4:
			myTrade.getIndex();
			system("pause");
			break;
		case 7:
			cout << "是否确定退出系统?(Y/N):";
			char ans;
			cin >> ans;
			system("pause");
			if ('Y' == ans || 'y' == ans)
			{
				myTrade.save();
				return 0;
			}
			else
				break;
		default:
			break;
		}
	}
	return 0;
}

void toBuy(int& ID, int& count)
{
	//system("cls");
	cout << "请输入需要购进的商品的ID:";
	cin >> ID;
	getchar();
	cout << "请输入需要购进的数目:";
	cin >> count;
}

void toSell(int& ID, int& count)
{
	//system("cls");
	cout << "请输入卖出的商品ID:";
	cin >> ID;
	getchar();
	cout << "请输入卖出的商品数目:";
	cin >> count;
}
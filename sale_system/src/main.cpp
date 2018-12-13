#include <iostream>
#include "Commodity.h"
#include "trade.h"

#define CONSOLE_WIDTH 100
#define CONSOLE_HEIGHT 40
#define SYS_TITLE "����ϵͳ"
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
	printf("\t||           ��ӭʹ������ϵͳ            ||\n");
	printf("\t||=======================================||\n");
	printf("\t||           1 -   ������Ʒ              ||\n");
	printf("\t||           2 -   ������Ʒ              ||\n");
	printf("\t||           3 -   �����Ʒ              ||\n");
	printf("\t||           4 -   �鿴��Ʒ��Ϣ          ||\n");
	printf("\t||           5 -   �鿴�ɹ���¼          ||\n");
	printf("\t||           6 -   �鿴���ۼ�¼          ||\n");
	printf("\t||           7 -   �˳�                  ||\n");
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
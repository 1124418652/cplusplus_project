#include <iostream>
#include "Commodity.h"
#include "trade.h"

#define CONSOLE_WIDTH 100
#define CONSOLE_HEIGHT 40
#define SYS_TITLE "����ϵͳ"
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

static void drawIndex()
{
	system("cls");
	printf("\t=====================================================\n");
	printf("\t              ******  ��ƷĿ¼  ******               \n");
	printf("\t=====================================================\n");
}

static void drawLine()
{
	printf("\t=====================================================\n");
}

void operate()
{
	cout << "�����������" << endl;
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
		myTrade = Trade();      // ���init����ֵΪfalse����myTrade����Ϊ�µĶ���
	}
	bool quitFlag = false;
	while(!quitFlag)
	{
		drawMainMenu();
		cout << "����������ѡ��:";
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
				std::cout << "û�и���Ʒ�������������Ʒ" << std::endl;
				system("pause");
				break;
			}
			if (myTrade.buy(ID, count))
			{
				printf("�ɹ�����%d����Ʒ%d��\n", count, ID);
				system("pause");
			}
			else
			{
				cout << "������Ʒʧ��" << endl;
			}
			break;
		case 2:
			drawIndex();
			myTrade.getIndex();
			drawLine();
			toSell(ID, count);
			if (!myTrade.getInformation(ID))
			{
				cout << "û�и���Ʒ���޷�����" << endl;
				system("pause");
				break;
			}
			if (myTrade.sell(ID, count))
			{
				printf("�ɹ�����%d����Ʒ%d��\n", count, ID);
				system("pause");
			}
			else
			{
				cout << "������Ʒʧ��" << endl;
			}
			break;
		case 3:
			char name[30];
			float costPrice;
			float price;
			getchar();
			cout << "��������Ʒ����:";
			cin.getline(name, 29);
			cout << "������ɹ��ɱ���:";
			cin >> costPrice;
			cout << "�������ۼ�:";
			cin >> price;
			myTrade.addNew(name, costPrice, price);
			cout << "�ɹ������Ʒ" << endl;
			system("pause");
			break;
		case 4:
			myTrade.getIndex();
			system("pause");
			break;
		case 7:
			cout << "�Ƿ�ȷ���˳�ϵͳ?(Y/N):";
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
	cout << "��������Ҫ��������Ʒ��ID:";
	cin >> ID;
	getchar();
	cout << "��������Ҫ��������Ŀ:";
	cin >> count;
}

void toSell(int& ID, int& count)
{
	//system("cls");
	cout << "��������������ƷID:";
	cin >> ID;
	getchar();
	cout << "��������������Ʒ��Ŀ:";
	cin >> count;
}
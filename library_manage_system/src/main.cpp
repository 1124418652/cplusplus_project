#include <iostream>
#include <iomanip>      // io����
#include <stdlib.h>     // ��׼ģ����ļ�
#include <conio.h>      // ����̨io���ͷ�ļ�
#include <string>
#include <fstream>
#include "Book.h"

#define CMD_COLS 80
#define CMD_ROWS 25
using namespace std;

void setScreenGrid();    // ����console����Ĵ�С
void clearScreen();      // ���console
void setSysCaption(const char*);  // ���ô��ڱ���
void showWelcome();      // ��ʾ��ӭ��Ϣ
void showRootMenu();     // ��ʾ��ʼ�˵�
void waitUser();         // �ȴ��û�����
void guideInput();       // ʹ�������ͼ����Ϣ
int getSelect();         // ��ȡ�û��˵�ѡ��
long getFileLength(ifstream& ifs); // ��ȡ�ļ�����
void viewData(int iSelPage);   // ���ָ��ҳ��ͼ���¼
void showDataset();
void deleteBookFromFile(); // ���ļ���ɾ��ͼ���¼
void mainLoop();         // ��ѭ��

int main()
{
	setSysCaption("library management system");
	setScreenGrid();
	mainLoop();
	return 0;
}

/*
  ��console�У�ͨ��mode������Ը���console��ʾ������������
  ����ʹ��system������ִ��console�е�����
*/
void setScreenGrid()
{
	char sysSetBuf[80];
	sprintf(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_ROWS);
	system(sysSetBuf);
}

void clearScreen()
{
	system("cls");
}

void setSysCaption(const char* titleName)
{
	char* sysTitleBuf = new char[80];
	sprintf(sysTitleBuf, "title %s", titleName);
	system(sysTitleBuf);
}

void showWelcome()
{
	for (int i = 0; i < 7; ++i)
		cout << endl;
	cout << setw(50);
	cout << "******************************" << endl;
	cout << setw(40);
	cout << "ͼ�����ϵͳ" << endl;
	cout << setw(50);
	cout << "******************************" << endl;
}

void showRootMenu()
{
	cout << setw(40);
	cout << "��ѡ����" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 �������" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 ���ȫ��" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 ɾ��ͼ��" << endl;
	cout << endl;
}

void waitUser()
{
	int iInputPage = 0;
	cout << "enter �������˵� \t q �˳�" << endl;
	char buf[256];
	gets(buf);
	if ('q' == buf[0])
		system("exit");
}

int getSelect()
{
	char buf[256];
	gets(buf);
	return atoi(buf);
}

void mainLoop()
{
	showWelcome();
	while (1)
	{
		clearScreen();
		showWelcome();
		showRootMenu();
		switch (getSelect())
		{
		case 1:
			clearScreen();
			guideInput();
			break;
		case 2:
			clearScreen();
			showDataset();
			break;
		case 3:
			clearScreen();
			deleteBookFromFile();
			break;
		default:
			break;
		}
		waitUser();
	}
}

void guideInput()
{
	char inName[NUM1];
	char inlsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "������������";
	gets(inName);
	cout << endl;
	cout << "������ISBN��";
	gets(inlsbn);
	cout << endl;
	cout << "������۸�";
	gets(inPrice);
	cout << endl;
	cout << "���������ߣ�";
	gets(inAuthor);
	cout << endl;

	CBook book(inName, inlsbn, inPrice, inAuthor);
	book.writeData();
	cout << "Write finish" << endl << endl;
	waitUser();
}

void viewData(int iSelPage = 1)
{
	int iPage = 0;
	int iCurPage = iSelPage;
	int iDataCount = 0;
	char inName[NUM1];
	char inlsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength = 0;
	ifstream ifile;
	ifile.open("../dataBase/book.dat", ios::binary);
	iFileLength = getFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;

	// ׼����ӡ��Ϣ
	clearScreen();
	cout << "���м�¼��" << iDataCount << "��" << " ";
	cout << "����ҳ����" << iPage << "ҳ" << ' ';
	cout << "��ǰΪ�� " << iCurPage << "ҳ" << endl;
	cout << "n ��ʾ��һҳ��b ��ʾ��һҳ��m �˳�" << endl;
	cout << setw(5) << "Index";
	cout << setw(22) << "Name";
	cout << setw(22) << "LSBN";
	cout << setw(15) << "Price";
	cout << setw(15) << "Author" << endl;
	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2),
					std::ios_base::beg);
		if (ifile.good())
		{
			for (int i = 1; i < 21; ++i)    // ��ȡһҳ�ļ�¼��20����
			{
				memset(inName, 0, NUM1);    // �Ƚ���������
				memset(inlsbn, 0, NUM1);
				memset(inPrice, 0, NUM2);
				memset(inAuthor, 0, NUM2);
				if (bIndex)                 // ��ӡIndex
					cout << setw(5) << (iCurPage - 1) * 20 + i;
				ifile.read(inName, NUM1); 
				cout << setw(22) << inName;
				ifile.read(inlsbn, NUM1);
				cout << setw(22) << inlsbn;
				ifile.read(inPrice, NUM2);
				cout << setw(15) << inPrice;
				ifile.read(inAuthor, NUM2);
				cout << setw(15) << inAuthor << endl;
			}
		}
		ifile.close();
	}
	catch (...)
	{
		cout << "throw file exception" << endl;
		throw "file error occurred";
		ifile.close();
	}
}

long getFileLength(ifstream& ifs)
{
	long tmpPos;    // ��¼�ļ���ԭ�ȵ�ָ��λ��
	long resPos;
	tmpPos = ifs.tellg();
	ifs.seekg(0, std::ios_base::end);
	resPos = ifs.tellg();
	ifs.seekg(tmpPos, std::ios_base::beg);  // ���ļ�ָ�븴ԭ
	return resPos;
}

void showDataset()
{
	int iSelPage = 1;
	viewData(iSelPage);
	while (1)
	{
		char inputBuf[10];
		gets(inputBuf);
		if ('n' == inputBuf[0])
		{
			iSelPage += 1;
			viewData(iSelPage);
		}
		else if ('b' == inputBuf[0])
		{
			if (iSelPage > 1)
			{
				iSelPage -= 1;
				viewData(iSelPage);
			}
			else
			{
				cout << "��ǰ�Ѿ��ǵ�һҳ" << endl;
			}
		}
		else if ('m' == inputBuf[0])
			break;
	}
	return;
}

void deleteBookFromFile()
{
	int iCount = 0;
	long fileSize = 0;
	int dataSize = 0;
	while (1)
	{
		cout << "������Ҫɾ���ļ�¼��������";
		cin >> iCount;
		ifstream file;
		file.open("../dataBase/book.dat", ios::binary);
		file.seekg(0, std::ios_base::end);
		fileSize = file.tellg();
		dataSize = fileSize / (NUM1 + NUM1 + NUM2 + NUM2);
		if (dataSize < iCount)
		{
			int usrSelect;
			cout << "Don't have so mush records." << endl;
			cout << "Press \'Enter\' to retry or \'q\' to quit" << endl;
			while (1)
			{
				if (_kbhit())
				{
					usrSelect = _getch();
					cout <<usrSelect<<endl;
					if (13 == usrSelect)
						break;
					else if (113 == usrSelect)
						return;
				}
			}
			continue;
		}
		else if (iCount <= 0)
		{
			cout << "the index must larger than 0" << endl;
			continue;
		}
		else
		{
			CBook book;
			book.deleteData(iCount);
		}
	}
	
}
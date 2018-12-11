#include <iostream>
#include <iomanip>      // io操作
#include <stdlib.h>     // 标准模板库文件
#include <conio.h>      // 控制台io相关头文件
#include <string>
#include <fstream>
#include "Book.h"

#define CMD_COLS 80
#define CMD_ROWS 25
using namespace std;

void setScreenGrid();    // 设置console窗体的大小
void clearScreen();      // 清除console
void setSysCaption(const char*);  // 设置窗口标题
void showWelcome();      // 显示欢迎信息
void showRootMenu();     // 显示开始菜单
void waitUser();         // 等待用户操作
void guideInput();       // 使用向导添加图书信息
int getSelect();         // 获取用户菜单选择
long getFileLength(ifstream& ifs); // 获取文件长度
void viewData(int iSelPage);   // 浏览指定页的图书记录
void showDataset();
void deleteBookFromFile(); // 从文件中删除图书记录
void mainLoop();         // 主循环

int main()
{
	setSysCaption("library management system");
	setScreenGrid();
	mainLoop();
	return 0;
}

/*
  在console中，通过mode命令可以更改console显示的行数和列数
  这里使用system函数来执行console中的命令
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
	cout << "图书管理系统" << endl;
	cout << setw(50);
	cout << "******************************" << endl;
}

void showRootMenu()
{
	cout << setw(40);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 添加新书" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 浏览全部" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 删除图书" << endl;
	cout << endl;
}

void waitUser()
{
	int iInputPage = 0;
	cout << "enter 返回主菜单 \t q 退出" << endl;
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

	cout << "请输入书名：";
	gets(inName);
	cout << endl;
	cout << "请输入ISBN：";
	gets(inlsbn);
	cout << endl;
	cout << "请输入价格：";
	gets(inPrice);
	cout << endl;
	cout << "请输入作者：";
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

	// 准备打印信息
	clearScreen();
	cout << "共有记录：" << iDataCount << "条" << " ";
	cout << "共有页数：" << iPage << "页" << ' ';
	cout << "当前为第 " << iCurPage << "页" << endl;
	cout << "n 显示下一页，b 显示上一页，m 退出" << endl;
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
			for (int i = 1; i < 21; ++i)    // 读取一页的记录（20条）
			{
				memset(inName, 0, NUM1);    // 先将变量清零
				memset(inlsbn, 0, NUM1);
				memset(inPrice, 0, NUM2);
				memset(inAuthor, 0, NUM2);
				if (bIndex)                 // 打印Index
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
	long tmpPos;    // 记录文件流原先的指针位置
	long resPos;
	tmpPos = ifs.tellg();
	ifs.seekg(0, std::ios_base::end);
	resPos = ifs.tellg();
	ifs.seekg(tmpPos, std::ios_base::beg);  // 将文件指针复原
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
				cout << "当前已经是第一页" << endl;
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
		cout << "请输入要删除的记录的索引：";
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
#include "Book.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

CBook::CBook(char *cName, char *clsbn, char *cPrice, char *cAuthor)
{
	strncpy(m_cName, cName, NUM1);
	strncpy(m_clsbn, clsbn, NUM1);
	strncpy(m_cPrice, cPrice, NUM2);
	strncpy(m_cAuthor, cAuthor, NUM2);
}

char* CBook::getName()
{
	return m_cName;
}

void CBook::setName(char* cName)
{
	/*
	strncpy ����� strcpy ���Ը���ȫ��strcpy��s2�ĳ��ȴ���s1ʱ
	�ᷢ�������strncpyֻҪ��֤n>s2�ĳ��ȾͲ���������
	*/
	strncpy(m_cName, cName, NUM1);    
}

char* CBook::getlsbn()
{
	return m_clsbn;
}

void CBook::setlsbn(char* clsbn)
{
	strncpy(m_clsbn, clsbn, NUM1);
}

void CBook::getPrice()
{
	return m_cPrice;
}

char* CBook::setPrice(char* cPrice)
{
	strncpy(m_cPrice, cPrice, NUM2);
}

void CBook::getAuthor()
{
	return m_cAuthor;
}

char* CBook::setAuthor(char* cAuthor)
{
	strncpy(m_cAuthor, cAuthor, NUM2);
}

void CBook::writeData()
{
	ofstream ofile;
	ofile.open("../dataBase/book.dat", ios::binary|ios::app);
	if (!ofile.good())
		return;
	try
	{
		ofile.write(m_cName, NUM1);
		ofile.write(m_clsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);
	}
	catch (CFileException* e)
	{
		throw "file error occurred";
		ofile.close();
	}
	catch (CException* e)
	{
	}
	ofile.close();
}
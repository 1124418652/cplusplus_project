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

char* CBook::getName(){
	return m_cName;
}

void CBook::setName(char* cName)
{
	/*
	strncpy ����� strcpy ���Ը���ȫ��strcpy��s2�ĳ��ȴ���s1ʱ
	�ᷢ�������strncpyֻҪ��֤n>s2�ĳ��ȾͲ���������.
	memcpy��strncpy���ƣ�����memcpy���Զ�ȡ\0
	*/
	strncpy(m_cName, cName, NUM1);    
}

char* CBook::getlsbn(){
	return m_clsbn;
}

void CBook::setlsbn(char* clsbn){
	strncpy(m_clsbn, clsbn, NUM1);
}

char* CBook::getPrice(){
	return m_cPrice;
}

void CBook::setPrice(char* cPrice){
	strncpy(m_cPrice, cPrice, NUM2);
}

char* CBook::getAuthor(){
	return m_cAuthor;
}

void CBook::setAuthor(char* cAuthor){
	strncpy(m_cAuthor, cAuthor, NUM2);
}

/*
  ��ͼ�����д�뵽�ļ���
  */
void CBook::writeData()
{
	std::ofstream ofile;
	ofile.open("../dataBase/book.dat", std::ios::binary|std::ios::app);

	try
	{
		ofile.write(m_cName, NUM1);
		ofile.write(m_clsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);
	}
	catch (...)
	{
		throw "file error occurred";
		ofile.close();
	}
	ofile.close();
}

/*
  ���ļ��ж�ȡ����������ͼ�����
  */
void CBook::getBookFromFile(int iCount)
{
	char cName[NUM1];
	char clsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	std::ifstream ifile;
	ifile.open("../dataBase/book.dat", std::ios::binary);

	try
	{
		ifile.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2), std::ios_base::beg);  // seekgָ��λ��
		ifile.read(cName, NUM1);
		if (ifile.tellg() > 0)
			strncpy(m_cName, cName, NUM1);
		ifile.read(clsbn, NUM1);
		if (ifile.tellg() > 0)
			strncpy(m_clsbn, clsbn, NUM1);
		ifile.read(cPrice, NUM2);
		if (ifile.tellg() > 0)
			strncpy(m_cPrice, cPrice, NUM2);
		ifile.read(cAuthor, NUM2);
		if (ifile.tellg() > 0)
			strncpy(m_cAuthor, cAuthor, NUM2);
	}
	catch (...)
	{
		throw "file error occurred";
		ifile.close();
	}
	ifile.close();
}

/*
  ���ļ���ɾ��ָ��������
  */
void CBook::deleteData(int iCount)
{	
	long respos;
	int iDataCount = 0;
	std::fstream file;
	std::fstream tmpfile;
	std::ofstream ofile;
	char cTempBuf[NUM1 * 2 + NUM2 * 2];
	file.open("../dataBase/book.dat", 
			  std::ios::binary|std::ios::in|std::ios::out);
	tmpfile.open("../dataBase/tmp.dat",
				 std::ios::binary|std::ios::trunc|std::ios::in|std::ios::out);
	file.seekg(0, std::ios_base::end);    // ��λ���ļ������
	respos = file.tellg();                // ��ȡ��ǰ�ļ�ָ���λ�ã��ļ���󣬿����ɴ˼�����ļ������ݵĴ�С��
	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2);   // �ܹ���������������
	if (iCount < 0 || iCount > iDataCount)
		throw "input number error";
	else
	{
		file.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2), std::ios_base::beg);  // �������ļ��е�������0��ʼ
		for (int j = 0; j < (iDataCount - iCount); ++j)   // ÿִ��һ��ѭ�����ļ���ָ�����
		{
			memset(cTempBuf, 0, (NUM1 + NUM1 + NUM2 + NUM2));   // ��cTempBuf�е�����λ��0���
			file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);     // ��ȡ��Ҫɾ��������֮�������
			tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}
		file.close();
		tmpfile.seekg(0, std::ios_base::beg);
		ofile.open("../dataBase/book.dat");     // Ĭ����truncģʽ���ļ�
		ofile.seekp(iCount * (NUM1 + NUM1 + NUM2 + NUM2) - 1, std::ios::beg);
		for (int i = 0; i < (iDataCount - iCount); ++i)
		{
			memset(cTempBuf, 0, (NUM1 + NUM1 + NUM2 + NUM2));
			tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}
	}
	tmpfile.close();
	ofile.close();
	remove("../dataBase/book.dat");
}
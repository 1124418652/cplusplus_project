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
	strncpy 相比于 strcpy 而言更安全，strcpy在s2的长度大于s1时
	会发生溢出，strncpy只要保证n>s2的长度就不会有问题.
	memcpy与strncpy类似，但是memcpy可以读取\0
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
  将图书对象写入到文件中
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
  从文件中读取数据来构建图书对象
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
		ifile.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2), std::ios_base::beg);  // seekg指定位置
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
  从文件中删除指定的数据
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
	file.seekg(0, std::ios_base::end);    // 定位到文件的最后
	respos = file.tellg();                // 获取当前文件指针的位置（文件最后，可以由此计算出文件中内容的大小）
	iDataCount = respos / (NUM1 + NUM1 + NUM2 + NUM2);   // 总共包含的数据条数
	if (iCount < 0 || iCount > iDataCount)
		throw "input number error";
	else
	{
		file.seekg(iCount * (NUM1 + NUM1 + NUM2 + NUM2), std::ios_base::beg);  // 数据在文件中的索引从0开始
		for (int j = 0; j < (iDataCount - iCount); ++j)   // 每执行一次循环，文件流指针后移
		{
			memset(cTempBuf, 0, (NUM1 + NUM1 + NUM2 + NUM2));   // 将cTempBuf中的所有位用0填充
			file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);     // 读取出要删除的数据之后的数据
			tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}
		file.close();
		tmpfile.seekg(0, std::ios_base::beg);
		ofile.open("../dataBase/book.dat");     // 默认以trunc模式打开文件
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
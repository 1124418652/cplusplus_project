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
	会发生溢出，strncpy只要保证n>s2的长度就不会有问题
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

void CBook::writeData()
{
	std::ofstream ofile;
	ofile.open("../dataBase/book.dat", std::ios::binary|std::ios::app);
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
	ofile.close();
}

void CBook::getBookFromFile(int iCount)
{
	char cName[NUM1];
	char clsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	std::ifstream ifile;
	ifile.open("../dataBase/book.dat", std::ios::binary);
	if (!ifile.good())
		return;
	try
	{
		ifile.seekg(iCount * (NUM1 * 2 + NUM2 * 2), std::ios_base::beg);
		ifile.read(cName, NUM1);

	}
	catch (CFileException* e)
	{
		throw "file error occurred";
		ifile.close();
	}
}
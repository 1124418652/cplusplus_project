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
	strncpy 相比于 strcpy 而言更安全，strcpy在s2的长度大于s1时
	会发生溢出，strncpy只要保证n>s2的长度就不会有问题
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
	
}
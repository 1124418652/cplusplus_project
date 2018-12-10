#define NUM1 128
#define NUM2 50

class CBook
{
public:
	CBook() = default;
	CBook(char *cName, char *clsbn, char *cPrice, char *cAuthor);
	~CBook(){}
	char* getName();
	void setName(char* cName);
	char* getlsbn();
	void setlsbn(char* clsbn);
	char* getAuthor();
	void setAuthor(char* cAuthor);
	char* getPrice();
	void setPrice(char* cPrice);
	void writeData();
	void deleteData(int iCount);
	void getBookFromFile(int iCount);
protected:
	char m_cName[NUM1];
	char m_clsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};
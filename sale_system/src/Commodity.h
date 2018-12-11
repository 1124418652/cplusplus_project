class Commodity
{
public:
	Commodity(char name[], float costPrice, float price);
	int getID();
	int getStock();
	float getCostPrice();
	float getPrice();
	char* getName();
	void updateStock(int n);
private:
	int static kinds;    // 商品种类（static成员是所有对象共享的，可以用来记录类别数）
	int ID;              // 商品ID
	int stock;           // 库存量
	float costPrice;     // 成本价
	float price;         // 售价
	char name[30];       // 商品名称
};

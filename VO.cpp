
#include <string>
#include <vector>
using namespace std;

//base class(parent)
class Info {
	public:
		int stt=0;
		string name, address, phone, email;
};
//child
class Client : public Info {
	// The structure to store city information;
	
};

//child
class SaleRep : public Info{

};

class Product {
	public:
		int stt = 0;
		double price = 0.0;
		string  name;
		bool active=0;
};

class SaleHistory {
	public:
		int stt =0, saleRep = 0, prod =0, client = 0, quantity = 0;
		string date;
		double total = 0;
};

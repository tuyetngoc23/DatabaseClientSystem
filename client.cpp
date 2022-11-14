#include <vector>
#include "VO.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "client.h"
#include "sales.h"


//Client client[100];
vector<Client> client;
//getline in file
void explode(Client& client, const string& s, const char& c) {
    string buff{ "" };
    vector<string> v;

    for (auto n : s) {
        if (n != c)
            buff += n;
        else if (n == c && buff != "") {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);
    //getline file, lint have string -> save stt=0
    if (v.size() == 5) {
        if (v[0] == "Stt") {
            client.stt= 0;
        }
        else {
            client.stt = atoi(v[0].c_str());
        }        
        client.name = v[1];
        client.address = v[2];
        client.phone = v[3];
        client.email = v[4];
    }
}

void readFile(string fileName) {
    string line;
    int i = 0;
    client = {};
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            Client cl;            
            explode(cl, line, ','); //getline 1 Client
            client.push_back(cl); //inser into vector Client
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}
void writeFile(string fileName) {
    ofstream ptr;
    ptr.open(fileName);
    //add header tag into file
    ptr << "Stt" << ',' << "Name"  << ',' << "Address" << ',' << "Phone" << ',' << "Email" << '\n';
    //add vector Client into file
    int i = 1;
    while (i < client.size()) {
        ptr << client.at(i).stt << "," << client.at(i).name << "," << client.at(i).address << "," << client.at(i).phone << ","
            << client.at(i).email << '\n';
        cout << "Flie saved" << endl;
        i++;
    }
    ptr.close();
}

//list all object
void listAll() {
    int index = 0;
    string short_address; 
    double total = 0;
    for (int i = 1; i < client.size(); i++) {
        if (client[i].stt == 0) {
            break;
        }
        else {
            //calculate total sales of each client
            vector<SaleHistory> sales = getListClient(client.at(i).stt);
            total = 0;
            if (sales.size() > 0) {                
                for (int k = 0; k < sales.size(); k++) {
                    if (sales.at(k).total > 0) {
                        total = total + sales.at(k).total;
                    }
                }
            }
            //get short address after '-'
            //shor address is string after '-'
            for (int j = client[i].address.length() - 1; j >= 0; j--) {
                if (client[i].address[j] == '-') {
                    index = j;
                    break;
                }
                else {
                    index = 0;
                }
            }
            if (index != 0) {
                short_address = client[i].address.substr(index + 1);
            }
            else {
                short_address = client[i].address.substr(index);
            }

            cout << "Stt: " << client[i].stt << " == Name: " << client[i].name << " == Address: " << short_address
                << " == Total sales: " << total << endl;
        }
    }
}

//view detail each Client
void viewDetailClient(int i) {
    if (i >= client.size() || i == 0) {
        cout << "No row" << endl;
    }
    else {
        cout << "Stt: " << client[i].stt << "\nName: " << client[i].name << "\nAddress: " << client[i].address
            << "\nPhone: " << client[i].phone << "\nEmail: " << client[i].email << endl;
    }

}
//add client into vector Client
void addClient(Client a) {
    
    a.stt = client.size();
    client.push_back(a);

}
//update client into vector Client
void updateClient(int index, Client a) {
    if (index >= client.size() || index == 0) {
        cout << "Row number not exist!!" << endl;
    }
    else {
        client.at(index) = a;
    }

}

//get client with id
Client getClient(int i)
{
    Client a;
    readFile("client.csv");
    if (i < client.size()) {
        a = client.at(i);
    }
    return a;
    
}

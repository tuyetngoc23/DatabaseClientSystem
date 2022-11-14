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
            /*cout << line << '\n';*/
            explode(cl, line, ',');
            client.push_back(cl);
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}
void writeFile(string fileName) {
    ofstream ptr;
    ptr.open(fileName);
    ptr << "Stt" << ',' << "Name"  << ',' << "Address" << ',' << "Phone" << ',' << "Email" << '\n';
    int i = 1;
    while (i < client.size()) {
        ptr << client.at(i).stt << "," << client.at(i).name << "," << client.at(i).address << "," << client.at(i).phone << ","
            << client.at(i).email << '\n';
        cout << "Flie saved" << endl;
        i++;
    }
    ptr.close();
}

void listAll() {
    int index = 0;
    string short_address; 
    double total = 0;
    for (int i = 1; i < client.size(); i++) {
        if (client[i].stt == 0) {
            break;
        }
        else {
            vector<SaleHistory> sales = getListClient(client.at(i).stt);
            total = 0;
            if (sales.size() > 0) {                
                for (int k = 0; k < sales.size(); k++) {
                    if (sales.at(k).total > 0) {
                        total = total + sales.at(k).total;
                    }
                }
            }            
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

void viewDetailClient(int i) {
    if (i >= client.size() || i == 0) {
        cout << "No row" << endl;
    }
    else {
        cout << "Stt: " << client[i].stt << "\nName: " << client[i].name << "\nAddress: " << client[i].address
            << "\nPhone: " << client[i].phone << "\nEmail: " << client[i].email << endl;
    }

}
void addClient(Client a) {
    /*int index = 0;*/
    /*for (int i = 1; i < client.size(); i++) {
        if (client[i].stt == 0) {
            index = i;
            break;
        }
    }*/
   /* ostringstream convert;
    convert << index;
    a.stt = convert.str();*/
    a.stt = client.size();
    /*client[client.size()].stt = index;
    client[client.size()].name = a.name;
    client[client.size()].address = a.address;
    client[client.size()].phone = a.phone;
    client[client.size()].email = a.email;*/
    client.push_back(a);

}
void updateClient(int index, Client a) {
    if (index >= client.size() || index == 0) {
        cout << "Row number not exist!!" << endl;
    }
    else {
        /*client.at(index).stt = a.stt;
        client.at(index).name = a.name;
        client.at(index).address = a.address;
        client.at(index).email = a.email;
        client.at(index).phone = a.phone;*/
        client.at(index) = a;
        /*client.push_back(a);*/
    }

}

Client getClient(int i)
{
    Client a;
    readFile("client.csv");
    if (i < client.size()) {
        a = client.at(i);
    }
    return a;
    
}

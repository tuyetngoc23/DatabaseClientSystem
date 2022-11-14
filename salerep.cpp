#define _CRT_SECURE_NO_WARNINGS
#include "VO.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "salerep.h"
#include "sales.h"

//SaleRep saleRep[100];
vector<SaleRep> saleRep = {};

void explode(SaleRep& saler, const string& s, const char& c) {
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
            saler.stt = 0;
        }
        else {
            saler.stt = atoi(v[0].c_str());
        }
        
        saler.name = v[1];
        saler.address = v[2];
        saler.phone = v[3];
        saler.email = v[4];
    }
}
void readFileSaler(string fileName) {
    string line;
    int i = 0;
    saleRep = {};
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            /*cout << line << '\n';*/
            SaleRep s;
            explode(s, line, ',');
            saleRep.push_back(s);
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}
void writeFileSaler(string fileName) {
    ofstream ptr;
    ptr.open(fileName);
    ptr << "Stt" << ',' << "Name"  << ',' << "Address" << ',' << "Phone" << ',' << "Email" << '\n';
    int i = 1;
    while (i < saleRep.size()) {
        ptr << saleRep.at(i).stt << "," << saleRep.at(i).name << "," << saleRep.at(i).address << "," << saleRep.at(i).phone << ","
            << saleRep.at(i).email << '\n';
        cout << "File saved" << endl;
        i++;
    }
}
void listAllSaleRep() {
    int index = 0;
    string short_address;
    double total{};
    for (int i = 1; i < saleRep.size(); i++) {
        if (saleRep[i].stt == 0) {
            break;
        }
        else {
            vector<SaleHistory> sales = getListSaler(saleRep.at(i).stt);
            total = 0;
            if (sales.size() > 0) {                
                for (int k = 0; k < sales.size(); k++) {
                    if (sales.at(k).total > 0) {
                        total = total + sales.at(k).total;
                    }
                }
            }
            for (int j = saleRep[i].address.length() - 1; j >= 0; j--) {
                if (saleRep[i].address[j] == '-') {
                    index = j;
                    break;
                }
                else {
                    index = 0;
                }
            }
            if (index != 0) {
                short_address = saleRep[i].address.substr(index + 1);
            }
            else {
                short_address = saleRep[i].address.substr(index);
            }

            cout << "Stt: " << saleRep[i].stt << " == Name: " << saleRep[i].name << " == Address: " << short_address 
                << " == Total sales: " << total << endl;
        }
    }
}
void viewDetailSaleRep(int i) {
    if (saleRep.size() <= i || i == 0) {
        cout << "No row" << endl;
    }
    else {
        vector<int> monthly;
        vector<double> totalmonthly;
        vector<int> yearly;
        vector<SaleHistory> sales = getListSaler(saleRep.at(i).stt);
        
        int day, month, year;
        time_t t = time(0);
        int yearCrr = (localtime(&t)->tm_year + 1900);
        for (int j = 0; j < sales.size(); j++) {
            bool flag = true;
            sscanf_s(sales.at(j).date.c_str(), "%2d/%2d/%4d", &day, &month, &year);
            for (int k = 0; k < monthly.size(); k++) {
                if (month == monthly[k]) {
                    flag = false;
                    if (year == yearCrr) {
                        totalmonthly.at(k) = totalmonthly.at(k) + sales.at(j).total;
                    }
                }
            }
            if (flag) {
                if (year == yearCrr) {
                    monthly.push_back(month);
                    totalmonthly.push_back(sales.at(j).total);
                }                
            }                                                 
        }
        
        cout << "Stt: " << saleRep[i].stt << "\nName: " << saleRep[i].name << "\nAddress: " << saleRep[i].address
            << "\nPhone: " << saleRep[i].phone << "\nEmail: " << saleRep[i].email << endl;
        for (int h = 0; h < monthly.size(); h++) {
            cout << "Month: " << monthly[h] <<  " == Total: " << totalmonthly[h]  << endl;
        }
    }
}
void addSaleRep(SaleRep a) {
    /*int index = 0;
    for (int i = 1; i < 100; i++) {
        if (saleRep[i].stt == 0) {
            index = i;
            break;
        }
    }*/
    /*ostringstream convert;
    convert << index;
    a.stt = convert.str();*/
    a.stt = saleRep.size();
    /*saleRep[index].stt = a.stt;
    saleRep[index].name = a.name;
    saleRep[index].address = a.address;
    saleRep[index].phone = a.phone;
    saleRep[index].email = a.email;*/
    saleRep.push_back(a);
}
void updateSaleRep(int index, SaleRep a) {
    if (saleRep.size() <= index || index == 0) {
        cout << "Row number not exist!!" << endl;
    }
    else {
        /*saleRep[index].stt = a.stt;
        saleRep[index].name = a.name;
        saleRep[index].phone = a.phone;
        saleRep[index].address = a.address;
        saleRep[index].email = a.email;*/
        saleRep.at(index) = a;
    }
}

SaleRep getSaler(int i)
{
    SaleRep a;
    readFileSaler("salerep.csv");
    if (i < saleRep.size()) {
        a = saleRep[i];
    }
    return a;
}

double saleBonus(int yearInput, int i)
{
   
    double total=0, bonus;
    int day, month, year;
    vector<SaleHistory> sales = getListSaler(saleRep.at(i).stt);
    for (int j = 0; j < sales.size(); j++) {
        sscanf_s(sales.at(j).date.c_str(), "%2d/%2d/%4d", &day, &month, &year);
        if (yearInput == year) {
            total += sales.at(j).total;
        }
    }
    if (total <= 100) {
        bonus = total * 5 / 100;
    }
    else if (total <= 300) {
        bonus = total * 10 / 100;
    }
    else {
        bonus = total * 20 / 100;
    }
    return bonus;
}

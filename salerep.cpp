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
//getline in file
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
    //stt =0 if have header tag
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
//read file
void readFileSaler(string fileName) {
    string line;
    int i = 0;
    saleRep = {};
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            SaleRep s;
            explode(s, line, ','); // get 1 Saler
            saleRep.push_back(s); // insert into vector salerep
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}
void writeFileSaler(string fileName) {
    ofstream ptr;
    ptr.open(fileName);
    //write header tag into file
    ptr << "Stt" << ',' << "Name"  << ',' << "Address" << ',' << "Phone" << ',' << "Email" << '\n';
    int i = 1;
    //write file to vector salerep: start object 1
    while (i < saleRep.size()) {
        ptr << saleRep.at(i).stt << "," << saleRep.at(i).name << "," << saleRep.at(i).address << "," << saleRep.at(i).phone << ","
            << saleRep.at(i).email << '\n';
        cout << "File saved" << endl;
        i++;
    }
}
//list all Saler
void listAllSaleRep() {
    //init
    int index = 0;
    string short_address;
    double total{};
    for (int i = 1; i < saleRep.size(); i++) {
        //break if tag
        if (saleRep[i].stt == 0) {
            break;
        }
        else {
            //calculate total sales of saler
            vector<SaleHistory> sales = getListSaler(saleRep.at(i).stt);
            total = 0;
            if (sales.size() > 0) {                
                for (int k = 0; k < sales.size(); k++) {
                    if (sales.at(k).total > 0) {
                        total = total + sales.at(k).total;
                    }
                }
            }
            //get short address is string after '-'
            for (int j = saleRep[i].address.length() - 1; j >= 0; j--) {
                if (saleRep[i].address[j] == '-') {
                    index = j;
                    break;
                }
                else {
                    index = 0;
                }
            }
            //check if don't have '-' -> long address = short address
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
//view detail saler
void viewDetailSaleRep(int i) {
    //check saler exist
    if (saleRep.size() <= i || i == 0) {
        cout << "No row" << endl;
    }
    else {
        vector<int> monthly;
        vector<double> totalmonthly;
        vector<int> yearly;
        vector<SaleHistory> sales = getListSaler(saleRep.at(i).stt);
        //get current year
        int day, month, year;
        time_t t = time(0);
        int yearCrr = (localtime(&t)->tm_year + 1900);
        for (int j = 0; j < sales.size(); j++) {
            bool flag = true;
            sscanf_s(sales.at(j).date.c_str(), "%2d/%2d/%4d", &day, &month, &year); // get day, month, year
            //get total sales in month of current year
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
//add saler into vector salerep
void addSaleRep(SaleRep a) {
    
    a.stt = saleRep.size();
    saleRep.push_back(a);
}
//update saler
void updateSaleRep(int index, SaleRep a) {
    //check saler exist
    if (saleRep.size() <= index || index == 0) {
        cout << "Row number not exist!!" << endl;
    }
    else {
        saleRep.at(index) = a;
    }
}

//get 1 SaleRep
SaleRep getSaler(int i)
{
    SaleRep a;
    readFileSaler("salerep.csv");
    if (i < saleRep.size()) {
        a = saleRep[i];
    }
    return a;
}

//calculate sale bonnus year of saler
double saleBonus(int yearInput, int i)
{
   
    double total=0, bonus;
    int day, month, year;
    vector<SaleHistory> sales = getListSaler(saleRep.at(i).stt);
    //calculate total sales year of saler
    for (int j = 0; j < sales.size(); j++) {
        sscanf_s(sales.at(j).date.c_str(), "%2d/%2d/%4d", &day, &month, &year); //get day, month, year
        if (yearInput == year) {
            total += sales.at(j).total;
        }
    }
    // total <= 100 -> bonus 5% sales
    if (total <= 100) {
        bonus = total * 5 / 100;
    }
    // total <= 300 -> bonus 10% sales
    else if (total <= 300) {
        bonus = total * 10 / 100;
    }
    // total > 300 -> bonus 10% sales
    else {
        bonus = total * 20 / 100;
    }
    return bonus;
}

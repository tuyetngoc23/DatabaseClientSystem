#include <vector>
#include "VO.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "sales.h"

//SaleHistory saleHis[100];
vector<SaleHistory> saleHis = {};

void explode(SaleHistory& saleHis, const string& s, const char& c) {
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

    if (v.size() == 7) {
        if (v[0] == "Stt") {
            saleHis.stt = 0;
            saleHis.saleRep = 0;
            saleHis.client = 0;
            saleHis.prod = 0;
            saleHis.quantity = 0;
            saleHis.total = 0;
        }
        else {
            saleHis.stt = atoi(v[0].c_str());
            saleHis.saleRep = atoi(v[1].c_str());
            saleHis.client = atoi(v[2].c_str());
            saleHis.prod = atoi(v[3].c_str());
            saleHis.quantity = atoi(v[4].c_str());
            saleHis.total = atof(v[6].c_str());
        }
        saleHis.date = v[5];
    }
}
void readFileSales(string fileName)
{
    string line;
    int i = 0;
    saleHis = {};
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            SaleHistory sa;
            /*cout << line << '\n';*/
            explode(sa, line, ',');
            saleHis.push_back(sa);
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

void writeFileSales(string fileName)
{
    ofstream ptr;
    ptr.open(fileName);
    ptr << "Stt" << ',' << "SaleRep" << ',' << "Client" << ',' << "Product" << ',' << "Quantity" << "," 
        << "Date" << "," << "Total" << '\n';
    int i = 1;
    while (i < saleHis.size()) {
        ptr << saleHis[i].stt << "," << saleHis[i].saleRep << "," << saleHis[i].client << "," << saleHis[i].prod << ","
            << saleHis[i].quantity << "," << saleHis[i].date << "," << saleHis[i].total << '\n';
        cout << "File saved" << endl;
        i++;
    }
}

void listAllSales()
{
    int index = 0;
    for (int i = 1; i < saleHis.size(); i++) {
        if (saleHis[i].stt == 0) {
            break;
        }
        else {
            cout << "Stt: " << saleHis[i].stt << " == SaleRep: " << saleHis[i].saleRep << " == Client: " << saleHis[i].client
                << " == Product: " << saleHis[i].prod << endl;
        }
    }
}

void viewDetailSales(int i)
{
    if (saleHis.size() <= i || i == 0) {
        cout << "No row" << endl;
    }
    else {
        cout << "Stt: " << saleHis[i].stt << "\nSale Representatives: " << saleHis[i].saleRep << "\nClient: " << saleHis[i].client
            << "\nProduct: " << saleHis[i].prod << "\nQuantity: " << saleHis[i].quantity << "\nDate: " << saleHis[i].date
            << "\nTotal: " << saleHis[i].total << endl;
    }
}

void addSales(SaleHistory a)
{
    /*int index = 0;
    for (int i = 1; i < 100; i++) {
        if (saleHis[i].stt == 0) {
            index = i;
            break;
        }
    }*/
    a.stt = saleHis.size();/*
    saleHis[index].stt = a.stt;
    saleHis[index].saleRep = a.saleRep;
    saleHis[index].client = a.client;
    saleHis[index].prod = a.prod;
    saleHis[index].quantity = a.quantity;
    saleHis[index].date = a.date;
    saleHis[index].total = a.total;*/
    saleHis.push_back(a);
}

void updateSales(int index, SaleHistory a)
{
    if (saleHis.size() <= index || index == 0) {
        cout << "Row number not exist!!" << endl;
    }
    else {
        /*saleHis[index].stt = a.stt;
        saleHis[index].saleRep = a.saleRep;
        saleHis[index].client = a.client;
        saleHis[index].prod = a.prod;
        saleHis[index].quantity = a.quantity;
        saleHis[index].date = a.date;
        saleHis[index].total = a.total;*/
        saleHis[index] = a;
    }
}

SaleHistory getSaleHistory(int i)
{
    SaleHistory a;
    readFileSales("saleshistory.csv");
    if (i < saleHis.size()) {
        a = saleHis.at(i);
    }
    return a;
}

vector<SaleHistory> getListClient(int indexClient)
{
    vector<SaleHistory> sales;
    readFileSales("saleshistory.csv");
    for (int i = 1; i < saleHis.size(); i++) {
        if (saleHis.at(i).client == indexClient) {
            sales.push_back(saleHis.at(i));
        }
    }
    return sales;
}

vector<SaleHistory> getListSaler(int indexSaler)
{
    vector<SaleHistory> sales;
    readFileSales("saleshistory.csv");
    for (int i = 1; i < saleHis.size(); i++) {
        if (saleHis.at(i).saleRep == indexSaler) {
            sales.push_back(saleHis.at(i));
        }
    }
    return sales;
}

vector<SaleHistory> getListProduct(int indexProduct)
{
    vector<SaleHistory> sales;
    readFileSales("saleshistory.csv");
    for (int i = 1; i < saleHis.size(); i++) {
        if (saleHis.at(i).prod == indexProduct) {
            sales.push_back(saleHis.at(i));
        }
    }
    return sales;
}

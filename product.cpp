#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include "VO.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "product.h"
#include "sales.h"

//Product product[100];
vector<Product> product = {};
void explode(Product& product, const string& s, const char& c) {
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
    //stt = 0 in line 1
    if (v.size() == 4) {
        if (v[0] == "Stt" && v[2] == "Quantity" && v[3] == "Active") {
            product.stt = 0;
            product.price = 0;
            product.active = 0;
        }
        else {
            product.stt = atoi(v[0].c_str());
            product.price = atof(v[2].c_str());
            product.active = (bool)atoi(v[3].c_str());
        }
        product.name = v[1];
        
    }
}

void readFileProduct(string fileName)
{
    string line;
    int i = 0;
    product = {};
    ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {

            Product prd;
            explode(prd, line, ','); //get 1 product
            product.push_back(prd); // insert product into vector
            i++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

void writeFileProduct(string fileName)
{
    ofstream ptr;
    ptr.open(fileName);
    int i = 1;
    //add header into file
    ptr << "Stt" << "," << "Name" << "," << "Price" << "," << "Active" << '\n';
    //add vector product into file
    while (i < product.size()) {
        ptr << product[i].stt << "," << product[i].name << "," << product[i].price << "," << product[i].active << '\n';
        cout << "File saved" << endl;
        i++;
    }
}

//list all product
void listAllPrd()
{
    double total;
    for (int i = 1; i < product.size(); i++) {
        //break line 1(tag)
        if (product[i].stt == 0) {
            break;
        }
        else {
            //calculate total sales of each product
            vector<SaleHistory> sales = getListProduct(product.at(i).stt);
            total = 0;
            if (sales.size() > 0) {
                for (int k = 0; k < sales.size(); k++) {
                    if (sales.at(k).total > 0) {
                        total = total + sales.at(k).total;
                    }
                }
            }
            cout << "Stt: " << product[i].stt << " == Name: " << product[i].name << " == Active: " << product[i].active 
                << " == Total: " << total << endl;
        }
    }
}

//view detail product
void viewDetailProduct(int i)
{
    if (i >= product.size() || i == 0) {
        cout << "No row" << endl;
    }
    else {
        cout << "Stt: " << product[i].stt << "\nName: " << product[i].name << "\nPrice: " << product[i].price
            << "\nActive: " << product[i].active << endl;
    }
}


//add product into vector
void addProduct(Product a)
{    
    a.stt = product.size();
    product.push_back(a);
}

//update product
void updateProduct(int index, Product a)
{
    //check product exist
    if (index >= product.size() || index == 0) {
        cout << "Row number not exist!!" << endl;
    }
    else {
        product[index] = a;
    }
}

//get 1 product 
Product getProduct(int i) {

    Product a;
    readFileProduct("product.csv");
    if (i < product.size()) {
        a = product[i];
    }

    return a;
}

//create report month in current year
void reportProduct(int monthInput)
{
    double total;
    int amount, day, month, year;
    //get current of computer system
    time_t t = time(0);
    int yearCrr = (localtime(&t)->tm_year + 1900);
    readFileProduct("product.csv");
    //create table report
    cout << setw(5) << "No." << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(10) << "Total" << endl;
    //calculate total sales of product in month of current year
    for (int i = 1; i < product.size(); i++) {
        vector<SaleHistory> sales = getListProduct(product.at(i).stt);
        total = 0;
        amount = 0;
        if (sales.size() > 0) {
            for (int k = 0; k < sales.size(); k++) {
                sscanf_s(sales.at(k).date.c_str(), "%2d/%2d/%4d", &day, &month, &year); //get each day,month,year
                if (monthInput == month && year == yearCrr) {
                    if (sales.at(k).total > 0) {
                        total = total + sales.at(k).total;
                        amount += sales.at(k).quantity;
                    }
                }                
            }
        }
        cout << setw(5) << product.at(i).stt << setw(20) << product.at(i).name << setw(10) << product.at(i).price 
            << setw(10) << amount << setw(10) << total << endl;
    }
}
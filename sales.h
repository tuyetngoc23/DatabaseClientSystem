#include <string>
#pragma once
void readFileSales(string fileName);
void writeFileSales(string fileName);
void listAllSales();
void viewDetailSales(int i);
void addSales(SaleHistory a);
void updateSales(int index, SaleHistory a);
SaleHistory getSaleHistory(int i);
vector<SaleHistory> getListClient(int indexClient);
vector<SaleHistory> getListSaler(int indexSaler);
vector<SaleHistory> getListProduct(int indexProduct);
#include <string>
#pragma once
void readFileSaler(string fileName);
void writeFileSaler(string fileName);
void listAllSaleRep();
void viewDetailSaleRep(int i);
void addSaleRep(SaleRep a);
void updateSaleRep(int index, SaleRep a);
SaleRep getSaler(int i);
double saleBonus(int year, int i);
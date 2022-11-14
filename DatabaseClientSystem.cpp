// DatabaseClientSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <vector>
#include <sstream>
#include <stdio.h>
#include "VO.cpp"
#include "client.h"
#include "salerep.h"
#include "product.h"
#include "sales.h"
using namespace std;


const int MAX_VALID_YR = 9999;
const int MIN_VALID_YR = 1800;

// Returns true if
// given year is valid.
bool isLeap(int year)
{
    // Return true if year
    // is a multiple of 4 and
    // not multiple of 100.
    // OR year is multiple of 400.
    return (((year % 4 == 0) &&
        (year % 100 != 0)) ||
        (year % 400 == 0));
}

// Returns true if given
// year is valid or not.
bool isValidDate(int d, int m, int y)
{
    // If year, month and day
    // are not in given range
    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    // Handle February month
    // with leap year
    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }

    // Months of April, June,
    // Sept and Nov must have
    // number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}

int main()
{
    cout << "Hello Word" << endl; 
    /*string date;
    cin >> date;
    int day, month, year;
    sscanf_s(date.c_str(), "%2d/%2d/%4d",
        &day,
        &month,
        &year);
    cout << "day: " << day << " month: " << month << " year: " << year << endl;*/
    string sum, ysum, nsum;
    int chooseMenu;
    do {
        cout << "What do you want?" << endl;
        cout << "1.Client\n2.Sale Representatives\n3.Products\n4.Sale History\n";
        cout << "Enter your choose: ";
        cin >> chooseMenu;
        switch (chooseMenu)
        {
        case 1: {
            //client function        
            //khaibao

            int index;
            string y, n;
            int choose;
            Client updateNew, addNew;
            string name, address, phone, email;
            //menu 
            do {
                //open to read file
                readFile("client.csv");
                //list all client
                listAll();
                //choose menu
                cout << "Client:\n1.Show detail\n2.Add client\n3.Update client\n4.Exit" << endl;
                cout << "Please enter number to choose menu: ";
                cin >> choose;
                switch (choose)
                {
                case 1: {
                    //view detail
                    cout << "input row want show detail: ";
                    cin >> index;
                    do {
                        viewDetailClient(index);
                        cout << "Do you want show other client(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                        cout << "Input row number: ";
                    } while (cin >> index);
                } break;
                case 2: {
                    //add new client

                    do {
                        cout << "Input information client: " << endl;
                        cout << "Name: "; cin >> name;
                        cout << "Address: "; cin >> address;
                        cout << "Phone(###-###-####): "; cin >> phone;
                        cout << "Email: "; cin >> email;

                        addNew.name = name;
                        addNew.address = address;
                        addNew.phone = phone;
                        addNew.email = email;

                        addClient(addNew);
                        writeFile("client.csv");
                        cout << "Do you want add more(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (y != "n" || y != "N");
                } break;
                case 3: {
                    //update info            
                    do {
                        cout << "input row want update: ";
                        cin >> index;                      

                        Client a = getClient(index);
                        if (a.stt != 0) {
                            cout << "Input information client: " << endl;
                            cout << "Name: "; cin >> name;
                            cout << "Address: "; cin >> address;
                            cout << "Phone(###-###-####): "; cin >> phone;
                            cout << "Email: "; cin >> email;
                            updateNew.stt = index;
                            updateNew.name = name;
                            updateNew.address = address;
                            updateNew.phone = phone;
                            updateNew.email = email;
                            updateClient(index, updateNew);
                            writeFile("client.csv");
                        }
                        else {
                            cout << "No row" << endl;
                        }                       
                        
                        cout << "Do you want update more(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (y != "n" || y != "N");
                } break;
                default:
                    cout << "Thanks. See you again" << endl;
                    break;
                }
                cout << "Do you want to see client menu(Y/N): ";
                cin >> n;
                if (n == "N" || n == "n") {
                    cout << "Thanks. See you later!!!" << endl;
                    break;
                }
            } while (n != "n" || n != "N");

            //save file
           /* writeFile("client.csv");*/
            //end client func
        } break;
        case 2: {
            //saleRep
            
            //khaibao

            int indexSaler;
            string ySaler, nSaler;
            int chooseSaler, year;
            SaleRep addSaler, updateSaler;
            string nameSaler, addressSaler, phoneSaler, emailSaler;
            //menu 
            do {
                //open to read file
                readFileSaler("salerep.csv");
                //list all Sale Rep
                listAllSaleRep();
                //choose menu
                cout << "SaleRep:\n1.Show detail\n2.Add new\n3.Update Infor\n4.SaleBonus\n5.Exit" << endl;
                cout << "Please enter number to choose menu: ";
                cin >> chooseSaler;
                switch (chooseSaler)
                {
                case 1: {
                    //view detail
                    cout << "input row want show detail: ";
                    cin >> indexSaler;
                    do {
                        viewDetailSaleRep(indexSaler);
                        cout << "Do you want show other client(Y/N): ";
                        cin >> ySaler;
                        if (ySaler == "N" || ySaler == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                        cout << "Input row number: ";
                    } while (cin >> indexSaler);
                } break;
                case 2: {
                    //add new

                    do {
                        cout << "Input information client: " << endl;
                        cout << "Name: "; cin >> nameSaler;
                        cout << "Address: "; cin >> addressSaler;
                        cout << "Phone(###-###-####): "; cin >> phoneSaler;
                        cout << "Email: "; cin >> emailSaler;

                        addSaler.name = nameSaler;
                        addSaler.address = addressSaler;
                        addSaler.phone = phoneSaler;
                        addSaler.email = emailSaler;

                        addSaleRep(addSaler);
                        //save file
                        writeFileSaler("salerep.csv");
                        cout << "Do you want add more(Y/N): ";
                        cin >> ySaler;
                        if (ySaler == "N" || ySaler == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (ySaler != "n" || ySaler != "N");
                } break;
                case 3: {

                    do {
                        //update info
                        cout << "input row want update: ";
                        cin >> indexSaler;
                        

                        SaleRep a = getSaler(indexSaler);
                        if (a.stt != 0) {
                            cout << "Input information client: " << endl;
                            cout << "Name: "; cin >> nameSaler;
                            cout << "Address: "; cin >> addressSaler;
                            cout << "Phone(###-###-####): "; cin >> phoneSaler;
                            cout << "Email: "; cin >> emailSaler;
                            updateSaler.stt = indexSaler;
                            updateSaler.name = nameSaler;
                            updateSaler.address = addressSaler;
                            updateSaler.phone = phoneSaler;
                            updateSaler.email = emailSaler;

                            updateSaleRep(indexSaler, updateSaler);
                            //save file
                            writeFileSaler("salerep.csv");
                        }
                        else {
                            cout << "No row" << endl;
                        }

                        
                        cout << "Do you want update more(Y/N): ";
                        cin >> ySaler;
                        if (ySaler == "N" || ySaler == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (ySaler != "n" || ySaler != "N");
                } break; 
                case 4: {
                    //calculate sale bonus year
                    do {
                        cout << "Choose saler: "; cin >> indexSaler;
                        SaleRep a = getSaler(indexSaler);
                        if (a.stt != 0) {
                            cout << "Input year(yyyy): ";
                            cin >> year;
                            cout << "Sale bonus of " << year << ": " << saleBonus(year, indexSaler) << endl;
                        }
                        else {
                            cout << "No row" << endl;
                        }
                        cout << "Do you want calculate other saler(Y/N): ";
                        cin >> ySaler;
                        if (ySaler == "N" || ySaler == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (ySaler != "n" || ySaler != "N");                        
                }break;
                default:
                    cout << "Thanks. See you again" << endl;
                    break;
                }
                cout << "Do you want to see saler menu(Y/N): ";
                cin >> nSaler;
                if (nSaler == "N" || nSaler == "n") {
                    cout << "Thanks. See you later!!!" << endl;
                    break;
                }
            } while (nSaler != "n" || nSaler != "N");

            
            //end saler func
        } break;
        case 3: {
            //product function        
            //khaibao

            int indexPr;
            string y, n;
            int choose;
            Product updatePr, addPr;
            string namePrd;
            double price;
            bool activePrd;
            //menu 
            do {
                //open to read file
                readFileProduct("product.csv");
                //list all product
                listAllPrd();
                //choose menu
                cout << "Product:\n1.Show detail\n2.Add new\n3.Update product\n4.Report Month\n5.Exit" << endl;
                cout << "Please enter number to choose menu: ";
                cin >> choose;
                switch (choose)
                {
                case 1: {
                    //view detail
                    cout << "input row want show detail: ";
                    cin >> indexPr;
                    do {
                        viewDetailProduct(indexPr);
                        cout << "Do you want show other product(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                        cout << "Input row number: ";
                    } while (cin >> indexPr);
                } break;
                case 2: {
                    //add new product

                    do {
                        cout << "Input information product: " << endl;
                        cout << "Name: "; cin >> namePrd;
                        cout << "Price: "; cin >> price;
                        cout << "Active(1/0): "; cin >> activePrd;

                        addPr.name = namePrd;
                        addPr.price = price;
                        addPr.active = activePrd;

                        addProduct(addPr);
                        writeFileProduct("product.csv");
                        cout << "Do you want add more(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (y != "n" || y != "N");
                } break;
                case 3: {
                    //update info            
                    do {
                        cout << "input row want update: ";
                        cin >> indexPr;
                        //if have product -> update
                        // if not cout: no row
                        Product a = getProduct(indexPr);
                        if (a.stt != 0) {
                            cout << "Input information product: " << endl;
                            cout << "Name: "; cin >> namePrd;
                            cout << "Price: "; cin >> price;
                            cout << "Active(1/0): "; cin >> activePrd;
                            updatePr.stt = indexPr;
                            updatePr.name = namePrd;
                            updatePr.price = price;
                            updatePr.active = activePrd;

                            updateProduct(indexPr, updatePr);
                            writeFileProduct("product.csv");
                        }
                        else {
                            cout << "No row" << endl;
                        }
                        
                        cout << "Do you want update more(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (y != "n" || y != "N");
                } break;
                case 4: {
                    //report month in current year
                    do {
                        cout << "Input month to create report: "; cin >> indexPr;
                        reportProduct(indexPr);

                        cout << "Do you want create other report(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (y != "n" || y != "N");
                    
                } break;
                default:
                    cout << "Thanks. See you again" << endl;
                    break;
                }
                cout << "Do you want to see product menu(Y/N): ";
                cin >> n;
                if (n == "N" || n == "n") {
                    cout << "Thanks. See you later!!!" << endl;
                    break;
                }

            } while (n != "n" || n != "N");
                        
            //end product func
        } break;
        case 4: {
            //sale history function
        
            //khaibao

            int indexSales;
            string y, n;
            int chooseSales;
            SaleHistory update, add;
            string date;
            int quantity,saleRep,client,prod;
            double total=0;
            //menu 
            do {
                //open to read file
                readFileSales("saleshistory.csv");
                //list all product
                listAllSales();
                //choose menu
                cout << "Sale History:\n1.Show detail\n2.Add new\n3.Update sale history\n4.Exit" << endl;
                cout << "Please enter number to choose menu: ";
                cin >> chooseSales;
                switch (chooseSales)
                {
                case 1: {
                    //view detail
                    cout << "input row want show detail: ";
                    cin >> indexSales;
                    do {
                        viewDetailSales(indexSales);
                        cout << "Do you want show other product(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                        cout << "Input row number: ";
                    } while (cin >> indexSales);
                } break;
                case 2: {
                    //add new product

                    do {
                        cout << "Input information sale history: " << endl;
                        //open to read file
                        readFileSaler("salerep.csv");
                        //list all Sale Rep
                        listAllSaleRep();
                        cout << "Sale Representatives(number of stt): "; cin >> saleRep;
                        //open to read file
                        readFile("client.csv");
                        //list all client
                        listAll();
                        cout << "Client(number of stt): "; cin >> client;
                        //open to read file
                        readFileProduct("product.csv");
                        //list all product
                        listAllPrd();
                        cout << "Product(number of stt):"; cin >> prod;
                        cout << "Quantity: "; cin >> quantity;
                        //validate date
                        int day, month, year;
                        do {
                            cout << "Date(dd/mm/yyyy): "; cin >> date;
                            sscanf_s(date.c_str(), "%2d/%2d/%4d",
                                &day,
                                &month,
                                &year);
                            if(isValidDate(day, month, year)){
                                break;
                            }
                            else {
                                cout << "Please enter valid date!!!" << endl;
                            }
                        } while (!isValidDate(day, month, year));
                        

                        add.saleRep = saleRep;
                        add.client = client;
                        add.prod = prod;
                        add.quantity = quantity;
                        add.date = date;

                        //check have product, client, saler
                        //if total > 0 -> valid
                        // total = 0 -> invalid
                        Product prd = getProduct(prod);
                        Client cl = getClient(client);
                        SaleRep sr = getSaler(saleRep);
                        total = prd.price * double_t(quantity);
                        if (total > 0 && cl.stt != 0 && sr.stt != 0) {
                            add.total = total;
                        }
                        else {
                            add.total = 0;
                        }


                        addSales(add);
                        //save file
                        writeFileSales("saleshistory.csv");
                        cout << "Do you want add more(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (y != "n" || y != "N");
                } break;
                case 3: {
                    //update info            
                    do {
                        cout << "input row want update: ";
                        cin >> indexSales;
                        SaleHistory a = getSaleHistory(indexSales);
                        if (a.stt != 0) {
                            cout << "Input information product: " << endl;
                            //open to read file
                            readFileSaler("salerep.csv");
                            //list all Sale Rep
                            listAllSaleRep();
                            cout << "Sale Representatives(number of stt): "; cin >> saleRep;
                            //open to read file
                            readFile("client.csv");
                            //list all client
                            listAll();
                            cout << "Client(number of stt): "; cin >> client;
                            //open to read file
                            readFileProduct("product.csv");
                            //list all product
                            listAllPrd();
                            cout << "Product(number of stt):"; cin >> prod;
                            cout << "Quantity: "; cin >> quantity;
                            //validate date
                            int day, month, year;
                            do {
                                cout << "Date(dd/mm/yyyy): "; cin >> date;
                                sscanf_s(date.c_str(), "%2d/%2d/%4d",
                                    &day,
                                    &month,
                                    &year);
                                if (isValidDate(day, month, year)) {
                                    break;
                                }
                                else {
                                    cout << "Please enter valid date!!!" << endl;
                                }
                            } while (!isValidDate(day, month, year));
                            
                            update.stt = indexSales;
                            update.saleRep = saleRep;
                            update.client = client;
                            update.prod = prod;
                            update.quantity = quantity;
                            update.date = date;

                            //check have product, client, saler
                            //if total > 0 -> valid
                            // total = 0 -> invalid
                            Product prd = getProduct(prod);
                            Client cl = getClient(client);
                            SaleRep sr = getSaler(saleRep);
                            total = prd.price * double_t(quantity);
                            if (total > 0 && cl.stt != 0 && sr.stt != 0) {
                                update.total = total;
                            }
                            else {
                                update.total = 0;
                            }

                            updateSales(indexSales, update);
                            //save file
                            writeFileSales("saleshistory.csv");
                        }
                        else {
                            cout << "No row" << endl;
                        }

                        cout << "Do you want update more(Y/N): ";
                        cin >> y;
                        if (y == "N" || y == "n") {
                            cout << "Bye. See you again" << endl;
                            break;
                        }
                    } while (y != "n" || y != "N");
                } break;
                default:
                    cout << "Thanks. See you again" << endl;
                    break;
                }
                cout << "Do you want to see sale history menu(Y/N): ";
                cin >> n;
                if (n == "N" || n == "n") {
                    cout << "Thanks. See you later!!!" << endl;
                    break;
                }

            } while (n != "n" || n != "N");

            
            //end sale history func
        } break;
        default:
            break;
        }
        cout << "Do you want to choose orther menu(Y/N): ";
        cin >> ysum;
        if (ysum == "N" || ysum == "n") {
            cout << "Thanks. See you later!!!" << endl;
            break;
        }
    } while (ysum != "n" || ysum != "N");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#pragma once
#ifndef PART_h
#define PART_h
#include <iostream>
#include <string>
using namespace std;


class Part {
private:
    int SKU;
    string Description;
    double Price;
    string UOM;
    int quantityOnHand;
    int leadTime;
public:
    //Constructor
    Part();
    Part(int sku, string description, double price, string uom, int qoh);        //Returns stock keeping number with description
    int getSKU();
    string getPartInfo();                               //getters and setters
    double getPrice() { return Price; }
    void setLeadTime(int lt) { leadTime = lt; }         //Checks if quantity on hand is greater than 0
    bool inStock();                                     //Accepts a date and checks if the item is in stock or if the date is greater than lead time. 
    bool Available(int month, int day);
    void Display();

    bool operator == (const Part&);
    bool operator < (const Part&);
    bool operator > (const Part&);

};


#endif

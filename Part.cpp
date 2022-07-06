#include "Part.h"
#include <iostream>
using namespace std;

Part::Part() {
    SKU = 0;
    Description = "";
    Price = 0;
    UOM = "";
    quantityOnHand = 0;
}

Part::Part(int sku, string description, double price, string uom, int qoh = 0) {
    SKU = sku;
    Description = description;
    Price = price;
    UOM = uom;
    quantityOnHand = qoh;
}

int Part::getSKU() {
    return SKU;
}

string Part::getPartInfo() {
    string retWord;
    retWord += to_string(SKU);
    retWord += " : ";
    retWord += Description;
    return retWord;
}

bool Part::inStock() {
    return quantityOnHand > 0;
}

bool Part::Available(int month, int day) {
    if (inStock()) {
        return true;
    }
    else {
        //get current date from user
        int currMonth;
        int currDay;
        cout << "Enter the current month as a digit" << endl;
        cin >> currMonth;
        while (currMonth < 1 || currMonth > 12) {
            cout << "Invalid, enter the current month as a digit" << endl;
            cin >> currMonth;
        }

        cout << "Enter the current day of the month" << endl;
        cin >> currDay;
        while (currDay < 1 || currDay > 30) {
            cout << "Invalid, enter the current day of the month" << endl;
            cin >> currDay;
        }

        //Initialize shipping dates
        int shipMonth = currMonth;
        int shipDay = currDay;

        //Adding shipping time to current date
        if ((currDay + leadTime) > 30) {
            shipMonth += 1;
            shipDay = (currDay + leadTime) - 30;
        }
        else {
            shipDay = currDay + leadTime;
        }

        //Compare shipping date to desired dates
        if (shipMonth > month) {
            return false;
        }
        else if (shipMonth < month) {
            return true;
        }
        else if (shipMonth == month) {
            if (shipDay < day) {
                return false;
            }
            else {
                return true;
            }
        }
    }
}

void Part::Display() {
    cout << "============================" << endl;
    cout << "SKU: " << SKU << endl;
    cout << "Description : " << Description << endl;
    cout << "Price : $" << Price << endl;
    cout << "Quantity: " << quantityOnHand << endl;
    cout << "============================" << endl;
}

bool Part::operator == (const Part& item) {
    return this->SKU == item.SKU;
}
bool Part::operator < (const Part& item) {
    return this->SKU < item.SKU;
}
bool Part::operator > (const Part& item) {
    return this->SKU > item.SKU;
}
#include <iostream>
#include "DoubleLinked.h"
#include <string>
#include "Part.h"
using namespace std;

Part* partSetup() {
	int SKU;
	string Description;
	double Price;
	string UOM;
	int QOH;

	cout << "Enter the SKU (as an integer):" << endl;
	cin >> SKU;

	cout << "Enter the Description:" << endl;
	cin.ignore();
	getline(cin, Description);

	cout << "Enter Price (as a double):" << endl;
	cin >> Price;

	cout << "Enter Unit of Measure:" << endl;
	cin >> UOM;

	cout << "Enter Quantity on hand (int):" << endl;
	cin >> QOH;

	Part* myPart = new Part(SKU, Description, Price, UOM, QOH);
	return myPart;
}

int main() {
	DoubleLinked<Part> Partlist;
	int sel = 0;
	bool quit = false;

	do {
		do {
			cout << "Main Menu:" << endl
				<< "\t 1 - Add Item" << endl
				<< "\t 2 - Get Item" << endl
				<< "\t 3 - IsInList" << endl
				<< "\t 4 - IsEmpty" << endl
				<< "\t 5 - Size" << endl
				<< "\t 6 - See At" << endl
				<< "\t 7 - See Prev" << endl
				<< "\t 8 - See Next" << endl
				<< "\t 9 - Reset" << endl
				<< "\t 10 - Display List" << endl
				<< "\t 11 - Quit" << endl;

			cout << "Enter your selection: " << endl;
			cin >> sel;
		} while ((sel < 1 || sel > 11));

		if (sel == 1) {
			try {
				Partlist.AddItem(partSetup());
			}
			catch (Exception e) {
				e.printError();
			}
			cout << "--Successfully added item.--" << endl;
		}
		else if (sel == 2) {					// Issues with selections 2 and 3
			int sku;
			bool found = false;
			cout << "Enter SKU Number: " << endl;
			cin >> sku;
			Part* removePart = new Part();
			try {
				for (int i = 0; i < Partlist.Size(); ++i) {
					if (Partlist.SeeAt(i)->getSKU() == sku) {
						removePart = Partlist.SeeAt(i);
						//cout << Partlist.SeeAt(i) << endl;
						Partlist.GetItem(removePart);
						found = true;
						cout << "Got this item: " << removePart->getPartInfo() << endl;
					}
					else if (i == Partlist.Size() - 1) {
						cout << "Item not found" << endl;
					}
				}
				if (Partlist.Size() == 0 && !found) {
					cout << "List is empty" << endl;
				}
				else if (!found) {
					cout << "Item not found" << endl;
				}
			}
			catch (Exception e) {
				e.printError();
			}
		}
		else if (sel == 3) {
			int sku;
			cout << "Enter SKU Number: " << endl;
			cin >> sku;
			Part* checkPart = new Part();
			try {
				for (int i = 0; i < Partlist.Size(); ++i) {
					if (Partlist.SeeAt(i)->getSKU() == sku) {
						checkPart = Partlist.SeeAt(i);
					}
				}
				if (Partlist.IsInList(checkPart)) {
					cout << "This part is in the list." << endl;
				}
				else {
					cout << "This part is not in the list." << endl;
				}
			}
			catch (Exception e) {
				e.printError();
			}
		}
		else if (sel == 4) {
			if (Partlist.IsEmpty()) {
				cout << "The list is empty." << endl;
			}
			else {
				cout << "The list is not empty." << endl;
			}
		}
		else if (sel == 5) {
			cout << "The size of the list is: " << Partlist.Size() << endl;
		}
		else if (sel == 6) {
			int pos;
			cout << "Enter the postion you would like to view: " << endl;
			cin >> pos;
			Part* seePart = new Part();
			seePart = Partlist.SeeAt(pos);
			cout << "Item at position " << pos << " is: " << seePart->getPartInfo() << endl;
			//delete seePart;
		}
		else if (sel == 7) {
			Part* seePart = new Part();
			seePart = Partlist.SeePrev();
			cout << "The previous item in the list is: " << seePart->getPartInfo() << endl;
			//delete seePart;
		}
		else if (sel == 8) {
			Part* seePart = new Part();
			seePart = Partlist.SeeNext();
			cout << "The next item in the list is: " << seePart->getPartInfo() << endl;
			//delete seePart;
		}
		else if (sel == 9) {
			cout << "Resetting the view position to 0." << endl;
			Partlist.Reset();
		}
		else if (sel == 10) {
			cout << "Displaying list..." << endl;
			Partlist.DisplayList();
		}
		else if (sel == 11) {
			Partlist.~DoubleLinked();
			cout << "Quitting..." << endl;
			quit = true;
			break;
		}

	} while (/*(sel < 1 || sel > 10) &&*/ !quit);

}
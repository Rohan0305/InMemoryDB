#include <iostream>
#include <string>
#include "InMemoryDB.h"
#include <limits>

using namespace std;

int main() {
    InMemoryDB db;

    while (true) {
        int option;

        cout << "Choose following menu options: " << endl;
        cout << "------------------------------" << endl;
        cout << "1 - Begin" << endl;
        cout << "2 - Put" << endl;
        cout << "3 - Commit" << endl;
        cout << "4 - Get" << endl;
        cout << "5 - Rollback" << endl;
        cout << "6 - Exit" << endl;
        cout << "Option (Please enter a number between 1 and 6): ";

        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << endl;
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            cout << endl << endl;
            continue;
        }
        
        if (option < 1 || option > 6) {
            cout << endl;
            cout << "Invalid option. Please enter a number between 1 and 6." << endl;
            cout << endl << endl;
            continue;
        }

        try {
            if (option == 1) {
                db.begin_transaction();
                cout << endl;
                cout << "Transaction started." << endl;
            } else if (option == 2) {
                cout << endl;
                string key;
                int val;

                cout << "Key: ";
                cin >> key;

                cout << "Value: ";
                cin >> val;

                db.put(key, val);
                cout << "Key-Value added - Commit to save." << endl;
            } else if (option == 3) {
                db.commit();
                cout << endl;
                cout << "Transaction committed." << endl;
            } else if (option == 4) {
                string key;
                cout << endl;
                cout << "Enter key to retrieve value: ";
                cin >> key;

                auto result = db.get(key);
                if (result.has_value()) {
                    cout << "Value: " << result.value() << endl;
                } else {
                    cout << "Key not found." << endl;
                }
            } else if (option == 5) {
                db.rollback();
                cout << endl;
                cout << "Transaction rolled back." << endl;
            } else if (option == 6) {
                cout << endl;
                cout << "Program exited." << endl;
                break;
            }
        } catch (const exception& e) {
            cout << endl;
            cout << "Error: " << e.what() << endl;
        }

        cout << endl << endl;
    }

    return 0;
}

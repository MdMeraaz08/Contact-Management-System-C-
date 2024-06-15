#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For system()
using namespace std;

// Function prototypes
bool check_digits(const string &);
bool check_numbers(const string &);
void addContact();
void searchContact();
void help();
void self_exit();

// Global variables
string fname, lname, phone_num;

int main() {
    short int choice;
    while (true) {
        system("cls");
        system("color 0A");
        cout << "\n\n\n\t\t\tContact Management.";
        cout << "\n\n\t1. Add Contact\n\t2. Search Contact\n\t3. Help\n\t4. Exit\n\t> ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    addContact();
                    break;
                case 2:
                    searchContact();
                    break;
                case 3:
                    help();
                    break;
                case 4:
                    self_exit();
                    return 0;
                default:
                    throw runtime_error("Invalid Input!");
            }
        } catch (const exception &ex) {
            cerr << "\n\n\tException: " << ex.what();
            cerr << "\n\tPress Any Key To Continue...";
            cin.ignore().get(); // Pause and wait for any key
        }
    }
    return 0;
}

void self_exit() {
    system("cls");
    cout << "\n\n\n\t\tThank You For Using!";
    exit(0);
}

void help() {
    system("cls");
    cout << "\n\n\tContact Management System Help:";
    cout << "\n\t1. Add Contact: Allows you to add a new contact with first name, last name, and phone number.";
    cout << "\n\t2. Search Contact: Allows you to search for an existing contact by name.";
    cout << "\n\t3. Help: Displays this help message.";
    cout << "\n\t4. Exit: Exits the program.";
    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore().get(); // Pause and wait for any key
}

void addContact() {
    ofstream phone("number.txt", ios::app);
    system("cls");
    cout << "\n\n\tEnter First Name: ";
    cin >> fname;
    cout << "\n\tEnter Last Name: ";
    cin >> lname;
    cout << "\n\tEnter 10-Digit Phone Number: ";
    cin >> phone_num;

    if (!check_digits(phone_num) || !check_numbers(phone_num)) {
        throw invalid_argument("Invalid Phone Number. A Phone Number Must Contain 10 Digits and Only Numbers.");
    }

    if (!phone.is_open()) {
        throw runtime_error("Error Opening File!");
    }

    phone << fname << " " << lname << " " << phone_num << endl;
    cout << "\n\tContact Saved Successfully!";
    phone.close();
    cout << "\n\tPress any key to return to the main menu...";
    cin.ignore().get(); // Pause and wait for any key
}

void searchContact() {
    ifstream myfile("number.txt");
    if (!myfile.is_open()) {
        throw runtime_error("Error Opening File!");
    }

    bool found = false;
    string keyword;
    system("cls");
    cout << "\n\tEnter Name To Search: ";
    cin >> keyword;

    while (myfile >> fname >> lname >> phone_num) {
        if (keyword == fname || keyword == lname) {
            system("cls");
            cout << "\n\n\n\t\tContact Details:";
            cout << "\n\n\tFirst Name: " << fname;
            cout << "\n\tLast Name: " << lname;
            cout << "\n\tPhone Number: " << phone_num;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n\tNo Such Contact Found";
    }
    myfile.close();
    cout << "\n\tPress any key to return to the main menu...";
    cin.ignore().get(); // Pause and wait for any key
}

bool check_digits(const string &x) {
    return x.length() == 10;
}

bool check_numbers(const string &x) {
    return all_of(x.begin(), x.end(), ::isdigit);
}

#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
#include <iomanip>

using namespace std;

//Class Definition

class Store {
private:
    static int storage_count;
    string name;
    double avg;
    bool exist;

public:
    Store();

    Store(string, double);

    ~Store();

    void setName(const string value);

    void setAvg(const double value);

    string getName() const;

    double getAvg() const;

    bool getExist() const;

    static int get_available_objects();

    bool add_information(const string, const double);

    bool remove_information();

    void show_info() const;

    friend int get_available_items(Store[], int);
};

int Store::storage_count = 0;

Store::Store() {
    storage_count++;
    name = "";
    avg = 0;
    exist = false;
}

Store::Store(string n, double Avg) {
    storage_count++;
    name = n;
    avg = Avg;
    exist = true;
}

Store::~Store() {
    storage_count--;
}

void Store::setName(const string value) { name = value; }

void Store::setAvg(const double value) { avg = value; }

string Store::getName() const { return name; }

double Store::getAvg() const { return avg; }

bool Store::getExist() const { return exist; }

int Store::get_available_objects() { return storage_count; }

void Store::show_info() const {
    if (exist)
        cout << endl << "\t Item Name: " << name << endl
             << fixed << showpoint << setprecision(2)
             << "\t Average: " << avg << endl
             << "\t------------------------" << endl;
}

bool Store::add_information(const std::string value, const double double_value) {
    if (!exist) {
        name = value;
        avg = double_value;
        exist = true;
        return true;
    } else {
        return false;
    }
}

bool Store::remove_information() {
    if (exist) {
        exist = false;
        return true;
    } else {
        return false;
    }
}

//Menus and SubMenus
int mainMenu();

int searchMenu();

int sortMenu();

int findSlot(const Store[], const int);

int search_by_name(const Store[], const int, const string);

void search_by_average(const Store[], const int, const double);

void sort_by_name(Store[], const int);

void sort_by_average(Store[], const int);

//Driver
int main() {
    int listSize = 10;
    Store list[listSize];
    int index = 0;

    string temp_str;
    double temp_avg;

    while (true) {
        switch (mainMenu()) {
            case 1: {
                index = findSlot(list, listSize);
                if (index >= 0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\tEnter Item's Name: ";
                    getline(cin, temp_str);
                    cout << "\tEnter Item's Average: ";
                    cin >> temp_avg;
                    if (list[index].add_information(temp_str, temp_avg)) {
                        cout << endl << "\t Record Add Successfully";
                    } else {
                        cout << endl << "\t Record Add Failurefully";
                    }
                }
            }
                break;
            case 2: {

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\t Enter Your Item's Name: ";
                getline(cin, temp_str);
                index = search_by_name(list, listSize, temp_str);
                if (index >= 0) {
                    if (list[index].remove_information()) {
                        cout << "\t Record Remove Successfully";
                    } else {
                        cout << endl << "\t Record Remove Failurefully";
                    }
                } else {
                    cout << endl << "\tRecord Not Found ! ";
                }
            }
                break;
            case 3: {
                switch (searchMenu()) {
                    case 1: {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << " Enter Student Name to Search : ";
                        getline(cin, temp_str);
                        index = search_by_name(list, listSize, temp_str);
                        list[index].show_info();
                    }
                        break;

                    case 2: {
                        cout << " Enter Student Average to Search : ";
                        cin >> temp_avg;
                        search_by_average(list, listSize, temp_avg);
                    }
                        break;

                    case 3: {
                        continue;
                    }

                }
            }
                break;

            case 4: {
                switch (sortMenu()) {
                    case 1: {
                        sort_by_name(list, listSize);
                    }
                        break;

                    case 2: {
                        sort_by_average(list, listSize);
                    }
                        break;

                    case 3: {
                        continue;
                    }
                }
            }
                break;

            case 5: {
                for (int i = 0; i < listSize; i++)
                    list[i].show_info();
            }
                break;

            case 6: {
                cout << "\t Alive Objects Using Static Member : "
                     << list[0].get_available_objects() << endl;
            }
                break;

            case 7: {
                cout << "\t Available Students : "
                     << get_available_items(list, listSize) << endl;
            }
                break;

            case 8: {
                exit(1); // exit program with code 1
            }
                break;

            default:
                cout << " Wrong Entry, please try again" << endl;


        }
        Sleep(5000);

    }


    return 0;
}


//-----------------Functions-----------------
int mainMenu() {
    int choice;
    system("cls");
    cout << endl << "  Welcome "
         << endl << "   [ 1 ] : Add New Student . "
         << endl << "   [ 2 ] : Remove Student . "
         << endl << "   [ 3 ] : Search for Student ."
         << endl << "   [ 4 ] : Sort Student List ."
         << endl << "   [ 5 ] : Show Student List Information ."
         << endl << "   [ 6 ] : Alive Objects Count ."
         << endl << "   [ 7 ] : Available Students Objects Count ."
         << endl << "   [ 8 ] : Exit ."
         << endl << "  Enter your menu number->   ";
    cin >> choice;
    return choice;
}

int searchMenu() {
    int choice;
    system("cls");
    cout << endl << " Note : all similar information will display ! "
         << endl << "   [ 1 ] : Search By Name ."
         << endl << "   [ 2 ] : Search By Average ."
         << endl << "   [ 3 ] : Back ."
         << endl << "  Enter your menu number->   ";
    cin >> choice;
    return choice;
}

int sortMenu() {
    int choice;
    system("cls");
    cout << endl << "   [ 1 ] : Sort By Name ."
         << endl << "   [ 2 ] : Sort By Average ."
         << endl << "   [ 3 ] : Back ."
         << endl << "  Enter your menu number->    ";
    cin >> choice;
    return choice;
}

int findSlot(const Store list[], const int listSize) {
    for (int i = 0; i < listSize; i++)
        if (!list[i].getExist())
            return i;
    return -1;
}

int search_by_name(const Store list[], const int listSize, const string str) {
    for (int i = 0; i < listSize; i++)
        if (list[i].getName() == str)
            return i;
    return -1;
}

void search_by_average(const Store list[], const int listSize, const double num) {
    for (int i = 0; i < listSize; i++)
        if (list[i].getAvg() == num)
            list[i].show_info();
}

void sort_by_name(Store list[], const int listSize) {
    for (int i = 0; i < listSize; i++) {
        for (int j = 0; j < listSize - i - 1; j++) {
            if (list[j].getName() > list[j + 1].getName()) {
                Store temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }


        }
    }
}

void sort_by_average(Store list[], const int listSize) {
    for (int i = 0; i < listSize; i++) {
        for (int j = 0; j < listSize - i - 1; j++) {
            if (list[j].getAvg() > list[j + 1].getAvg()) {
                Store temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }

        }
    }
}

int get_available_items(Store list[], int list_size) {
    int count = 0;
    for (int i = 0; i < list_size; i++)
        if (list[i].exist)
            count++;
    return count;
}
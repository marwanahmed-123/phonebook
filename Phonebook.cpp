#include <iostream>

using namespace std;

class PhoneBook
{
    string* names;
    string* phones;
    int phoneBookSize;
public:
    void setSize(int);                  //1
    bool addEntry(string ,string);      //2
    bool displayEntryAtIndex(int);      //3
    void displayEntryAtIndices(int*);   //4
    void displayAll();                  //5
    int* findByName(string);            //6
    string findByPhone(string);         //7
    bool updateNameAt(string, int);     //8
    bool updatePhoneAt(string, int);    //9
    void copyPB(const PhoneBook&);      //10
    void clear();                       //11
};

bool validatePhoneNumber(string);



int main() {
    PhoneBook Test;
    int size;
    cout<<"enter the size of the phone book: ";
    cin>>size;

    Test.setSize(size);

    for (int i = 0; i < size; i++) {
        string phone, name;
        bool validPhone;
        cout << "Enter name " << i + 1 << ": ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter phone " << i + 1 << ": ";
        cin >> phone;
        validPhone = Test.addEntry(name,phone);
        while (!validPhone){
            cout << "Invalid number, renter phone: " << i + 1 << " :";
            cin >> phone;
            validPhone = Test.addEntry(name,phone);
        }
    }


    int choice;
    string input;
    int inNum;
    bool flag;
    PhoneBook PB2;
    bool inLoop = true;

    while (inLoop) {
        cout << "Enter your choice: " << endl
                << "1- Display all phone book" << endl
                << "2- Search for entry/entries by name" << endl
                << "3- Search for entry/entries by phone" << endl
                << "4- Find an entry by index" << endl
                << "5- Update name by index" << endl
                << "6- Update phone by index" << endl
                << "7- Copy phone book to another and display entries of the new phone book" << endl
                << "8- Exit" << endl;

        cin >> choice;

        switch (choice) {
            case 1:
                Test.displayAll();
                break;
            case 2:
                cout << "Enter the name to search for: " << endl;
                cin.ignore();
                getline(cin, input);
                Test.displayEntryAtIndices(Test.findByName(input));
                break;
            case 3:
                cout << "Enter the phone number to search for: " << endl;
                cin >> input;
                cout << Test.findByPhone(input) << endl << endl;
                break;
            case 4:
                cout << "Enter Index: " << endl;
                cin >> inNum;
                flag = Test.displayEntryAtIndex(inNum);
                if (!flag) cout << "Index out of range, try again next time." << endl;
                break;
            case 5:
                cout << "Enter the index you wish to change: ";
                cin >> inNum;
                cout << "Enter the new name: ";
                cin.ignore();
                getline(cin, input);
                flag = Test.updateNameAt(input, inNum);
                if (!flag) cout << "Index out of range, try again next time." << endl << endl;
                break;
            case 6:
                cout << "Enter the index you wish to change: ";
                cin >> inNum;
                cout << "Enter the new phone number: ";
                cin >> input;
                flag = Test.updatePhoneAt(input, inNum);
                if (!flag) cout << "Index out of range/Invalid phone number." << endl;
                break;
            case 7:
                PB2.copyPB(Test);
                PB2.displayAll();
                break;
            case 8:
                inLoop = false;
                Test.clear();
                exit(0);
        }
    }
}

bool validatePhoneNumber(string phone){
    bool valid=true;
    if (phone.length()==11){
        for (int i = 0; i < 11; i++){
            if (isdigit(phone[i])){
                continue;
            }
            else{
                valid=false;
                break;
            }
        }
    }
    else{
        valid=false;
    }
    return valid;
}

void PhoneBook::setSize(int size){
    phoneBookSize=size;
    names = new string[phoneBookSize];
    phones = new string[phoneBookSize];
}
bool PhoneBook::addEntry(string name, string phone){
    static int callCount=0;
    if (validatePhoneNumber(phone)) {
        names[callCount] = name;
        phones[callCount] = phone;
        callCount++;
        return true;
    }
    else return false;
}
bool PhoneBook::displayEntryAtIndex(int index){
    if (index>=0 && index < phoneBookSize)
    {
        cout<< names[index] <<" "<< phones[index] << endl << endl;
        return true;
    }
    return false;
}
void PhoneBook::displayEntryAtIndices(int* indec){
    for (int i = 0; i < phoneBookSize; i++)
    {
        if (indec[i]==1)
        {
            cout<<names[i]<<" "<<phones[i] << endl;
        }
    }
    cout << endl;
}
void PhoneBook::displayAll(){
    for (int i = 0; i < phoneBookSize; i++)
    {
        cout<<names[i]<<" "<<phones[i]<<endl;
    }
    cout << endl;
}

int* PhoneBook::findByName(string search) {
    int *arr;
    arr = new int [phoneBookSize];
    bool match;
    for (int i=0; i<phoneBookSize; i++){
        match = true;
        for (int j=0; j<search.length(); j++){
            if (names[i][j] != search[j]){
                match = false; break;
            }
        }
        if (match) {
            arr[i] = 1;
        }
        else arr[i] = 0;
    }
    return arr;
}
string PhoneBook::findByPhone(string search){
    for (int i=0; i<phoneBookSize; i++)
        if (phones[i] == search)
            return names[i];
    return "";
}
bool PhoneBook::updateNameAt(string newName, int index){
    if (index >= 0 && index < phoneBookSize){
        names[index] = newName;
        return true;
    }
    else return false;
}
bool PhoneBook::updatePhoneAt(string newNum, int index){
    if (!validatePhoneNumber(newNum)) return false;
    if (index >= 0 && index < phoneBookSize){
        phones[index] = newNum;
        return true;
    }
    else return false;
} // Given number must already be checked if 11 digits
void PhoneBook::copyPB(const PhoneBook& right){
    phoneBookSize = right.phoneBookSize;

    names = new string [phoneBookSize];
    phones = new string [phoneBookSize];

    for (int i=0; i<phoneBookSize; i++){
        names[i] = right.names[i];
        phones[i] = right.phones[i];
    }
}
void PhoneBook::clear() {
    delete [] names;
    delete [] phones;
}

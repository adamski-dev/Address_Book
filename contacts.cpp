#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <windows.h>
#include "contacts.h"
#include "user.h"

using namespace std;

void Addressed::import_list_of_contacts (vector <Addressed> & contacts, int logged_user)
{
    fstream file;
    file.open("object_contacts.txt",ios::in);
    if (!file.good())
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << "There are no contacts in the address book. Add new contact, " << endl;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),15);
        Sleep(1500);
    }
    string line;
    char mark = '|';
    int text_nr = 1;
    Addressed contact_from_file;
    while (getline(file, line, mark))
    {
            switch (text_nr)
            {
            case 1: contact_from_file.contact_id = atoi(line.c_str()); break;
            case 2: contact_from_file.id = atoi(line.c_str()); break;
            case 3: contact_from_file.name = line; break;
            case 4: contact_from_file.surname = line; break;
            case 5: contact_from_file.address = line; break;
            case 6: contact_from_file.email_address = line; break;
            case 7: contact_from_file.phone_number = line;
                if (contact_from_file.id == logged_user) {contacts.push_back(contact_from_file);}
                break;
            }
            if (text_nr == 7) {text_nr = 0;}
            text_nr ++;
    }
    file.close();
}
void Addressed::add_new_contact (vector<Addressed> & contacts, int logged_user)
{
    Addressed new_contact;
    string name, surname;
    cout << "Type in first name: ";
    cin >> name;
    cout << "Type in surname: ";
    cin >> surname;
    new_contact.name = convert_first_letter_to_capital (name);
    new_contact.surname = convert_first_letter_to_capital (surname);
    cout << "Type in an address: ";
    cin.sync();
    getline (cin, new_contact.address);
    cout << "Type in an email address: ";
    cin >> new_contact.email_address;
    cout << "Type in a phone number: ";
    cin >> new_contact.phone_number;
    if (get_last_contact_id() == 0) new_contact.contact_id = 1;
    else {new_contact.contact_id = get_last_contact_id() + 1;}
    new_contact.id = logged_user;
    contacts.push_back(new_contact);
    fstream file;
    file.open ("object_contacts.txt",ios::out | ios::app);
    file << new_contact.contact_id             <<"|";
    file << new_contact.id                     <<"|";
    file << new_contact.name                   <<"|";
    file << new_contact.surname                <<"|";
    file << new_contact.address                <<"|";
    file << new_contact.email_address          <<"|";
    file << new_contact.phone_number           <<"|" <<endl;
    file.close();
}
int Addressed::get_last_contact_id ()
{
    fstream file;
    file.open("object_contacts.txt",ios::in);
    if (!file.good()) return 0;
    string line, new_line, text;
    while (getline(file, line)) new_line = line;
    file.close();
    size_t position;
    position = new_line.find('|');
    for (int i=0; i< position; i++) text += new_line[i];
    int last_contact_id = string_to_int_convert (text);
    return last_contact_id;
}
void Addressed::find_contact_by_first_name (vector <Addressed> & contacts)
{
    string name;
    cout << endl << "Please type in the first name of contact you are looking for: ";
    cin >> name;
    name = convert_first_letter_to_capital (name);
    int number_of_case = 0;

    for (vector<Addressed>:: iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        if (it -> name == name) {display_content(*it); number_of_case ++;}
    }
    if (number_of_case == 0) cout << "There are no contacts of that first name in the address book, " << endl;
    system("pause");
}
void Addressed::display_content (Addressed content)
{
        cout << content.contact_id      << "|";
        cout << content.id              << "|";
        cout << content.name            << "|";
        cout << content.surname         << "|";
        cout << content.address         << "|";
        cout << content.email_address   << "|";
        cout << content.phone_number    << "|" << endl;
}
void Addressed::find_contact_by_surname (vector <Addressed> & contacts)
{
    string surname;
    cout << endl << "Please type in the surname of contact you are looking for: ";
    cin >> surname;
    surname = convert_first_letter_to_capital (surname);
    int number_of_case = 0;

    for (vector<Addressed>:: iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        if (it -> surname == surname) {display_content(*it); number_of_case ++;}
    }
    if (number_of_case == 0) cout << "There are no contacts of that surname in the address book, " << endl;
    system("pause");
}
void Addressed::display_all_contacts (vector<Addressed> & contacts)
{
    int number_of_case = 0;
    for (vector<Addressed>:: iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
        display_content (*it);
        number_of_case ++;
    }
    if (number_of_case !=0 ) system("pause");
    if (number_of_case == 0)
    {
        cout << "No contacts saved in your address book. Add new contact," << endl;
        system("pause");
    }
}
void Addressed::delete_contact (vector <Addressed> & contacts)
{
    int id;
    int number_of_case = 0;
    cout << endl << "Please type an id number of contact you would like to delete: ";
    cin >> id;

    for (int i=0; i<contacts.size(); i++)
    {
        if (contacts[i].contact_id == id)
        {
            cout<<endl<< "Press the letter y on the keyboard in order to delete: "<<endl;
            number_of_case ++;
            char select;
            cin >> select;
                if (select == 'y' || select == 'Y')
                {
                    contacts.erase(contacts.begin() + i);
                    cout << "Contact has been deleted from the address book...";
                    Sleep(1000);
                    delete_contact_from_file(id);
                }
                else
                {
                    cout << "You didn't press the letter y - the address book remains unchanged.";
                    Sleep(2000);
                }
        }
    }
    if (number_of_case == 0) cout << "There are no contacts of that id number in the address book," << endl;
    Sleep(2000);
}
void Addressed::delete_contact_from_file (int id)
{
    fstream file;
    fstream temp_file;
    file.open("object_contacts.txt",ios::in);
    string line;
    int contact_id;
    while (getline(file, line))
    {
        string text;
        size_t position = line.find('|');
        for (int i=0; i<position; i++) text+= line[i];
        contact_id = string_to_int_convert (text);
        if (contact_id != id)
        {
            temp_file.open ("temp.txt",ios::out | ios::app);
            temp_file << line << endl;
            temp_file.close();
        }
    }
    file.close();
    remove("object_contacts.txt");
    rename("temp.txt","object_contacts.txt");
}
void Addressed::edit_contact (vector <Addressed> & contacts)
{
    int id;
    cout << endl << "Please type an id number of contact you would like to edit: ";
    cin >> id;
    int number_of_case = 0;
    for (vector<Addressed>::iterator it = contacts.begin(); it != contacts.end(); it++)
    {
        if (it->contact_id == id)
        {
            display_edit_menu();
            number_of_case ++;
            cout<<endl<< "Select from the above menu what you would like to edit: ";
            char select;
            cin >> select;
            string new_data;
            switch (select)
            {
            case '1': cout << "Type in new first name: ";
                      cin >> new_data;
                      new_data = convert_first_letter_to_capital (new_data);
                      it -> name = new_data; break;
            case '2': cout << "Type in new surname: ";
                      cin >> new_data;
                      new_data = convert_first_letter_to_capital (new_data);
                      it -> surname = new_data; break;
            case '3': cout << "Type in new address: ";
                      cin.sync(); getline (cin, new_data);
                      it -> address = new_data; break;
            case '4': cout << "Type in new email address: ";
                      cin >> new_data;
                      it -> email_address = new_data; break;
            case '5': cout << "Type in new phone number: ";
                      cin >> new_data;
                      it -> phone_number = new_data; break;
            case '6': break;
            }
            if (select !='6') update_contact_in_file (*it, id);
        }
    }
    if (number_of_case == 0) cout << "There are no contacts of that id number in the address book, " << endl;
    Sleep(2000);
}
void Addressed::update_contact_in_file (Addressed contact, int id)
{
    fstream file, temp_file;
    file.open("object_contacts.txt",ios::in);
    string line;
    int contact_id;
    while (getline(file, line))
    {
        string text;
        size_t position = line.find('|');
        for (int i=0; i<position; i++) text+= line[i];
        contact_id = string_to_int_convert (text);
        if (contact_id != id)
        {
            temp_file.open ("temp.txt",ios::out | ios::app);
            temp_file << line << endl;
            temp_file.close();
        }
        else
        {
            temp_file.open ("temp.txt",ios::out | ios::app);
            temp_file << contact.contact_id                << "|";
            temp_file << contact.id                        << "|";
            temp_file << contact.name                      << "|";
            temp_file << contact.surname                   << "|";
            temp_file << contact.address                   << "|";
            temp_file << contact.email_address             << "|";
            temp_file << contact.phone_number              << "|" << endl;
            temp_file.close();
        }
    }
    file.close();
    remove("object_contacts.txt");
    rename("temp.txt","object_contacts.txt");
    cout << "Contact details updated... ";
}
void Addressed::change_password (vector<User> & users, int logged_user)
{
    string new_data;
    for (vector<User>::iterator it = users.begin(); it != users.end(); it++)
    {
        if (it-> user_id == logged_user)
        {
            cout << "Type in new password: ";
            cin >> new_data;
            it -> password = new_data;
            update_users_file (*it, logged_user);
            cout << "Password updated..."; Sleep(1000);
        }
    }
}
void Addressed::update_users_file (User data, int logged_user)
{
    fstream file, temp_file;
    file.open("object.txt",ios::in);
    string line;
    int id;
    while (getline(file, line))
    {
        string text;
        size_t position = line.find('|');
        for (int i=0; i<position; i++) text+= line[i];
        id = string_to_int_convert (text);
        if (id != logged_user)
        {
            temp_file.open ("temp.txt",ios::out | ios::app);
            temp_file << line << endl;
            temp_file.close();
        }
        else
        {
            temp_file.open ("temp.txt",ios::out | ios::app);
            temp_file << data.user_id                          << "|";
            temp_file << data.user_name                        << "|";
            temp_file << data.password                         << "|" << endl;
            temp_file.close();
        }
    }
    file.close();
    remove("object.txt");
    rename("temp.txt","object.txt");
}
string Addressed::convert_first_letter_to_capital (string text)
{
    string first_capital_letter;
    transform (text.begin(), text.end(), text.begin(),::tolower);
    text[0] = toupper (text[0]);
    first_capital_letter = text;
    return first_capital_letter;
}
int Addressed::string_to_int_convert (string text)
{
    std::string str = text;
    int k;
    std::istringstream iss(str);
    iss >> k;
    return k;
}
void Addressed::display_address_book_menu ()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"                         << endl;
    cout << " Address book menu:"                                 << endl;
    cout << "---------------------------"                         << endl;
    cout << "1.  Add new contact"                                 << endl;
    cout << "2.  Find by first name"                              << endl;
    cout << "3.  Find by surname"                                 << endl;
    cout << "4.  Display all contacts"                            << endl;
    cout << "5.  Delete contact"                                  << endl;
    cout << "6.  Edit contact"                                    << endl;
    cout << "7.  Change your password"                            << endl;
    cout << "8.  Log out"                                         << endl;
    cout << "---------------------------"                         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void Addressed::display_edit_menu()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"                       << endl;
    cout << " Edit menu:"                                       << endl;
    cout << "---------------------------"                       << endl;
    cout << "1.  Edit first name"                               << endl;
    cout << "2.  Edit surname"                                  << endl;
    cout << "3.  Edit address"                                  << endl;
    cout << "4.  Edit email address"                            << endl;
    cout << "5.  Edit phone number"                             << endl;
    cout << "6.  Back to main menu"                             << endl;
    cout << "---------------------------"                       << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
Addressed::Addressed (int number1, int number2, string text1, string text2, string text3, string text4, string text5)
{
    contact_id = number1;
    id = number2;
    name = text1;
    surname = text2;
    address = text3;
    email_address = text4;
    phone_number = text5;
}
Addressed::~Addressed ()
{
}

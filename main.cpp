#include <iostream>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
struct User
{
    int user_id;
    string user_name, password;
};
struct Addressed
{
    int id;
    string name, surname, address, email_address, phone_number;
};

void find_contact_by_first_name (vector <Addressed> & contacts);
void find_contact_by_surname (vector <Addressed> & contacts, int contacts_qty);
void display_all_contacts (vector <Addressed> & contacts, int contacts_qty);
void display_content(vector <Addressed> & contacts, int i);
void delete_contact(vector <Addressed> & contacts, int contacts_qty);
void edit_contact (vector <Addressed> & contacts);
void edit_first_name (vector <Addressed> & contacts, int id);
void edit_surname (vector <Addressed> & contacts, int id);
void edit_address (vector <Addressed> & contacts, int id);
void edit_email_address (vector <Addressed> & contacts, int id);
void edit_phone_number (vector <Addressed> & contacts, int id);
void create_temp_file (vector <Addressed> & contacts);
void display_all_contacts (vector <Addressed> & contacts, int contacts_qty);
void exit();
void display_main_menu ();
void display_edit_menu();
void address_book_full (int contacts_qty, const int maximum_contacts_qty);
int import_address_book (vector <Addressed> & contacts);
int add_new_contact (vector <Addressed> & contacts, int last_contact_id_number, int contacts_qty);
int string_to_int_convert (string text_of_id);
int get_last_contact_id_number (vector <Addressed> & contacts);
string convert_first_letter_to_capital (string text);

int main()
{

    const int maximum_contacts_qty = 1000;
    vector <Addressed> contacts;
    int contacts_qty = import_address_book (contacts);
    char select;

    while (contacts_qty <= maximum_contacts_qty)
    {
        display_main_menu();
        cout << endl << "Select:";
        cin >> select;
        int last_contact_id_number = get_last_contact_id_number (contacts);

        switch (select)
        {
        case '1':
            address_book_full (contacts_qty, maximum_contacts_qty);
            contacts_qty = add_new_contact (contacts, last_contact_id_number, contacts_qty);
            break;
        case '2':
            find_contact_by_first_name (contacts);
            break;
        case '3':
            find_contact_by_surname (contacts, contacts_qty);
            break;
        case '4':
            display_all_contacts (contacts, contacts_qty);
            break;
        case '5':
            delete_contact (contacts, contacts_qty);
            break;
        case '6':
            edit_contact (contacts);
            break;
        case '9':
            exit ();
           break;
        }
    }

    return 0;
}

void display_main_menu ()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"                         << endl;
    cout << " Main menu:"                                         << endl;
    cout << "---------------------------"                         << endl;
    cout << "1.  Add new contact"                                 << endl;
    cout << "2.  Find by first name"                              << endl;
    cout << "3.  Find by surname"                                 << endl;
    cout << "4.  Display all contacts"                            << endl;
    cout << "5.  Delete contact"                                  << endl;
    cout << "6.  Edit contact"                                    << endl;
    cout << "9.  Exit program"                                    << endl;
    cout << "---------------------------"                         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void display_edit_menu()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"                       << endl;
    cout << " Edit menu:"                                     << endl;
    cout << "---------------------------"                       << endl;
    cout << "1.  Edit first name"                            << endl;
    cout << "2.  Edit surname"                               << endl;
    cout << "3.  Edit address"                               << endl;
    cout << "4.  Edit email address"                               << endl;
    cout << "5.  Edit phone number"                               << endl;
    cout << "6.  Back to main menu"                               << endl;

    cout << "---------------------------"                       << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

int import_address_book (vector <Addressed> & contacts)
{
    fstream file;
    file.open("Address_Book_vector.txt",ios::in);

    if (!file.good())
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << "There are no contacts in the address book. Please add a new contact, " << endl;
        cout << endl;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
    }

    string line;
    char mark = '|';
    int text_nr = 1;
    int contacts_qty_file = 0;
    size_t position;

    Addressed contact_from_file;

    while (getline(file, line, mark))
    {
        switch (text_nr)
        {
        case 1: contact_from_file.id = atoi(line.c_str()); break;
        case 2: contact_from_file.name = line; break;
        case 3: contact_from_file.surname = line; break;
        case 4: contact_from_file.address = line; break;
        case 5: contact_from_file.email_address = line; break;
        case 6: contact_from_file.phone_number = line;
                contacts.push_back(contact_from_file); break;
        }
        if (text_nr == 6){text_nr = 0, contacts_qty_file ++;}
        text_nr ++;
    }
    file.close();

    return contacts_qty_file;
}

void create_temp_file (vector <Addressed> & contacts)
{
    fstream file;
    file.open("temp.txt",ios::out | ios::app);
    for (vector<Addressed>:: iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
            file << it->id << "|";
            file << it->name << "|";
            file << it->surname << "|";
            file << it-> address << "|";
            file << it-> email_address << "|";
            file << it-> phone_number << "|" << endl;
    }
    file.close();
    remove("Address_Book_vector.txt");
    rename("temp.txt","Address_Book_vector.txt");
}

int get_last_contact_id_number (vector <Addressed> & contacts)
{
    int last_contact_id;

    for (vector<Addressed>:: iterator it = contacts.begin(); it != contacts.end(); ++it)
    {
            last_contact_id = it->id;
    }

    return last_contact_id;
}

int add_new_contact (vector <Addressed> & contacts, int last_contact_id_number, int contacts_qty)
{
    Addressed new_contact;

    string name, surname, address, email_address, phone_number;

    cout << "Type in first name: ";
    cin >> name;
    name = convert_first_letter_to_capital (name);

    cout << "Type in surname: ";
    cin >> surname;
    surname = convert_first_letter_to_capital (surname);

    cout << "Type in an address: ";
    cin.sync();
    getline (cin, address);

    cout << "Type in an email address: ";
    cin >> email_address;

    cout << "Type in a phone number: ";
    cin >> phone_number;

    new_contact.name = name;
    new_contact.surname = surname;
    new_contact.address = address;
    new_contact.email_address = email_address;
    new_contact.phone_number = phone_number;
    new_contact.id = last_contact_id_number +1;

    contacts.push_back(new_contact);

    cout << endl << "A new contact has been added to the address book";
    Sleep(2000);

        fstream file;
        file.open("Address_Book_vector.txt",ios::out | ios::app);
        file<<new_contact.id              <<"|";
        file<<new_contact.name            <<"|";
        file<<new_contact.surname         <<"|";
        file<<new_contact.address         <<"|";
        file<<new_contact.email_address   <<"|";
        file<<new_contact.phone_number    <<"|"<<endl;
        file.close();

    return contacts_qty +1;
}

void display_all_contacts (vector <Addressed> & contacts, int contacts_qty)
{

    if (contacts_qty!=0)
    {
        for (vector<Addressed>:: iterator it = contacts.begin(); it != contacts.end(); ++it)
        {
            cout << it->id << "|";
            cout << it->name << "|";
            cout << it->surname << "|";
            cout << it-> address << "|";
            cout << it-> email_address << "|";
            cout << it-> phone_number << "|" << endl;
        }
        cout << endl;
        system("pause");
    }
    else
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << "There are no contacts in the address book. Please add a new contact, " << endl;
        cout << endl;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
    }
}

void display_content(vector <Addressed> & contacts, int i)
{
    cout<<contacts[i].id                                   << "|";
    cout<<contacts[i].name                                 << "|";
    cout<<contacts[i].surname                              << "|";
    cout<<contacts[i].address                              << "|";
    cout<<contacts[i].email_address                        << "|";
    cout<<contacts[i].phone_number                         << "|"<<endl;
}

void find_contact_by_first_name (vector <Addressed> & contacts)
{
    string name;
    cout << endl << "Please type in the first name of contact you are looking for: ";
    cin >> name;
    int number_of_case = 0;

    name = convert_first_letter_to_capital (name);

    for (int i=0; i<contacts.size(); i++)
    {
        if (contacts[i].name == name)
        {
            display_content(contacts, i);
            number_of_case ++;
        }
    }

    if (number_of_case == 0) cout << "There are no contacts of that first name in the address book, " << endl;
    system("pause");
}

void find_contact_by_surname (vector <Addressed> & contacts, int contacts_qty)
{
    string surname;
    int number_of_case = 0;
    cout << endl << "Please type in the surname of contact you are looking for: ";
    cin >> surname;

    surname = convert_first_letter_to_capital (surname);

    for (int i=0; i<contacts.size(); i++)
    {
        if (contacts[i].surname == surname)
        {
            display_content(contacts, i);
            number_of_case ++;
        }
    }

    if (number_of_case == 0) cout << "There are no contacts of that surname in the address book, " << endl;
    system("pause");
}

void delete_contact (vector <Addressed> & contacts, int contacts_qty)
{
    int id;
    int number_of_case = 0;
    cout << endl << "Please type an id number of contact you would like to delete: ";
    cin >> id;

    for (int i=0; i<contacts.size(); i++)
    {
        if (contacts[i].id == id)
        {
            cout<<endl<< "Press the letter t on the keyboard in order to delete the following contact: "<<endl;
            display_content(contacts, i);
            number_of_case ++;

            char select;
            cin >> select;

                if (select == 't')
                {
                    contacts.erase(contacts.begin() + i);
                    cout << "Contact has been deleted from the address book...";
                    Sleep(2000);
                    create_temp_file(contacts);

                }
                else
                {
                    cout << "You didn't press the letter t - the address book remains unchanged.";
                    Sleep(2000);
                }
        }
    }

    if (number_of_case == 0) cout << "There are no contacts of that id number in the address book," << endl;
    Sleep(2000);

}

void edit_contact (vector <Addressed> & contacts)
{
    int id;
    cout << endl << "Please type an id number of contact you would like to edit: ";
    cin >> id;
    int number_of_case = 0;

    for (int i=0; i<contacts.size(); i++)
    {
        while (contacts[i].id == id)
        {
            number_of_case ++;
            display_edit_menu();
            cout<<endl<< "Select from the above menu what you would like to edit: ";

            char select;
            cin >> select;

            switch (select)
            {
            case '1':
                edit_first_name (contacts, id);
                break;
            case '2':
                edit_surname (contacts, id);
                break;
            case '3':
                edit_address (contacts, id);
                break;
            case '4':
                edit_email_address (contacts, id);
                break;
            case '5':
                edit_phone_number (contacts, id);
                break;
            case '6':
                display_main_menu();
                break;
            }
           break;
        }
    }

    if (number_of_case == 0)
    {
        cout << "There are no contacts of that id number in the address book," << endl;
        Sleep(2000);
    }

}

void edit_first_name (vector <Addressed> & contacts, int id)
{
    string new_name;
    cout << "Type in new first name: ";
    cin >> new_name;
    new_name = convert_first_letter_to_capital (new_name);

    vector<Addressed>::iterator it;
    for (it = contacts.begin(); it != contacts.end(); it++)
    {
        if (it->id == id)
        {
            it->name = new_name;
            cout << "Contact details updated successfully..";
            Sleep(2000);
            create_temp_file(contacts);
            break;
        }
    }
}

void edit_surname (vector <Addressed> & contacts, int id)
{
    string new_surname;
    cout << "Type in new surname: ";
    cin >> new_surname;
    new_surname = convert_first_letter_to_capital (new_surname);

    vector<Addressed>::iterator it;
    for (it = contacts.begin(); it != contacts.end(); it++)
    {
        if (it->id == id)
        {
            it->surname = new_surname;
            cout << "Contact details updated successfully..";
            Sleep(2000);
            create_temp_file(contacts);
            break;
        }
    }
}

void edit_address (vector <Addressed> & contacts, int id)
{
    string new_address;
    cout << "Type in new address: ";
    cin.sync();
    getline (cin, new_address);

        vector<Addressed>::iterator it;
        for (it = contacts.begin(); it != contacts.end(); it++)
        {
            if (it->id == id)
            {
                it->address = new_address;
                cout << "Contact details updated successfully..";
                Sleep(2000);
                create_temp_file(contacts);
                break;
            }
        }
}
void edit_email_address (vector <Addressed> & contacts, int id)
{
    string new_email;
    cout << "Type in new email address: ";
    cin >> new_email;

        vector<Addressed>::iterator it;
        for (it = contacts.begin(); it != contacts.end(); it++)
        {
            if (it->id == id)
            {
                it->email_address = new_email;
                cout << "Contact details updated successfully..";
                Sleep(2000);
                create_temp_file(contacts);
                break;
            }
        }
}

void edit_phone_number (vector <Addressed> & contacts, int id)
{
    string new_phone_number;
    cout << "Type in new phone number: ";
    cin >> new_phone_number;

        vector<Addressed>::iterator it;
        for (it = contacts.begin(); it != contacts.end(); it++)
        {
            if (it->id == id)
            {
                it->phone_number = new_phone_number;
                cout << "Contact details updated successfully..";
                Sleep(2000);
                create_temp_file(contacts);
                break;
            }
        }
}

void address_book_full (int contacts_qty, const int maximum_contacts_qty)
{
    if (contacts_qty == maximum_contacts_qty)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << endl << "The address book has reached its maximum size. You can't add any more contacts. Call system administrator for support.";
        cout << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        exit(0);
    }
}
void exit()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout << endl << "End of program!" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    exit(0);
}

int string_to_int_convert (string text)
{
    std::string str = text;
    int k;
    std::istringstream iss(str);
    iss >> k;
    return k;
}

string convert_first_letter_to_capital (string text)
{
    string first_capital_letter;

    transform (text.begin(), text.end(), text.begin(),::tolower);
    text[0] = toupper (text[0]);

    first_capital_letter = text;

    return first_capital_letter;
}

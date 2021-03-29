// to wersja zmodyfikowana mojego oryginalnego kodu po sugestiach Kamila odnosnie dodania
// 2 dodatkowych funkcji rozbicie find by name i surname i display content
// tutaj rowniez zrobilem refaktoryzacje mojego kodu zgodnie z nowym seminarium
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <fstream>

using namespace std;

struct Address_Book
{
    int id;
    string name, surname, address, email_address, phone_number;
};

void display_main_menu ();
void display_search_menu();
void find_contact (Address_Book contacts[], int contacts_qty);
void display_all_contacts (Address_Book contacts[], int contacts_qty);
void exit();
void address_book_full (int contacts_qty, const int maximum_contacts_qty);
void display_by_name (Address_Book contacts[], int contacts_qty, string name);
void display_by_surname (Address_Book contacts[], int contacts_qty, string surname);
void display_content (Address_Book contacts[], int i);
int import_address_book (Address_Book contacts[]);
int add_new_contact (Address_Book contacts[], int contacts_qty);

int main()
{
    const int maximum_contacts_qty = 1000;
    Address_Book contacts [maximum_contacts_qty];
    int contacts_qty = import_address_book (contacts);

    char select;

    while (contacts_qty <= maximum_contacts_qty)
    {
        display_main_menu();
        cout << endl << "Select:";
        cin >> select;

        switch (select)
        {
        case '1':
            address_book_full (contacts_qty, maximum_contacts_qty);
            contacts_qty = add_new_contact (contacts, contacts_qty);
            break;
        case '2':
            find_contact (contacts, contacts_qty);
            break;
        case '3':
            display_all_contacts (contacts, contacts_qty);
            break;
        case '4':
            exit ();
            break;
        }
    }

    return 0;
}

int import_address_book (Address_Book contacts[])
{
    fstream file;
    file.open("Address_Book.txt",ios::in);

    if (!file.good())
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << "There are no contacts in the address book. Please add a new contact, " << endl;
        cout << endl;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
    }

    string line;
    int line_nr = 1;
    int contacts_qty_file = 0;

    while (getline(file,line))
    {
        switch (line_nr)
        {
            case 1: contacts[contacts_qty_file].id = atoi(line.c_str()); break;
            case 2: contacts[contacts_qty_file].name = line; break;
            case 3: contacts[contacts_qty_file].surname = line; break;
            case 4: contacts[contacts_qty_file].address = line; break;
            case 5: contacts[contacts_qty_file].email_address = line; break;
            case 6: contacts[contacts_qty_file].phone_number = line; break;
        }
        if (line_nr == 6) {line_nr = 0; contacts_qty_file ++;}
        line_nr ++;
    }
    file.close();
    return contacts_qty_file;
}

void display_main_menu ()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"                       << endl;
    cout << " Main menu:"                                       << endl;
    cout << "---------------------------"                       << endl;
    cout << "1.  Add new contact"                               << endl;
    cout << "2.  Find contact"                                  << endl;
    cout << "3.  Display all contacts"                          << endl;
    cout << "4.  Exit program"                                  << endl;
    cout << "---------------------------"                       << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void display_search_menu()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"                       << endl;
    cout << " Search menu:"                                     << endl;
    cout << "---------------------------"                       << endl;
    cout << "1.  Find by first name"                            << endl;
    cout << "2.  Find by surname"                               << endl;

    cout << "---------------------------"                       << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

int add_new_contact (Address_Book contacts[], int contacts_qty)
{
    string name, surname, address, email_address, phone_number;

    cout << "Type in first name: ";
    cin >> name;
    transform (name.begin(), name.end(), name.begin(),::tolower);
    name[0] = toupper (name[0]);

    cout << "Type in surname: ";
    cin >> surname;
    transform (surname.begin(), surname.end(), surname.begin(),::tolower);
    surname[0] = toupper (surname[0]);

    cout << "Type in an address: ";
    cin.sync();
    getline (cin, address);

    cout << "Type in an email address: ";
    cin >> email_address;

    cout << "Type in a phone number: ";
    cin >> phone_number;

    contacts[contacts_qty].name = name;
    contacts[contacts_qty].surname = surname;
    contacts[contacts_qty].address = address;
    contacts[contacts_qty].email_address = email_address;
    contacts[contacts_qty].phone_number = phone_number;
    contacts[contacts_qty].id = contacts_qty +1;

    cout << endl << "A new contact has been added to the address book";
    Sleep(2000);

        fstream file;
        file.open("Address_Book.txt",ios::out | ios::app);
        file<<contacts[contacts_qty].id                     << endl;
        file<<contacts[contacts_qty].name                   << endl;
        file<<contacts[contacts_qty].surname                << endl;
        file<<contacts[contacts_qty].address                << endl;
        file<<contacts[contacts_qty].email_address          << endl;
        file<<contacts[contacts_qty].phone_number           << endl;
        file.close();

    return contacts_qty +1;
}

void find_contact (Address_Book contacts[], int contacts_qty)
{
    display_search_menu();
    char select;
    cout << endl << "Select:";
    cin >> select;

    if (select == '1')
    {
        string name;
        cout << endl << "Please type in the first name of contact you are looking for: ";
        cin >> name;
        transform(name.begin(), name.end(), name.begin(),::tolower);
        name[0] = toupper (name[0]);
        display_by_name (contacts, contacts_qty, name);
    }

    if (select == '2')
    {
        string surname;
        cout << endl <<"Please type in the surname of contact you are looking for: ";
        cin >> surname;
        transform(surname.begin(), surname.end(), surname.begin(),::tolower);
        surname[0] = toupper(surname[0]);
        display_by_surname (contacts, contacts_qty, surname);
    }
}

void display_by_name (Address_Book contacts[], int contacts_qty, string name)
{
        int number_of_case = 0;
        for (int i=0; i<contacts_qty; i++)
        {
            if (contacts[i].name == name)
            {
                number_of_case++;
                display_content(contacts, i);
            }
        }
        if (number_of_case == 0)
        {
           cout << endl << "No contact of that name was found," << endl;
        }

        cout << endl;
        system("pause");
}

void display_by_surname (Address_Book contacts[], int contacts_qty, string surname)
{
    int number_of_case = 0;
    for (int i=0; i<contacts_qty; i++)
        {
            if (contacts[i].surname == surname)
            {
                number_of_case++;
                display_content(contacts, i);
            }
        }
        if (number_of_case == 0)
        {
           cout << endl << "No contact of that surname was found," << endl;
        }
        cout << endl;
        system("pause");
}

void display_content (Address_Book contacts[], int i)
{
    cout<<                                                            endl;
    cout<<"ID: "<<contacts[i].id                                   << endl;
    cout<<"Name: "<<contacts[i].name                               << endl;
    cout<<"Surname: "<<contacts[i].surname                         << endl;
    cout<<"Address: "<<contacts[i].address                         << endl;
    cout<<"Email address: "<<contacts[i].email_address             << endl;
    cout<<"Phone number: "<<contacts[i].phone_number               << endl;
}

void display_all_contacts (Address_Book contacts[], int contacts_qty)
{
    for (int i=0; i<contacts_qty; i++)
    {
       display_content(contacts, i);
    }
    if (contacts_qty == 0)
    {
        cout << endl << "No contacts saved in the address book" << endl;
    }

    cout << endl;
    system("pause");
}

void exit()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout << endl << "End of program!" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    exit(0);
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

/* ponizej moj oryginalny kod ktory napisalem ksiazka adresowa

#include <iostream>
#include <windows.h>
#include <algorithm>
#include <fstream>

using namespace std;

struct Address_Book
{
    int id;
    string name, surname, address, email_address, phone_number;
};

void display_main_menu ();
void display_search_menu();
void find_contact (Address_Book contacts[], int contacts_qty);
void display_all_contacts (Address_Book contacts[], int contacts_qty);
void exit();
void address_book_full (int contacts_qty);
int import_address_book (Address_Book contacts[]);
int add_new_contact (Address_Book contacts[], int contacts_qty);

int main()
{
    Address_Book contacts[1000];
    int contacts_qty=import_address_book(contacts);

     // loop to display all contacts already saved in the file "Address_Book.txt"
    //for (int i=0; i<contacts_qty; i++)
    //{
     //   cout<<"ID:"<<contacts[i].id<<endl;
     //   cout<<"Name:"<<contacts[i].name<<endl;
     //   cout<<"Surname:"<<contacts[i].surname<<endl;
     //   cout<<"Address:"<<contacts[i].address<<endl;
      //  cout<<"Email address:"<<contacts[i].email_address<<endl;
     //   cout<<"Phone number:"<<contacts[i].phone_number<<endl;
     //   cout<<endl;
   //}
    //system("pause");


    char select;

    while (contacts_qty<=1000)
    {
        display_main_menu();
        cout <<endl<<"Select:";
        cin >>select;

        switch (select)
        {
        case '1':
            contacts_qty = add_new_contact (contacts, contacts_qty);
            break;
        case '2':
            find_contact (contacts, contacts_qty);
            break;
        case '3':
            display_all_contacts (contacts, contacts_qty);
            break;
        case '4':
            exit ();
            break;
        }
    }

    return 0;
}

int import_address_book (Address_Book contacts[])
{
    fstream file;
    file.open("Address_Book.txt",ios::in);

    if (file.good() == false)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout<<"There are no contacts in the address book. Please add a new contact, "<<endl;
        cout<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
    }

    string line;
    int line_nr=1;
    int i=0;
    while (getline(file,line))
    {
        switch (line_nr)
        {
            case 1: contacts[i].id = atoi(line.c_str()); break;
            case 2: contacts[i].name = line; break;
            case 3: contacts[i].surname = line; break;
            case 4: contacts[i].address = line; break;
            case 5: contacts[i].email_address = line; break;
            case 6: contacts[i].phone_number = line; break;
        }
        if (line_nr==6) {line_nr=0; i++;}
        line_nr++;
    }
    file.close();
    return i;
}

void display_main_menu ()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"<<endl;
    cout << " Main menu:"<<endl;
    cout << "---------------------------"<<endl;
    cout << "1.  Add new contact"<<endl;
    cout << "2.  Find contact"<<endl;
    cout << "3.  Display all contacts"<<endl;
    cout << "4.  Exit program"<<endl;
    cout << "---------------------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void display_search_menu()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"<<endl;
    cout << " Search menu:"<<endl;
    cout << "---------------------------"<<endl;
    cout << "1.  Find by first name"<<endl;
    cout << "2.  Find by surname"<<endl;

    cout << "---------------------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

int add_new_contact (Address_Book contacts[], int contacts_qty)
{
    address_book_full(contacts_qty);

    string name, surname, address, email_address, phone_number;

    cout<<"Type in first name: ";
    cin>>name;
    transform(name.begin(), name.end(), name.begin(),::tolower);
    name[0]=toupper(name[0]);

    cout<<"Type in surname: ";
    cin>>surname;
    transform(surname.begin(), surname.end(), surname.begin(),::tolower);
    surname[0]=toupper(surname[0]);

    cout<<"Type in an address: ";
    cin.sync();
    getline (cin, address);

    cout<<"Type in an email address: ";
    cin>>email_address;

    cout<<"Type in a phone number: ";
    cin>>phone_number;

    contacts[contacts_qty].name=name;
    contacts[contacts_qty].surname=surname;
    contacts[contacts_qty].address=address;
    contacts[contacts_qty].email_address=email_address;
    contacts[contacts_qty].phone_number=phone_number;
    contacts[contacts_qty].id=contacts_qty+1;

    cout<<endl<<"A new contact has been added to the address book";
    Sleep(2000);

        fstream file;
        file.open("Address_Book.txt",ios::out | ios::app);
        file<<contacts[contacts_qty].id<<endl;
        file<<contacts[contacts_qty].name<<endl;
        file<<contacts[contacts_qty].surname<<endl;
        file<<contacts[contacts_qty].address<<endl;
        file<<contacts[contacts_qty].email_address<<endl;
        file<<contacts[contacts_qty].phone_number<<endl;
        file.close();

    return contacts_qty+1;
}

void find_contact (Address_Book contacts[], int contacts_qty)
{
    display_search_menu();
    int number_of_case=0;
    char select;
    cout <<endl<<"Select:";
    cin >>select;

    if (select=='1')
    {

        string name;
        cout<<endl<<"Please type in the first name of contact you are looking for: ";
        cin>>name;
        transform(name.begin(), name.end(), name.begin(),::tolower);
        name[0]=toupper(name[0]);

        for (int i=0; i<contacts_qty; i++)
        {
            if (contacts[i].name==name)
            {
                number_of_case++;
                cout<<endl;
                cout<<"ID: "<<contacts[i].id<<endl;
                cout<<"Name: "<<contacts[i].name<<endl;
                cout<<"Surname: "<<contacts[i].surname<<endl;
                cout<<"Address: "<<contacts[i].address<<endl;
                cout<<"Email address: "<<contacts[i].email_address<<endl;
                cout<<"Phone number: "<<contacts[i].phone_number<<endl;
            }
        }

        if (number_of_case==0)
        {
           cout<<endl<<"No contact of that name was found,"<<endl;
        }

        cout<<endl;
        system("pause");
    }

    if (select=='2')
    {
        string surname;
        cout<<endl<<"Please type in the surname of contact you are looking for: ";
        cin>>surname;
        transform(surname.begin(), surname.end(), surname.begin(),::tolower);
        surname[0]=toupper(surname[0]);

        for (int i=0; i<contacts_qty; i++)
        {
            if (contacts[i].surname==surname)
            {
                number_of_case++;
                cout<<endl;
                cout<<"ID: "<<contacts[i].id<<endl;
                cout<<"Name: "<<contacts[i].name<<endl;
                cout<<"Surname: "<<contacts[i].surname<<endl;
                cout<<"Address: "<<contacts[i].address<<endl;
                cout<<"Email address: "<<contacts[i].email_address<<endl;
                cout<<"Phone number: "<<contacts[i].phone_number<<endl;
            }
        }
        if (number_of_case==0)
        {
           cout<<endl<<"No contact of that surname was found,"<<endl;
        }
        cout<<endl;
        system("pause");
    }
}
void display_all_contacts (Address_Book contacts[], int contacts_qty)
{
    for (int i=0; i<contacts_qty; i++)
    {
        cout<<endl;
        cout<<"ID: "<<contacts[i].id<<endl;
        cout<<"Name: "<<contacts[i].name<<endl;
        cout<<"Surname: "<<contacts[i].surname<<endl;
        cout<<"Address: "<<contacts[i].address<<endl;
        cout<<"Email address: "<<contacts[i].email_address<<endl;
        cout<<"Phone number: "<<contacts[i].phone_number<<endl;
    }
    if (contacts_qty==0)
    {
        cout<<endl<<"No contacts saved in the address book"<<endl;
    }

    cout<<endl;
    system("pause");
}

void exit()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout<<endl<<"End of program!"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    exit(0);
}

void address_book_full (int contacts_qty)
{
    if (contacts_qty==1000)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout<<"The address book has reached its maximum size. You can't add any more contacts. Call system administrator for support.";
        cout<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        exit(0);
    }
}
*/

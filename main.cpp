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
    int contact_id;
    int id;
    string name, surname, address, email_address, phone_number;
};
void import_list_of_users (vector <User> & users);
int log_in (vector<User> & users);
void add_new_user (vector<User> & users);
bool exit();
void import_list_of_contacts (vector <Addressed> & contacts, int logged_user);
void add_new_contact (vector<Addressed> & contacts, int logged_user);
int get_last_contact_id ();
void find_contact_by_first_name (vector <Addressed> & contacts);
void display_content (Addressed content);
void find_contact_by_surname (vector <Addressed> & contacts);
void display_all_contacts (vector<Addressed> & contacts);
void delete_contact (vector <Addressed> & contacts);
void delete_contact_from_file (int id);
void edit_contact (vector <Addressed> & contacts);
void update_contact_in_file (Addressed contact, int id);
void change_password (vector<User> & users, int logged_user);
void update_users_file (User data, int logged_user);
int string_to_int_convert (string text);
string convert_first_letter_to_capital (string text);
void display_main_menu();
void display_address_book_menu ();
void display_edit_menu();

int main()
{
    vector <User> users;
    import_list_of_users(users);
    char select;
    int user_logged_in = 0;
    bool program_end;

    while (!program_end)
    {
        display_main_menu();
        cout << endl << "Select:";
        cin >> select;
        switch (select)
        {
           case '1': user_logged_in = log_in (users); break;
           case '2': add_new_user (users); break;
           case '3': program_end = exit(); break;
        }
        while (user_logged_in)
        {
            display_address_book_menu();
            vector <Addressed> contacts;
            import_list_of_contacts (contacts, user_logged_in);
            cout << endl << "Select: ";
            cin >> select;
            switch (select)
            {
            case '1': add_new_contact (contacts, user_logged_in); break;
            case '2': find_contact_by_first_name (contacts); break;
            case '3': find_contact_by_surname (contacts); break;
            case '4': display_all_contacts (contacts); break;
            case '5': delete_contact (contacts); break;
            case '6': edit_contact (contacts); break;
            case '7': change_password (users, user_logged_in); break;
            case '8': user_logged_in = 0; break;
            }
        }
    }
    return 0;
}
void import_list_of_users (vector <User> & users)
{
    fstream file;
    file.open("list_of_users.txt",ios::in);
    if (!file.good())
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),12);
        cout << "There are no registered users yet. Register an account, " << endl;
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("pause");
    }
    string line;
    char mark = '|';
    int text_nr = 1;
    User user_from_file;
    while (getline(file, line, mark))
    {
        switch (text_nr)
        {
        case 1: user_from_file.user_id = atoi(line.c_str()); break;
        case 2: user_from_file.user_name = line; break;
        case 3: user_from_file.password = line;
                users.push_back(user_from_file); break;
        }
        if (text_nr == 3) {text_nr = 0;}
        text_nr ++;
    }
    file.close();
}
int log_in (vector<User> & users)
{
    const int number_of_attempts = 3;
    string log_in_user_name;
    string log_in_password;
    cout << endl << "Please type in the user name: ";
    cin >> log_in_user_name;
    for (vector<User>:: iterator it = users.begin(); it != users.end(); ++it)
    {
        if (it -> user_name == log_in_user_name)
        {
            for (int i = 0; i < number_of_attempts; i++)
            {
                cout<<"Type in your password. Attempts left ("<< number_of_attempts - i <<"): ";
                cin>> log_in_password;
                if (it -> password == log_in_password)
                {
                    cout << "Log-in successful" << endl;
                    Sleep(1500);
                    return it -> user_id;
                }
            }
            cout<<"You have tried 3 times with incorrect password. Wait 3 seconds."<<endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "This user name was not registered before ...";
    Sleep (2000);
    return 0;
}
void add_new_user (vector<User> & users)
{
    User new_user;
    string another_user_name;
    cout << "Type in user name: ";
    cin >> another_user_name;
    int i=0;
    while (i<users.size())
    {
        if (users[i].user_name == another_user_name)
        {
            cout << "This user name already exist. Use a different user name: ";
            cin >> another_user_name;
            i = 0;
        }
        else i++;
    }
    new_user.user_name = another_user_name;
    cout << "Type in password: ";
    cin >> new_user.password;
    if (users.size() == 0) new_user.user_id = 1;
    else
    {
       int last_user_id_number = users.back().user_id;
       new_user.user_id = last_user_id_number + 1;
    }
    users.push_back(new_user);
    fstream file;
    file.open ("list_of_users.txt",ios::out | ios::app);
    file << new_user.user_id         <<"|";
    file << new_user.user_name       <<"|";
    file << new_user.password        <<"|" <<endl;
    file.close();
}
bool exit()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout << endl << "Program end...!" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(1000);
    return true;
}
void import_list_of_contacts (vector <Addressed> & contacts, int logged_user)
{
    fstream file;
    file.open("list_of_contacts.txt",ios::in);
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
void add_new_contact (vector<Addressed> & contacts, int logged_user)
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
    file.open ("list_of_contacts.txt",ios::out | ios::app);
    file << new_contact.contact_id             <<"|";
    file << new_contact.id                     <<"|";
    file << new_contact.name                   <<"|";
    file << new_contact.surname                <<"|";
    file << new_contact.address                <<"|";
    file << new_contact.email_address          <<"|";
    file << new_contact.phone_number           <<"|" <<endl;
    file.close();
}
int get_last_contact_id ()
{
    fstream file;
    file.open("list_of_contacts.txt",ios::in);
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
void find_contact_by_first_name (vector <Addressed> & contacts)
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
void display_content (Addressed content)
{
        cout << content.contact_id      << "|";
        cout << content.id              << "|";
        cout << content.name            << "|";
        cout << content.surname         << "|";
        cout << content.address         << "|";
        cout << content.email_address   << "|";
        cout << content.phone_number    << "|" << endl;
}
void find_contact_by_surname (vector <Addressed> & contacts)
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
void display_all_contacts (vector<Addressed> & contacts)
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
void delete_contact (vector <Addressed> & contacts)
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
void delete_contact_from_file (int id)
{
    fstream file;
    fstream temp_file;
    file.open("list_of_contacts.txt",ios::in);
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
    remove("list_of_contacts.txt");
    rename("temp.txt","list_of_contacts.txt");
}
void edit_contact (vector <Addressed> & contacts)
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
void update_contact_in_file (Addressed contact, int id)
{
    fstream file, temp_file;
    file.open("list_of_contacts.txt",ios::in);
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
    remove("list_of_contacts.txt");
    rename("temp.txt","list_of_contacts.txt");
    cout << "Contact details updated... ";
}
void change_password (vector<User> & users, int logged_user)
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
void update_users_file (User data, int logged_user)
{
    fstream file, temp_file;
    file.open("list_of_users.txt",ios::in);
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
    remove("list_of_users.txt");
    rename("temp.txt","list_of_users.txt");
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
void display_main_menu ()
{
    system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout << "---------------------------"                         << endl;
    cout << " Main menu:"                                         << endl;
    cout << "---------------------------"                         << endl;
    cout << "1.  Log in "                                         << endl;
    cout << "2.  Register an account"                                << endl;
    cout << "3.  Exit program"                                    << endl;
    cout << "---------------------------"                         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void display_address_book_menu ()
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
void display_edit_menu()
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

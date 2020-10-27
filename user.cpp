#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <windows.h>
#include "user.h"

using namespace std;

void User::import_list_of_users(vector<User> & users)
{
    fstream file;
    file.open("object.txt",ios::in);
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
void User::add_new_user(vector<User> & users)
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
    file.open ("object.txt",ios::out | ios::app);
    file << new_user.user_id         <<"|";
    file << new_user.user_name       <<"|";
    file << new_user.password        <<"|" <<endl;
    file.close();
}
int User::log_in(vector<User> & users)
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
int User::string_to_int_convert (string text)
{
    std::string str = text;
    int k;
    std::istringstream iss(str);
    iss >> k;
    return k;
}
int User::get_user_id()
{
    fstream file;
    file.open("object.txt",ios::in);
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
void User::display_main_menu ()
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
bool User::exit()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout << endl << "Program end...!" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(1000);
    return true;
}
User::User (int number, string name, string pass)
{
  user_id = number;
  user_name = name;
  password = pass;
}
User::~User()
{
}

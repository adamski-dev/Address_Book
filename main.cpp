#include <iostream>
#include <vector>
#include "user.h"
#include "contacts.h"

using namespace std;

int main()
{
    vector<User> users;
    User users_object;
    users_object.import_list_of_users(users);
    char select;
    bool program_end;
    int user_logged_in = 0;
    while (!program_end)
    {
        users_object.display_main_menu();
        cout << endl << "Select:";
        cin >> select;
        switch (select)
        {
           case '1': user_logged_in = users_object.log_in(users); break;
           case '2': users_object.add_new_user(users); break;
           case '3': program_end = users_object.exit(); break;
        }

        while (user_logged_in)
        {
            vector <Addressed> contacts;
            Addressed contacts_object;
            contacts_object.display_address_book_menu();
            contacts_object.import_list_of_contacts (contacts, user_logged_in);
            cout << endl << "Select: ";
            cin >> select;
            switch (select)
            {
            case '1': contacts_object.add_new_contact (contacts, user_logged_in); break;
            case '2': contacts_object.find_contact_by_first_name (contacts); break;
            case '3': contacts_object.find_contact_by_surname (contacts); break;
            case '4': contacts_object.display_all_contacts (contacts); break;
            case '5': contacts_object.delete_contact (contacts); break;
            case '6': contacts_object.edit_contact (contacts); break;
            case '7': contacts_object.change_password (users, user_logged_in); break;
            case '8': user_logged_in = 0; break;
            }
        }
    }
    return 0;
}
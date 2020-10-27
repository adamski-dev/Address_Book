#include <iostream>

using namespace std;

class User;
class Addressed
{
    int contact_id;
    int id;
    string name, surname, address, email_address, phone_number;

public:
    Addressed (int =1, int =1, string ="A", string ="A", string ="A",string ="A", string ="A");
    ~Addressed ();
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
    string convert_first_letter_to_capital (string text);
    int string_to_int_convert (string text);
    void display_address_book_menu();
    void display_edit_menu();
};

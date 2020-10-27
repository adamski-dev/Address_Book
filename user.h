#include <iostream>

using namespace std;

class User
{
    int user_id;
    string user_name, password;

public:
    User (int =1, string ="A", string ="A");
    ~User ();
    void import_list_of_users(vector<User> & users);
    void add_new_user(vector<User> & users);
    int log_in(vector<User> & users);
    int string_to_int_convert (string text);
    int get_user_id();
    void display_main_menu ();
    bool exit();
    friend class Addressed;
};

#ifndef USER_HPP
#define USER_HPP
#include<iostream>
#include<string>
#include<map>
#include<fstream>

using namespace std;

class User{

    public:

    void Login();
        void Register();
        User(string username, string password);
        string username;
        string password;
        void optionsWhenLoggedIn();
        std::map<string, string> users;
};


#endif //PROJECT2SYSNET_USER_HPP

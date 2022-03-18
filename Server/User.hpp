#ifndef USER_HPP
#define USER_HPP
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include <algorithm>
#include <vector>

using namespace std;

class User{

    public:

    void Login();
        void Register();
        User();
        User(string username, string password);
        string username;
        string password;
        void optionsWhenLoggedIn();
        std::map<string, string> users;
        void subscribe(string location);
        bool unsubscribe(string location);
        string seeLocations();
        vector<string> locations;
};


#endif //PROJECT2SYSNET_USER_HPP

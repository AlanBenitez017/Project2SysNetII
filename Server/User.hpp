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

        User();
        User(string username, string password);
        string username;
        string password;
        string getUsername();
        string getPassword();
        void setUsername(string username);
        void setPassword(string password);
        std::map<string, string> users;
        void subscribe(string location);
        bool unsubscribe(string location);
        string seeLocations();
        vector<string> locations;
};


#endif //USER_HPP

/***************************************************************
  Student Name: Alan Benitez
  File Name: User.hpp
  Project 2

  This is the header file of the user class
***************************************************************/

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
        User(string username, string password, int new_socket, int id);
        string username;
        string password;
        int new_socket;
        int id;
        string getUsername();
        string getPassword();
        int getNewSocket();
        int getId();
        void setUsername(string username);
        void setPassword(string password);
        void setNewSocket(int new_socket);
        void setId(int id);
        //std::map<string, string> users;
        void subscribe(string location);
        bool unsubscribe(string location);
        void addMsg(string msg);
        string seeLast10Msg();
        string seeLocations();
        vector<string> getLocations();
        string sendMsgToLocation();
        vector<string> locations;
        vector<string> messages;
        bool isActive = false;

};


#endif //USER_HPP

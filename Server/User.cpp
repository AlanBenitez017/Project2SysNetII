/***************************************************************
  Student Name: Alan Benitez
  File Name: User.cpp
  Project 2

  Here I implement some methods that will be used in the server class
***************************************************************/

#include "User.hpp"

User::User(string username, string password, int new_socket, int id) {
    this->username = username;
    this->password = password;
    this->new_socket = new_socket;
    this->id = id;
}

User::User(){
    this->username = "";
    this->password = "";
}

string User::getUsername(){
    return username;
}

string User::getPassword(){
    return password;
}

int User::getNewSocket() {
    return new_socket;
}

int User::getId(){
    return id;
}

void User::setUsername(string username){
    this->username = username;
}

void User::setPassword(string password) {
    this->password = password;
}

void User::setNewSocket(int new_socket) {
    this->new_socket = new_socket;
}

void User::setId(int id) {
    this->id = id;
}

void User::addMsg(string msg){
    this->messages.push_back(msg);
}

void User::subscribe(string location){
    this->locations.push_back(location);
}

bool User::unsubscribe(string location) {
    auto it = find(locations.begin(), locations.end(), location);
    if (it == locations.end()) {
        // name not in vector
        return false;
    } else {
        int index = std::distance(locations.begin(), it);
        locations.erase(locations.begin() + index);
        return true;
    }
}

string User::seeLocations() {
    string loc;
    for (unsigned int i = 0; i < locations.size(); i++) {
        loc += to_string(i) + ": "+ locations[i] + "\n";
    }
    return loc;
}

string User::seeLast10Msg() {
    string msgs;
    for (unsigned int i = 0; i < messages.size(); i++) {
        if(messages.empty()){
            msgs = "There is no messages";
        }else {
            msgs += messages[i] + "\n";
        }
    }
    return msgs;
}



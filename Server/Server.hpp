/***************************************************************
  Student Name: Alan Benitez
  File Name: Server.hpp
  Project 2

  This is the header file of the server
***************************************************************/
#ifndef SERVER_HPP
#define SERVER_HPP
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <sstream>
#include <map>
#include "User.hpp"

#define MAX 5000
#define PORT 60010

using namespace std;

class Server{

    public:
        mutex mtx;
        int server_fd;
        int new_socket;
        int id;
        char sendingBuff[MAX];
        char receivingBuff[MAX];
        struct sockaddr_in address;
        int addrLen;
        Server();
        //std::map<string, string> users;
        bool loggedIn = false;
        bool Login(int new_socket, int id);
        void Register(int new_socket);
        void mainMenu(int new_socket, int id);
        bool checkLogin(string username, string password);
        void optionsWhenLoggedIn(int new_socket);
        void subscribe(int new_socket, int id);
        void unsubscribe(int new_socket, int id);
        void seeLocations(int new_socket, int id);
        void seeActiveUsers(int new_socket, int id);
        void sendMsgToAUser(int new_socket, int id);
        void seeLast10Msg(int new_socket, int id);
        void sendMsgToALocation(int new_socket, int id);
        //User u;
        void notImplemented();
        void changePassword(int new_socket, int id);
        void run(int socket, int id);
        vector<thread> threads;
        vector<User> users;
        vector<string> locations;
        int usersActive;


    };

#endif //SERVER_HPP

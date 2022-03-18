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
        int server_fd;
        int new_socket;
        char sendingBuff[MAX];
        char receivingBuff[MAX];
        struct sockaddr_in address;
        int addrLen;
        Server();
        std::map<string, string> users;
        bool logedIn = false;
        bool Login();
        void Register();
        void mainMenu();
        bool checkLogin(string username, string password);
        void optionsWhenLoggedIn();
        void subscribe();
        void unsubscribe();
        void seeLocations();
        User u;
        void notImplemented();
        void changePassword();


    };

#endif //SERVER_HPP

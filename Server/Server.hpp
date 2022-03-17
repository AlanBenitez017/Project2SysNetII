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
#include <map>

#define MAX 5000
#define PORT 60010

using namespace std;

class Server{

    struct newUser{
        int id;
        int new_socket;
    };

    public:
        int numThreads = 4;
        int usersActive = 0;
        int server_fd;
        int new_socket;
        int id;
        char sendingBuff[MAX];
        char receivingBuff[MAX];
        struct sockaddr_in address;
        int addrLen;
        Server();
        std::mutex lock;
        void handleNewClient(struct newUser* user);
        std::map<string, string> users;
        bool logedIn = false;
        bool leave = false;
        bool Login();
        void Register();
        void mainMenu();
        bool checkLogin(string username, string password);
        void optionsWhenLoggedIn();



    };

#endif //PROJECT2SYSNET_SERVER_HPP

/***************************************************************
  Student Name: Alan Benitez
  File Name: Server.cpp
  Project 2

  In this file I develop the responses from the client. Will add the new users to a .txt file and does the communication with the client
***************************************************************/
#include "Server.hpp"

Server::Server() {
    id = 0;
    addrLen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    cout << "bind done" << endl;
    if (listen(server_fd, 10) < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }


    while(true) {

        printf("Waiting for incoming connection...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrLen)) < 0) {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        cout << "Socket value before creating the thread" << new_socket << endl;
        threads.push_back(std::thread(&Server::run, this, new_socket, id));

        for (auto & thread : threads)
        {
            if (thread.joinable())
                thread.join();
        }

    }
}

bool Server::Login() {
    memset(receivingBuff, 0, MAX);
    memset(sendingBuff, 0, MAX);

    string username, password;
    string uName = " Username:\n";

    strcpy(sendingBuff, uName.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
    memset(receivingBuff, 0, MAX);   //might delete it later, already deleted it when calling this function
    read(new_socket, receivingBuff, (size_t)MAX);  //lee lo que acabo de escribir el client

    username = receivingBuff;
    memset(sendingBuff, 0, MAX);
    string pWord = " Password:\n";
    strcpy(sendingBuff, pWord.c_str());
    write(new_socket, sendingBuff, (int)MAX);
    read(new_socket, receivingBuff, (size_t)MAX);  //lee lo que acabo de escribir el client
    password = receivingBuff;
    cout << "u: " << username << " p: "  << password << endl;

    if(checkLogin(username, password)){
        User userr(username, password, new_socket, id);
        users.push_back(userr);
        //u.setUsername(username);
        //u.setPassword(password);
        memset(sendingBuff, 0, MAX);
        string loggedIn = "Successfully Logged In";
        strcpy(sendingBuff, loggedIn.c_str());
        write(new_socket, sendingBuff, (int)MAX);
        return true;
    }else{
        return false;
    }

}

void Server::run(int new_socket, int id){
    cout << "Connection accepted" << endl;
    cout << "Handler assigned" << endl;
    id++;
    cout << "ID #" << id << endl;
    mainMenu(new_socket);

    while(loggedIn){
        memset(receivingBuff, 0, MAX);
        read(new_socket, receivingBuff, (size_t)MAX);
        string choice = receivingBuff;
        int choiceParsed = stoi(choice);
        switch(choiceParsed){
            case 1:
                subscribe();
                break;
            case 2:
                unsubscribe();
                break;
            case 3:
                notImplemented();
                break;
            case 4:
                notImplemented();
                break;
            case 5:
                notImplemented();
                break;
            case 6:
                seeLocations();
                break;
            case 7:
                notImplemented();
                break;
            case 8:
                changePassword();
                break;
            case 9:
                loggedIn = false;
                mainMenu(new_socket);
                break;
            default:
                memset(sendingBuff, 0, MAX);
                string invalid = "Invalid choice, please try again";
                strcpy(sendingBuff, invalid.c_str());
                write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
                optionsWhenLoggedIn();
                break;


        }

    }
}

void Server::Register(){
    memset(receivingBuff, 0, MAX);
    memset(sendingBuff, 0, MAX);

    string username, password;
    string uName = " Username:\n";

    strcpy(sendingBuff, uName.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
    memset(receivingBuff, 0, MAX);   //might delete it later, already freeing it when calling this function
    read(new_socket, receivingBuff, (size_t)MAX);  //lee lo que acabo de escribir el client

    username = receivingBuff;
    memset(sendingBuff, 0, MAX);
    string pWord = " Password:\n";
    strcpy(sendingBuff, pWord.c_str());
    write(new_socket, sendingBuff, (int)MAX);
    read(new_socket, receivingBuff, (size_t)MAX);  //lee lo que acabo de escribir el client
    password = receivingBuff;
    cout << "u: " << username << " p: "  << password << endl; //just to check

    ofstream usersFile;
    usersFile.open("users.txt", fstream::app);
    if (usersFile.is_open())
    {
        usersFile << username << "\t" << password << endl;
        usersFile.close();
    }
    else{
        cout << "Unable to open file";
    }
    memset(sendingBuff, 0, MAX);
    string success = "Successfully Registered";
    strcpy(sendingBuff, success.c_str());
    write(new_socket, sendingBuff, (int)MAX);

}

void Server::changePassword() {

    memset(sendingBuff, 0, MAX);
    string pWord = " Please insert new password:\n";
    strcpy(sendingBuff, pWord.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer

    memset(receivingBuff, 0, MAX);
    read(new_socket, receivingBuff, (size_t)MAX);  //lee lo que acabo de escribir el client
    string newPassword = receivingBuff;

    string username;
    string password;
    string inLine;

    ifstream usersFile;
    fstream tempFile;
    usersFile.open("users.txt", ios::in);
    tempFile.open("temp.txt", ios_base::app | ios::out | ios::in);
    if (usersFile.is_open() && tempFile.is_open()) {
        while (getline(usersFile, inLine)) {
            stringstream ss(inLine);
            ss >> username;
            ss >> password;
            string newLine = username;
            newLine += " ";
            if (username == u.getUsername()){
                newLine += newPassword;
                u.setPassword(newPassword);
            }else{
                newLine += password;
            }
            newLine += "\n";
            tempFile << newLine;
        }
    }

    usersFile.close();
    tempFile.close();
    rename("temp.txt", "users.txt");

    memset(sendingBuff, 0, MAX);
    pWord = " Password changed successfully\n";
    strcpy(sendingBuff, pWord.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
    optionsWhenLoggedIn();
}

void Server::mainMenu(int new_socket) {
    memset(sendingBuff, 0, MAX);
    string firstOptions = "Welcome!\n  Press 1 to Login\n  Press 2 to Register\n  Type \'exit\' to Quit\n";
    strcpy(sendingBuff, firstOptions.c_str());
    write(new_socket, sendingBuff, (int)MAX);

    while(loggedIn == false){
        memset(receivingBuff, 0, MAX);
        read(new_socket, receivingBuff, (size_t)MAX);
        if(strcmp(receivingBuff, "exit") == 0){
            close(new_socket);
            exit(EXIT_SUCCESS);
        }
        if(strcmp(receivingBuff, "1") == 0){
            if(Login()){
                optionsWhenLoggedIn();
                //isActive = true;
                loggedIn = true;
            }else{
                string notFound = "Could not find the account";
                strcpy(sendingBuff, notFound.c_str());
                write(new_socket, sendingBuff, (int)MAX);
                mainMenu(new_socket);
            }
        }
        if(strcmp(receivingBuff, "2") == 0){
            Register();
            mainMenu(new_socket);
        }
    }
}

bool Server::checkLogin(string username, string password) {
    string uName, pWord;
    ifstream usersFile;
    usersFile.open("users.txt");
    if (usersFile.is_open())
    {
        usersFile >> uName >> pWord;
        while (!usersFile.eof()) { // keep reading until end-of-file
            if(uName == username && pWord == password){
                return true;
            }
            usersFile >> uName >> pWord; // sets EOF flag if no value found
        }
        usersFile.close();
    }
    return false;
}

void Server::optionsWhenLoggedIn() {
    memset(sendingBuff, 0, MAX);
    string options;
    options = " 1. Subscribe to a location\n";
    options += " 2. Unsubscribe to a location\n";
    options += " 3. See the online users\n";
    options += " 4. Send a message to a user\n";
    options += " 5. Send a group message to a location\n";
    options += " 6. See all the locations that the client has subscribed to\n";
    options += " 7. See the last 10 message received\n";
    options += " 8. Change password\n";
    options += " 9. Quit\n";
    strcpy(sendingBuff, options.c_str());
    write(new_socket, sendingBuff, (int)MAX);

}

void Server::subscribe(){
    memset(sendingBuff, 0, MAX);
    string locToSub = "Please enter a location to subscribe";
    strcpy(sendingBuff, locToSub.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer

    memset(receivingBuff, 0, MAX);   //might delete it later, already deleted it when calling this function
    read(new_socket, receivingBuff, (size_t)MAX);  //lee lo que acabo de escribir el client

    string location = receivingBuff;

    u.subscribe(location);

    memset(sendingBuff, 0, MAX);
    locToSub = "Subscribed successfully";
    strcpy(sendingBuff, locToSub.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
    optionsWhenLoggedIn();
}


void Server::unsubscribe() {
    memset(sendingBuff, 0, MAX);
    string showLocations = u.seeLocations();
    strcpy(sendingBuff, showLocations.c_str());
    write(new_socket, sendingBuff, (int)MAX);

    memset(sendingBuff, 0, MAX);
    string locToSub = "Please enter a location to unsubscribe";
    strcpy(sendingBuff, locToSub.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer

    memset(receivingBuff, 0, MAX);   //might delete it later, already deleted it when calling this function
    read(new_socket, receivingBuff, (size_t)MAX);  //lee lo que acabo de escribir el client

    string location = receivingBuff;
    if(u.unsubscribe(location)){
        memset(sendingBuff, 0, MAX);
        locToSub = "Unsubscribed successfully";
        strcpy(sendingBuff, locToSub.c_str());
        write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
        optionsWhenLoggedIn();
    }else{
        memset(sendingBuff, 0, MAX);
        locToSub = "Could not find the location";
        strcpy(sendingBuff, locToSub.c_str());
        write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
        optionsWhenLoggedIn();
    }
}

void Server::seeLocations(){
    memset(sendingBuff, 0, MAX);
    string locations = u.seeLocations();
    strcpy(sendingBuff, locations.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
    optionsWhenLoggedIn();

}

void Server::notImplemented() {
    memset(sendingBuff, 0, MAX);
    string notImplemented = "Not implemented for this part of the project";
    strcpy(sendingBuff, notImplemented.c_str());
    write(new_socket, sendingBuff, (int)MAX);  //enviando el buffer
    optionsWhenLoggedIn();
}
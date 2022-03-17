#include "Server.hpp"

Server::Server() {
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

    std::thread threads[numThreads];
    //cout << "Server started." << endl << endl;
    //cout << "Server ready." << endl << endl;

    while(true) {

        if(usersActive < numThreads) {
            printf("Waiting for incoming connection...\n");
            if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrLen)) < 0) {
                perror("In accept");
                exit(EXIT_FAILURE);
            }

            cout << "Connection accepted" << endl;
            //struct newUser* newUserr = (struct newUser*)malloc(sizeof(struct newUser));
            //newUserr->id = usersActive;
            //newUserr->new_socket = new_socket;
            //threads[usersActive] = std::thread(handleNewClient, newUserr);
            cout << "Handler assigned" << endl;

            mainMenu();
            while(leave == false && logedIn == false){
                memset(receivingBuff, 0, MAX);
                read(new_socket, receivingBuff, (size_t)MAX);
                if(strcmp(receivingBuff, "exit") == 0){
                    close(new_socket);
                    exit(EXIT_SUCCESS);
                }
                if(strcmp(receivingBuff, "1") == 0){
                    if(Login()){
                        logedIn = true;
                        optionsWhenLoggedIn();
                    }
                }
                if(strcmp(receivingBuff, "2") == 0){
                    Register();
                    mainMenu();
                }
            }




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
        memset(sendingBuff, 0, MAX);
        string loggedIn = "Successfully Logged In";
        strcpy(sendingBuff, loggedIn.c_str());
        write(new_socket, sendingBuff, (int)MAX);
        return true;
    }else{
        return false;
    }
    /*cout << " Username:" << endl;
    cin >> username;
    cout << endl << endl;

    cout << " Password" << endl;
    cin >> password;

    string uName, pWord;
    ifstream usersFile;
    usersFile.open("users.txt");
    if (usersFile.is_open())
    {
        usersFile >> uName >> pWord;
        while (!usersFile.eof()) { // keep reading until end-of-file
            if(uName == username && pWord == password){
                cout << "Successfully logged in" << endl;
                //User user = new User (username, password);
                //optionsWhenLoggedIn(password);
            }else{
                cout << "Could not find the account, please register if you did not have done so or try again" << endl;
            }
            //cout << "Username: " << uName << "Password: " << pWord << endl;
            usersFile >> uName >> pWord; // sets EOF flag if no value found
        }
        usersFile.close();
    }*/

}


void Server::Register(){
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
    //cout << "Successfully Registered "<< endl;
    /*string username, password;

    cout << " Username:" << endl;
    cin >> username;
    cout << endl;

    cout << " Password" << endl;
    cin >> password;

    ofstream usersFile;
    usersFile.open("users.txt", fstream::app);
    if (usersFile.is_open())
    {
        usersFile << username << "\t" << password << endl;
        usersFile.close();
    }
    else cout << "Unable to open file";


    cout << "Successfully Registered "<< endl;*/

}



void Server::handleNewClient(struct newUser* user) {
    lock.lock();
    usersActive++;
    lock.unlock();

    struct newUser* newUser = user;
    int id_ = newUser->id;
    int sock = newUser->new_socket;
    char buffer[1280] = {0};

    while(true){
        if(read(sock, buffer, 30000) > 0){
            //std::string packet = packet_util(buffer).http_response();
            printf("THREAD: %d\n", id_);
            //write(sock, (char*)packet.c_str(), (int)packet.size());
            printf("---------- MESSAGE SENT -----------\n");
        }
    }
    close(sock);

    lock.lock();
    usersActive--;
    lock.unlock();
    std::terminate();
}

void Server::mainMenu() {
    memset(sendingBuff, 0, MAX);
    string firstOptions = "Welcome!\n  Press 1 to Login\n  Press 2 to Register\n  Type \'exit\' to Quit\n";
    strcpy(sendingBuff, firstOptions.c_str());
    write(new_socket, sendingBuff, (int)MAX);
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
//            }else{
//                cout << "Could not find the account, please register if you did not have done so or try again" << endl;
//            }
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

    /*cout << " 1. Subscribe to a location" << endl;
    cout << " 2. Unsubscribe to a location" << endl;
    cout << " 3. See the online users" << endl;
    cout << " 4. Send a message to a user" << endl;
    cout << " 5. Send a group message to a location" << endl;
    cout << " 6. See all the locations that the client has subscribed to" << endl;
    cout << " 7. See the last 10 message received" << endl;
    cout << " 8. Change password" << endl;
    cout << " 9. Quit" << endl;*/

    string choice;
    cin >> choice;
    int choiceParsed = stoi(choice);
    //while(choiceParsed > 0 || choiceParsed < 10){
    switch(choiceParsed){
        case 1:
            cout << "option 1 chosen" << endl;
            break;
        case 2:
            cout << "option 2 chosen" << endl;
            break;
        case 3:
            cout << "option 3 chosen" << endl;
            break;
        case 4:
            cout << "option 4 chosen" << endl;
            break;
        case 5:
            cout << "option 5 chosen" << endl;
            break;
        case 6:
            cout << "option 6 chosen" << endl;
            break;
        case 7:
            cout << "option 7 chosen" << endl;
            break;
        case 8:
            //cout << "option 8 chosen" << endl;
            //changePassword(password);
            break;
        case 9:
            exit(EXIT_SUCCESS);
            //break;
        default:
            //while(choiceParsed < 0 && choiceParsed > 9){
            cout << "invalid choice, please enter a valid choice" << endl;
            cin >> choiceParsed;
            //}

            //continue;
    }
}

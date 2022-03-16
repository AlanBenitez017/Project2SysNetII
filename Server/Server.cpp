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

            memset(sendingBuff, 0, MAX);
            string firstOptions = "Welcome!\n  Press 1 to Login\n  Press 2 to Register\n  Type \'exit\' to Quit\n";
            strcpy(sendingBuff, firstOptions.c_str());
            write(new_socket, sendingBuff, (int)MAX);
            while(leave == false && logedIn == false){
                memset(receivingBuff, 0, MAX);
                read(new_socket, receivingBuff, (size_t)MAX);
                if(strcmp(receivingBuff, "exit") == 0){
                    close(new_socket);
                    exit(EXIT_SUCCESS);
                }
                if(strcmp(receivingBuff, "1") == 0){
                    Login();
                }
                if(strcmp(receivingBuff, "2") == 0){
                    Register();
                }
            }


            /*char * request = new char [400];
            char * pointer = request;
            int numBytes = 0;
            int max = 400;
            int length = 0;
            string received;

            while((numBytes = read(new_socket,pointer,max)) > 0) {
                pointer += numBytes;
                max -= numBytes;
                length += numBytes;
            }

            if(numBytes < 0){
                cout << "Error reading"<< endl;
            }

            received = request;

            cout << "Request from client\n\n" + received +" \n\nend of what was received\n" << endl;*/

            //handleResponses();
            //memset(receivingBuff, '\0', sizeof sendingBuff);
//            read(server_fd, receivingBuff, 30000);//message sent form client is in the buffer
//            cout << receivingBuff << "hola" << endl;
//            string r;
//            r += receivingBuff;
//            cout << r << endl;
            /*if(received.find("register")!=string::npos){
                string delimiter = " ";
                vector<string> words;
                size_t pos = 0;
                while ((pos = received.find(delimiter)) != string::npos) {
                    words.push_back(received.substr(0, pos));
                    received.erase(0, pos + delimiter.length());
                }
                string username = words.at(2);
                string password = words.at(4);
                users[username] = password;//.insert(username, password);
                ofstream usersFile;
                usersFile.open("users.txt", fstream::app);
                if (usersFile.is_open())
                {
                    usersFile << username << "\t" << password << endl;
                    usersFile.close();
                }
                else cout << "Unable to open file";

                memset(sendingBuff, '\0', sizeof sendingBuff);
                string sendToServer = "Successfully Registered";
                strcpy(sendingBuff, sendToServer.c_str());
                cout << sendingBuff << "probando" << endl;
                write(server_fd, sendingBuff, sizeof sendingBuff);

            }

            if(received.find("login")!=string::npos){
                string delimiter = " ";
                vector<string> words;
                size_t pos = 0;
                while ((pos = received.find(delimiter)) != string::npos) {
                    words.push_back(received.substr(0, pos));
                    received.erase(0, pos + delimiter.length());
                }
                string username = words.at(2);
                string password = words.at(4);
                bool found = false;
                map<string, string>::iterator it;
                for (it = users.begin(); it != users.end(); it++)
                {
                    string uName = it->first;
                    string pWord = it->second;
                    if(uName == username && pWord == password){
                        found = true;
                        //cout << "Successfully logged in" << endl;
                        //User user = new User (username, password);
                        //optionsWhenLoggedIn(password);
                    }else{
                        found = false;
                        //cout << "Could not find the account, please register if you did not have done so or try again" << endl;
                    }
                    //std::cout << it->first    // string (key)
                    //          << ':'
                    //          << it->second   // string's value
                    //          << std::endl;
                }
                if(found){
                    cout << "Successfully logged in" << endl;
                }else{
                    cout << "Could not find the account, please register if you did not have done so or try again" << endl;
                }

                memset(sendingBuff, '\0', sizeof sendingBuff);
                string sendToServer = "Successfully logged in";
                strcpy(sendingBuff, sendToServer.c_str());
                write(server_fd, sendingBuff, sizeof sendingBuff);


            }*/
            //User user = new User()
            //Login();

        }
    }
}

void Server::Login() {

    string username, password;
    memset(sendingBuff, 0, MAX);
    string uName = " Username:\n";
    strcpy(sendingBuff, uName.c_str());
    write(new_socket, sendingBuff, (int)MAX);
    cin.getline(receivingBuff, MAX);
    read(new_socket, receivingBuff, (size_t)MAX);
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
    write(new_socket, sendingBuff, (int)MAX);
    cin.getline(receivingBuff, MAX);
    read(new_socket, receivingBuff, (size_t)MAX);

    memset(receivingBuff, 0, MAX);
    memset(sendingBuff, 0, MAX);
    string pWord = " Password:\n";
    strcpy(sendingBuff, uName.c_str());
    write(new_socket, sendingBuff, (int)MAX);
    cin.getline(receivingBuff, MAX);
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

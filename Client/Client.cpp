#include "Client.hpp"

Client::Client() {


    //bind to appropriate port

    std::string ipAddress;
    cout << "Enter hostname: ";
    cin >> ipAddress;
    if(ipAddress == "localhost")
        ipAddress = "127.0.0.1";

    if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Could not make socket !!!");
        exit(EXIT_FAILURE);
    } else{
        cout << "Socket created" << endl;
    }

    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = inet_addr((char*)ipAddress.c_str());
    //bzero(&address.sin_zero, 0);

    if(connect(client_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("Failed to bind !!!");
        close(client_fd);
        exit(EXIT_FAILURE);
    } else{
        cout << "localhost resolved to 127.0.0.1" << endl << "Connected" << endl << endl;
    }

    //if(fork() == 0){
        //cout << "In forked process" << endl;
        //cout << "A client has connected" << endl;
    memset(sendingBuff, '\0', sizeof sendingBuff);
    memset(receivingBuff, '\0', sizeof receivingBuff);

    read(client_fd,receivingBuff, (size_t) MAX);
    cout << receivingBuff << endl;
    //memset(sendingBuff,0,MAX_LEN);
    cin.getline(sendingBuff, MAX);
    write(client_fd, sendingBuff, (size_t)MAX);

}

#include "Client.hpp"

void sendMsg(int client_fd);
void receiveMsg(int client_fd);

int main(){

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

    thread t1(receiveMsg, client_fd);
    thread t2(sendMsg, client_fd);

    threadReceiving = move(t1);
    threadSending = move(t2);


    if (threadReceiving.joinable())
        threadReceiving.join();

    if (threadSending.joinable())
        threadSending.join();


    return 0;
}

void receiveMsg(int client_fd) {
    while(1){
        memset(receivingBuff, 0, MAX);
        cin.getline(receivingBuff, MAX);
        write(client_fd, receivingBuff, (size_t)MAX);
        if(strcmp(receivingBuff, "exit") == 0){
            exitClient = true;
            threadReceiving.detach();
            close(client_fd);
            return;
        }
    }
}

void sendMsg(int client_fd) {
    while(1){
        if(exitClient){
            threadSending.detach();
            return;
        }
        //eraseText(MAX);
        memset(sendingBuff, 0, MAX);
        int bytesRecv = read(client_fd, sendingBuff, (size_t)MAX);
        if(bytesRecv <= 0){
            continue;
        }
        cout << sendingBuff << endl;
        fflush(stdout);
    }
}
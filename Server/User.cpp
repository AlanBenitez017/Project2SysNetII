#include "User.hpp"

#include <utility>

User::User(string username, string password) {
    this->username = std::move(username);
    this->password = std::move(password);
}

void User::optionsWhenLoggedIn() {
    cout << " 1. Subscribe to a location" << endl;
    cout << " 2. Unsubscribe to a location" << endl;
    cout << " 3. See the online users" << endl;
    cout << " 4. Send a message to a user" << endl;
    cout << " 5. Send a group message to a location" << endl;
    cout << " 6. See all the locations that the client has subscribed to" << endl;
    cout << " 7. See the last 10 message received" << endl;
    cout << " 8. Change password" << endl;
    cout << " 9. Quit" << endl;

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
void User::Login() {

    string username, password;
    cout << " Username:" << endl;
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
    }

}

void User::Register(){
    string username, password;
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


    cout << "Successfully Registered "<< endl;

}


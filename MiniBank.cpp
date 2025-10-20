#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

list<string> MyUsername = {"babek"};
list<string> MyPassword = {"2525"};
list<double> myAmountMoney = {100};
int WrongCounter = 3;
double ExtractMoney;
double InputMoney;
double extract_result;
double input_result;
bool usernameTF, passwordTF;
bool launcherTF;
bool LaunchPeriod = true;
string NewUsername;
string NewPassword;

class SecurityPIN {
public:
    bool verifyPIN() {
        int pin;
        int realPIN = rand() % 9000 + 1000;
        cout << "---------------------------------" << endl;
        cout << "Your PIN: " << realPIN << endl;
        cout << "---------------------------------" << endl;
        cout << "Enter your 4-digit PIN: ";
        cin >> pin;
        if(pin == realPIN) {
            cout << "PIN accepted" << endl;
            cout << "---------------------------------" << endl;
            return true;
        } else {
            cout << "Incorrect PIN" << endl;
            cout << "---------------------------------" << endl;
            return false;
        }
    }
} pinCheck;

class CheckerClass {
public:
    bool passwordChecker(string password){
        return password == MyPassword.back();
    }

    bool usernameChecker(string username){
        return username == MyUsername.back();
    }
};

class MiniBankProgram {
public:

    void LoadData() {
        ifstream file("demo.txt");
        if (file.is_open()) {
            string savedUsername, savedPassword;
            double savedBalance;
            file >> savedUsername >> savedPassword >> savedBalance;
            if (!file.fail()) {
                MyUsername.clear();
                MyPassword.clear();
                myAmountMoney.clear();
                MyUsername.push_back(savedUsername);
                MyPassword.push_back(savedPassword);
                myAmountMoney.push_back(savedBalance);
            }
            file.close();
        }
    }

    void SaveData() {
        ofstream file("demo.txt");
        if (file.is_open()) {
            file << MyUsername.back() << " " << MyPassword.back() << " " << myAmountMoney.back();
            file.close();
        }
    }

    void LaunchProgram(bool operationNumber){
        if(operationNumber){
            cout << "------------------------------------" << endl;
            cout << "Launch Program..." << endl;
            int InputYourOperation;
            cout << "0 - Exit Program" << "\n" << "1 - Show My Balance" << "\n" << "2 - Extract Money" 
                 << "\n" << "3 - Input Money" << "\n" << "4 - Info" << "\n" << "5 - Change Your Info" << endl;
            while(LaunchPeriod){
                cout << "Choose a operation: ";
                cin >> InputYourOperation;
                switch(InputYourOperation){
                    case 0:
                        cout << "Saved Your Balance. Goodbye..." << endl;
                        SaveData();
                        LaunchPeriod = false;
                        break;
                    case 1:
                        cout << "------------------------------------" << endl;
                        cout << "Your Balance: " << myAmountMoney.back() << "$" << endl;
                        cout << "------------------------------------" << endl;
                        break;
                    case 2:
                        if (!pinCheck.verifyPIN()) {
                            cout << "Access Denied." << endl;
                            break;
                        }
                        cout << "Please, Enter Money Amount: ";
                        cin >> ExtractMoney;
                        if(myAmountMoney.back() >= ExtractMoney){
                            extract_result = myAmountMoney.back() - ExtractMoney;
                            myAmountMoney.push_back(extract_result);
                            SaveData();
                            cout << "Money extracted successfully! Your new balance: " << extract_result << "$" << endl;
                        }else{
                            cout << "Not enough money!" << endl;
                        }
                        break;
                    case 3:
                        if (!pinCheck.verifyPIN()) {
                            cout << "Access Denied." << endl;
                            break;
                        }
                        cout << "Please, Enter Money Amount: ";
                        cin >> InputMoney;
                        input_result = myAmountMoney.back() + InputMoney;
                        myAmountMoney.push_back(input_result);
                        SaveData();
                        cout << "Money inputed successfully! Your new balance: " << input_result << "$" << endl;
                        break;
                    case 4:
                        cout << "1 - My Username" << "\n" << "2 - My Password" << endl;
                        int InfoInputNumber;
                        cout << "Please, Enter Operation Number: ";
                        cin >> InfoInputNumber;
                        switch(InfoInputNumber){
                            case 1:
                                cout << "Your username: " << MyUsername.back() << endl;
                                break;
                            case 2:
                                if (!pinCheck.verifyPIN()) {
                                    cout << "Access Denied." << endl;
                                    break;
                                } else {
                                    cout << "Your password: " << MyPassword.back() << endl;
                                }
                                break;
                        }
                        break;
                    case 5:
                        int InputChangeNumber;
                        cout << "1 - Change Username" << "\n" << "2 - Change Password" << endl;
                        cout << "Enter Operation Number: ";
                        cin >> InputChangeNumber;
                        switch(InputChangeNumber){
                            case 1:
                                cout << "Enter new username: ";
                                cin >> NewUsername;
                                MyUsername.clear();
                                MyUsername.push_back(NewUsername);
                                SaveData();
                                cout << "Username changed successfully!" << endl;
                                break;
                            case 2:
                                cout <<  "Enter new password: ";
                                cin >> NewPassword;
                                MyPassword.clear();
                                MyPassword.push_back(NewPassword);
                                SaveData();
                                cout << "Password changed successfully and saved!" << endl;
                                break;
                            default:
                                cout << "ERROR!" << endl;
                                break;
                        }
                        break;
                    default:
                        cout << "Invalid operation!" << endl;
                        break;
                }
            }
        } else {
            cout << "------------------------------------" << endl;
            cout << "ERROR, Not Launch Program!" << endl;
        }
    }

    void systemLogin(string FuncUsername){
        if(usernameTF && passwordTF){
            cout << "Hello, " << FuncUsername << endl;
            launcherTF = true;
            LaunchProgram(launcherTF);
        }else{
            cout << "Username or Password is wrong!" << endl;
            launcherTF = false;
            LaunchProgram(launcherTF);
            WrongCounter--;
        }
    }
};

int main(){
    srand(time(0));
    MiniBankProgram minibank;
    CheckerClass checkInfo;
    minibank.LoadData();

    string usernameInput, passwordInput;
    bool period = true;

    while(period){
        if(WrongCounter > 0){
            cout << "Enter Username: ";
            cin >> usernameInput;
            cout << "Enter Password: ";
            cin >> passwordInput;

            usernameTF = checkInfo.usernameChecker(usernameInput);
            passwordTF = checkInfo.passwordChecker(passwordInput);

            if(usernameTF && passwordTF){
                minibank.systemLogin(usernameInput);
                break;
            }else{
                WrongCounter--;
                cout << "Wrong! Attempts left: " << WrongCounter << endl;
                if(WrongCounter == 0){
                    cout << "Max Attempt Reached! Program locked." << endl;
                    period = false;
                }
            }
        }
    }
}

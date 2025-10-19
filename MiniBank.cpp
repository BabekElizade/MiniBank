#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
using namespace std;
list<double> myAmountMoney = {100};
int checkCounter = 0;
int WrongCounter = 3;
double ExtractMoney;
double InputMoney;
double extract_result;
double input_result;
bool usernameTF, passwordTF;
bool launcherTF;
bool LaunchPeriod = true; 

bool passwordChecker(string password){
    if(password == "babek2008"){
        checkCounter++;
        passwordTF = true;
    }else{
        passwordTF = false;
    }
        return passwordTF;
}

bool usernameChecker(string username){
    if(username == "babekelizade"){
        checkCounter++;
        usernameTF = true;
    }else{
        usernameTF = false;
    }
        return usernameTF;

}

void LoadMoneyAmount() {
    ifstream file("demo.txt");
    if (file.is_open()) {
        double savedBalance;
        file >> savedBalance;
        if (!file.fail()) {
            myAmountMoney.clear();
            myAmountMoney.push_back(savedBalance);
        }
        file.close();
    }
}

void SaveMoneyAmount() {
    ofstream file("demo.txt");
    if (file.is_open()) {
        file << myAmountMoney.back();
        file.close();
    }
}

void LaunchProgram(bool operationNumber){
    if(operationNumber){
        cout << "------------------------------------" << endl;
        cout << "Launch Program..." << endl;
        int InputYourOperation;
        cout << "0 - Exit Program" << "\n" << "1 - Show My Balance" << "\n" << "2 - Extract Amount" << "\n" << "3 - Input Money" << endl;
        while(LaunchPeriod){
            cout << "Choose a operation: ";
            cin >> InputYourOperation;
            switch(InputYourOperation){
                case 0:
                    cout << "Saved Your Money. Goodbye..." << endl;
                    SaveMoneyAmount();
                    LaunchPeriod = false;
                    break;
                case 1:
                    cout << "------------------------------------" << endl;
                    cout << "Your Balance: " << myAmountMoney.back() << "$" << endl;
                    cout << "------------------------------------" << endl;
                    break;
                case 2:
                    cout << "Please, Enter Money Amount: ";
                    cin >> ExtractMoney;
                    if(myAmountMoney.back() >= ExtractMoney){
                        extract_result = myAmountMoney.back() - ExtractMoney;
                        myAmountMoney.push_back(extract_result);
                        cout << "Money extracted successfully! Your new balance: " << extract_result << "$" << endl;
                    }else{
                        cout << "Not enough money!" << endl;
                    }
                    break;
                case 3:
                    cout << "Please, Enter Money Amount: ";
                    cin >> InputMoney;
                    input_result = myAmountMoney.back() + InputMoney;
                    myAmountMoney.push_back(input_result);
                    cout << "Money inputed successfully! Your new balance: " << input_result << "$" << endl;
                    break;
                default:
                    cout << "ERROR!" << endl;
                    break;
            }
            if(InputYourOperation == 0){
                    break;
                }
        }
    }else{
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
            cout << "";
        }
        
}


int main(){
    LoadMoneyAmount();

    string usernameInput, passwordInput;
    bool period = true;
while(period){
    if(WrongCounter > 0){
    cout << "Enter Username: ";
    cin >> usernameInput;
    cout << "Enter Password: ";
    cin >> passwordInput;

    usernameChecker(usernameInput);
    passwordChecker(passwordInput);

    if(usernameTF && passwordTF){
        systemLogin(usernameInput);
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
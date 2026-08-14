#include "Screens/UserDashboard/clsUserLogin.h"
#include "Core/global.h"
#include "Lib/clsInputValidate.h"
#include "Screens/UserDashboard/clsUserDashboard.h"
#include <cstdlib>
#include <iostream>
using namespace std;

bool clsUserLogin::dataleaded = false;

// print header Screen
void clsUserLogin::_HeaderScreen() {
    system("clear");
    PrintHeaderScreen("USER LOGIN", "🔏", Colors::Blue, false, 66);
    cout << "\n\n\n";
}

// func to lead data from file
void clsUserLogin::_LoadData() {
    // load data from files
    if (!dataleaded) {
        // load Users from file
        clsUser::LoadUsersFromFile();
    }
}

// login helper
bool clsUserLogin::_login() {
    // load data from files
    _LoadData();

    string username, password;
    bool CheckLogin = false;
    short TryLimit = 3;
    do {
        if (CheckLogin) {
            // print header Screen
            _HeaderScreen();
            --TryLimit;
            cout << Colors::GetRed() << " [ username or password is incorrect ]" << Colors::RESET() << endl;
            cout << Colors::GetBoldRed() << " [ You have only (" << TryLimit << ") attempts left ]\n" << Colors::RESET() << endl;
        }

        // Check Failed login limit
        if (TryLimit == 0) {
            cout << Colors::GetRed() << " ⊗ Failed to login ☹️" << Colors::RESET() << endl;
            return false;
        }

        // Read username and password
        username = clsInputValidate::ReadString(" ⊙ username : ");
        password = clsInputValidate::ReadString(" ⊙ password : ");
        // Search for user
        CurrUser = clsUser::Find(username, password);
        // Check if its found
        CheckLogin = CurrUser.isEmpty();
    } while (CheckLogin);

    return true;
}

bool clsUserLogin::UserLogin() {
    // print header Screen
    _HeaderScreen();

    if (_login()) {
        // after login is succes we go to admin dashboard
        clsUserDashboard::UserDashboardScreen();
        return true;
    }

    return false;
}

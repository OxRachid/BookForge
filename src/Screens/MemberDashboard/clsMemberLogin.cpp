#include "Screens/MemberDashboard/clsMemberLogin.h"
#include "Core/clsMember.h"
#include "Core/global.h"
#include "Lib/clsInputValidate.h"
#include "Screens/MemberDashboard/clsMemberDashboard.h"
#include <cstdlib>
#include <iostream>
using namespace std;

bool clsMemberLogin::dataleaded = false;

// func to lead data from file
void clsMemberLogin::_LoadData() {
    // load data from files
    if (!dataleaded) {
        // load Members from file
        clsMember::LoadMembersFromFile();
    }
}

// print header Screen
void clsMemberLogin::_HeaderScreen() {
    system("clear");
    PrintHeaderScreen("MEMBER LOGIN", "🔏", Colors::Cyan, false, 66);
    cout << "\n\n\n";
}
// login helper
bool clsMemberLogin::_login() {
    // lead members from file
    _LoadData();

    string accountnumber, password;
    bool checklogin = false;
    short TryLimit = 3;
    do {
        if (checklogin) {
            // print header Screen
            _HeaderScreen();
            --TryLimit;
            cout << Colors::GetRed() << " [ accountnumber or password is incorrect ]" << Colors::RESET() << endl;
            cout << Colors::GetBoldRed() << " [ You have only (" << TryLimit << ") attempts left ]\n" << Colors::RESET() << endl;
        }

        // Check Failed login limit
        if (TryLimit == 0) {
            cout << Colors::GetRed() << " ⊗ Failed to login ☹️" << Colors::RESET() << endl;
            return false;
        }

        // Read accountnumber and password
        accountnumber = clsInputValidate::ReadString(" * Account Number : ");
        password = clsInputValidate::ReadString(" * Password : ");
        // search for MEMBER
        CurrMember = clsMember::Find(accountnumber, password);
        // check if its found
        checklogin = CurrMember.isEmpty();
    } while (checklogin);

    // Check if Account is Blocked
    if (CurrMember.GetAccountStatus() == clsMember::eAccountStatus::BLOCKED) {
        cout << Colors::GetRed() << " ⊗ Your Account was Blocked, please contact your admin ..." << Colors::RESET() << endl;
        return false;
    }

    // Reset CurrUser
    CurrUser = clsUser::Find("");
    return true;
}

// Login
bool clsMemberLogin::MemberLogin() {
    // print header
    _HeaderScreen();

    if (_login()) {

        clsMemberDashboard::MemberDashboardScreen();
        return true;
    }

    return false;
}

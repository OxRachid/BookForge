#include "Screens/UserDashboard/Members/clsAddNewMember.h"
#include "Core/clsMember.h"
#include "Lib/clsInputValidate.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// print member data
void clsAddNewMember::_PrintMemberData(clsMember member) {
    cout << endl;
    PrintHeaderScreen("[Member Data]", "👤", Colors::Blue, false, 41);
    cout << Colors::GetBlue() << left << setw(20) << setfill(' ') << " AccountNumber" << " : " << member.GetAccountNumber() << endl;
    cout << left << setw(20) << " Firstname" << " : " << member.GetFirstName() << endl;
    cout << left << setw(20) << " Lastname" << " : " << member.GetLastName() << endl;
    cout << left << setw(20) << " Email" << " : " << member.GetEmail() << endl;
    cout << left << setw(20) << " Phone" << " : " << member.GetPhone() << endl;
    cout << left << setw(20) << " Role" << " : " << member.MemberRoleToString() << endl;
    cout << left << setw(20) << " Password" << " : " << member.GetPassword() << endl;
    cout << left << setw(20) << " Borrowed Books" << " : " << member.GetTotalBorrowedBooks() << endl;
    cout << left << setw(20) << " Violations" << " : " << member.GetViolations() << endl;
    cout << left << setw(20) << " Account Created on" << " : " << clsDate::ConvertDateToString(member.GetAccountCreated_on()) << endl;
    cout << left << setw(20) << " Account Status" << " : " << member.AccountStatusToString() << endl;
    cout << setw(41) << setfill('-') << "" << Colors::RESET() << endl;
}

// Get Unique AccountNumber of member
string clsAddNewMember::_GetUniqueAccountNumber() {
    PrintHeaderScreen("Read Member Data", "👤", Colors::Magenta, false, 54);
    string AccountNumber;
    bool isExist = false;
    do {
        if (isExist) {
            cout << Colors::GetRed() << " [ This AccountNumber is already Exist ]" << Colors::RESET() << endl;
        }

        AccountNumber = clsInputValidate::ReadString(" ⊙ Enter AccountNumber : ");
        isExist = clsMember::isMemberExist(AccountNumber);
    } while (isExist);
    return AccountNumber;
}

// Get Role Choice
short clsAddNewMember::_GetRoleChoice() {
    return clsInputValidate::Readnumberbetween(1, 2, " ⊙ What's Your Role [1] Student [2] Teacher ? ");
}

// Read Memeber obj data
void clsAddNewMember::_ReadMemberData(clsMember &member) {
    member.SetFirstName(clsInputValidate::ReadString(" ⊙ Enter Firstname : "));
    member.SetLastName(clsInputValidate::ReadString(" ⊙ Enter Lastname : "));
    member.SetEmail(clsInputValidate::ReadString(" ⊙ Enter Email : "));
    member.SetPhone(clsInputValidate::ReadString(" ⊙ Enter Phone : "));
    member.SetRole(_GetRoleChoice());
    member.SetPassword(clsInputValidate::ReadStringGreaterThan(5, " ⊙ Enter Password : "));
}

// Get member obj to Add
clsMember clsAddNewMember::_GetAddObjMode() {
    string AccountNumber = _GetUniqueAccountNumber();
    return clsMember::GetAddNewMemberObj(AccountNumber);
}

// Add new Member screen
void clsAddNewMember::AddNewMemberScreen() {
    PrintHeaderScreen("ADD MEMBER SCREEN", "+👤", Colors::Yellow);
    cout << "\n\n\n";

    // Get Member Obj to Add
    clsMember NewMember = _GetAddObjMode();
    // Read Member obj Data
    _ReadMemberData(NewMember);
    // Save the new member to file
    clsMember::enSaveMode Result = NewMember.save();
    switch (Result) {
        case clsMember::enSaveMode::SAVE_SUCCESS: {
            _PrintMemberData(NewMember);
            cout << Colors::GetGreen() << " [ Member Added Succesfully ]" << Colors::RESET() << endl;
            break;
        }
        case clsMember::enSaveMode::SAVE_FAILED: {
            cout << Colors::GetRed() << " [ The Proccess Failed ]" << Colors::RESET() << endl;
            break;
        }
        default:
            break;
    }
}

#include "Screens/UserDashboard/System/clsUpdateSystem.h"
#include "Core/clsBook.h"
#include "Core/clsMember.h"
#include "Core/clsTransaction.h"
#include "Lib/clsInputValidate.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

// reupload data from file
void clsUpdateSystem::_RuploadData() {
    cout << "\n Process start ..." << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
    // reupload books
    clsBook::LoadBooksFromFile();
    cout << Colors::GetGreen() << "\n  Books is up to date " << Colors::RESET() << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
    // reupload members
    clsMember::LoadMembersFromFile();
    cout << Colors::GetGreen() << "  Members is up to date " << Colors::RESET() << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
    // reupload Transactions
    clsTransaction::LoadTransactions();
    cout << Colors::GetGreen() << "  Transactions is up to date " << Colors::RESET() << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
    // reupload users
    clsUser::LoadUsersFromFile();
    cout << Colors::GetGreen() << "  Users is up to date " << Colors::RESET() << endl;
    this_thread::sleep_for(chrono::milliseconds(400));
}

// request denied
void clsUpdateSystem::_CancelRequest(clsTransaction &TargetTrans) {
    // Get TargetMember and TargetBook to update thier data
    clsMember TargetMember = clsMember::Find(TargetTrans.GetAccountNumber());
    clsBook TargetBook = clsBook::Find(TargetTrans.GetBookID());
    // update TargetMember and TargetBook and targetTrans after the request is canceled
    // update member data
    TargetMember.ReturnBook(1);
    // update book data
    TargetBook.ReturnBook();
    // update Transaction data
    TargetTrans.RequestCanceled();
}

// check expired requests
void clsUpdateSystem::_CheckExpiredRequests() {
    // Get Transactions list
    vector<clsTransaction> &vTrans = clsTransaction::GetTransactionsList();

    for (clsTransaction &T : vTrans) {
        if (T.GetStatus() == clsTransaction::enTransStatus::PENDING) {
            if (!T.isPickupOnTime()) {
                _CancelRequest(T);
            }
        }
    }
}

// update system
void clsUpdateSystem::UpdateSystemScreen() {
    PrintHeaderScreen("UPDATE SYSTEM", "🔅", Colors::Magenta);
    cout << "\n\n";

    if (clsInputValidate::AskUser("\n ⊙ do you wanna update system")) {
        // reupload data from file
        _RuploadData();
        // check expired requests
        _CheckExpiredRequests();
        cout << Colors::GetGreen() << " 󰂠 system is up to date " << Colors::RESET() << endl;
    } else {
        cout << Colors::GetRed() << " [ the process is canceled ]" << Colors::RESET() << endl;
    }
}

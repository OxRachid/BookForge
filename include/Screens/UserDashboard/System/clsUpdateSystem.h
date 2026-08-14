#ifndef CLSUPDATESYSTEM_H
#define CLSUPDATESYSTEM_H

#include "Core/clsTransaction.h"
#include "Screens/clsScreen.h"
class clsUpdateSystem : protected clsScreen {
    private:
        // reupload data from file
        static void _RuploadData();
        // check expired requests
        static void _CheckExpiredRequests();
        // cancel request
        static void _CancelRequest(clsTransaction &TargetTrans);

    public:
        // update system
        static void UpdateSystemScreen();
};

#endif // !CLSUPDATESYSTEM_H

#include "mainwindow.h"
#include <QApplication>
#include "cstagecontroller.h"
#include "hardwareserialui.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto pHardwareSerialUI = make_shared<HardwareSerialUI>();

    auto pMainWind = make_shared<MainWindow>();

    auto controller = make_shared<CStageController>(std::initializer_list<shared_ptr<IControlInterface>>{pMainWind, pHardwareSerialUI});

    // need to register for UI events, so we're notified
    // of the user doing stuff
    pMainWind->RegisterEventHandler(controller);
    pHardwareSerialUI->RegisterEventHandler(controller);

    pMainWind->show();
    return a.exec();
}

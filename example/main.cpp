#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include "updatergui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    quint16 version[4]{2,5,4,6};
    UpdaterGui *gui = new UpdaterGui(version, QUrl("http://somesite.com/some-path-to-json-file"));
    QObject::connect(gui, &UpdaterGui::newVersionIsUnavailable, [=] {
        QMessageBox::critical(0, QObject::tr("Error!"), QObject::tr("There is no new version of the Program, or url is wrong!"));
        exit(0);
    });
    gui->checkUpdate();

    return a.exec();
}

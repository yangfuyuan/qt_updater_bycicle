#include "updatergui.h"

UpdaterGui::UpdaterGui(quint16 version[], const QUrl &url, QObject *parent)
    : Updater(version, url, parent)
{
    connect(this, &UpdaterGui::newVersionIsAvailable, [=]
            (QMap<QString, QVariant> versionMap)
    {
        UpdaterWindow *window = new UpdaterWindow(versionMap.value("programName").toString(),
                                                  versionMap.value("version").toString(),
                                                  versionMap.value("desc").toList(),
                                                  curVersion());
        connect(window, &UpdaterWindow::downloadUpdate, this, &UpdaterGui::download);        
        connect(this, &Updater::unableToOpenFile, [=] {
            QMessageBox::critical(0, tr("Ошибка!"),
                                 tr("Невозможно открыть файл установки обновления"));
        });
        connect(this, &Updater::setupStarted, window, &UpdaterWindow::close);
        window->show();
    });
}

UpdaterGui::~UpdaterGui()
{
}

void UpdaterGui::download()
{
    QProgressDialog *prog = new QProgressDialog(tr("Скачивание обновления"), tr("Отмена"), 0, 0, 0,
                                                Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint
                                                | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    prog->setWindowModality(Qt::ApplicationModal);
    prog->setAttribute(Qt::WA_DeleteOnClose);
    prog->setWindowTitle(tr("Обновление..."));
    connect(this, &Updater::downloaded, prog, &QProgressDialog::close);
    connect(prog, &QProgressDialog::canceled, this, &Updater::cancelDownload);
    connect(this, &Updater::progress, [=] (qint64 current, qint64 total) {
        prog->setMaximum(total);
        prog->setValue(current);
    });
    prog->show();
    Updater::download();
}

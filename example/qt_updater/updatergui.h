#ifndef UPDATERGUI_H
#define UPDATERGUI_H

#include <QMessageBox>
#include <QProgressDialog>
#include "updaterwindow.h"
#include "updater.h"

/*!
 * \brief The UpdaterGui class
 * Класс отвечающий за создание пользовательского интерфейса для обновления
 */
class UpdaterGui : public Updater
{
    Q_OBJECT
public:
    explicit UpdaterGui(quint16 version[], const QUrl &url, QObject *parent = 0);
    ~UpdaterGui();
signals:
public slots:
    /*!
     * \brief download
     * Вирутальный слот начала скачивания обновления
     */
    void download();
};

#endif // UPDATERGUI_H

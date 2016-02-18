#ifndef UPDATERWINDOW_H
#define UPDATERWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QUrl>
#include <QDialogButtonBox>
#include <QSpacerItem>
#include <QWebView>

/*!
 * \brief The UpdaterWindow class
 * Класс, отрисовывающий пользовательский интерфейс информации об обновлении
 */
class UpdaterWindow : public QWidget
{
    Q_OBJECT
    QWebView *_webInfo;
public:
    explicit UpdaterWindow(const QString &programName, const QString &version, const QUrl &updateText,
                           const QString &curVersion, QWidget *parent = 0);
    ~UpdaterWindow();

signals:
    /*!
     * \brief downloadUpdate
     * Сигнал о запуске скачивания обновления
     */
    void downloadUpdate();

public slots:
};

#endif // UPDATERWINDOW_H

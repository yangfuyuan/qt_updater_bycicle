/**
  Описание пар JSON документа (далее, ключ: значение - описание):

    programName: "Name"         - наименование программы
    version: "1.0.0.0"          - версия программы
    desc: ["some_update_info_1", "some_update_info_2"]  - array с описанием обновлений
    updateDownload: "url"       - url к обновлению
    updateFile: "filename"      - имя файла обновления с расширением

    Пример готового JSON-документа:
    {
        "programName": "Programma",
        "version": "1.0.0.0",
        "desc": ["<h1>Hello world</h1>", "test", "<ul><li>One</li><li>Two</li><li>Three</li></ul>"],
        "updateDownload": "https://some-site.com/cloud/hfhg734jH/download",
        "updateFile": "update.exe"
    }
*/

#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAbstractSocket>
#include <QFile>
#include <QProcess>
#include "downloader.h"

/*!
 * \brief The Updater class
 * Класс, отвечающий за логику обновления
 */
class Updater : public QObject
{
    Q_OBJECT
    QUrl _url;
    QUrl _downloadLink;
    QString _fileName;
    Downloader *_dwn;
    QNetworkAccessManager _manager;
    QNetworkReply *_reply = nullptr;
    QString _curVersion;

    /*!
     * \brief _version
     * Номер версии являтся массивом из 4 цифр.
     * Допускается набор следующих после первой цифры(n) от 0 до 9, где n > 9 ? n = 9 : n
     */
    quint16 _version[4]{0,0,0,0};
protected:
    int fullVersion();
    int strToIntVrs(QString version) { return version.remove(".").toInt(); }
    QString curVersion() { return _curVersion; }
public:
    /*!
     * \brief Updater
     * Конструктор для создания объекта системы проверки обновлений
     * \param version
     * Версия программы для сравнения
     * \param url
     * URL нахождения файла проверки версии
     * \param parent
     * Родитель (если есть)
     */
    explicit Updater(quint16 version[], const QUrl &url, QObject *parent = 0);
    ~Updater();

    /*!
     * \brief checkUpdate
     * Функция для начала проверки обновления
     */
    void checkUpdate();

signals:
    /*!
     * \brief newVersionIsAvailable
     * Сигнал, оповещающий о том, что новая версия доступна
     * \param versionMap
     * Параметр, содержащий в себе информацию о программе (programName, version, desc)
     */
    void newVersionIsAvailable(QMap<QString, QVariant> versionMap);
    /*!
     * \brief newVersionIsUnavailable
     * Сигнал, оповещающий о том, что новой версии нет (или нет связи с Интернетом).
     * Реализуется пользователем самостоятельно.
     */
    void newVersionIsUnavailable();
    /*!
     * \brief downloaded
     * Сигнал, оповещающий об успешном завершении загрузки
     */
    void downloaded();
    /*!
     * \brief canceled
     * Сигнал, оповещающий о том, что загрузка была отменена
     */
    void canceled();
    /*!
     * \brief progress
     * Сигнал, оповещающий о прогрессе скачивания файла
     * \param current
     * Текущая сумма байт
     * \param total
     * Сумма байтов в скачиваемом файле
     */
    void progress(qint64 current, qint64 total);
    /*!
     * \brief unableToOpenFile
     * Сигнал о невозможности открыть скачанный файл
     */
    void unableToOpenFile();
    /*!
     * \brief cancelDownload
     * Сигнал, оповещающий о том, что была подана команда на отмену скачивания
     */
    void cancelDownload();
    /*!
     * \brief setupStarted
     * Сигнал, оповещающий о запуске обновления
     */
    void setupStarted();

private slots:
    /*!
     * \brief startInstall
     * Слот, открывающий скачанный файл для установки и закрывающий программу
     */
    void startInstall();
    /*!
     * \brief checkVersion
     * Слот, проверяющий версию
     * \param reply
     */
    void checkVersion();

public slots:
    /*!
     * \brief download
     * Виртуальный слот для начала загрузки обновления
     */
    virtual void download();
};

#endif // UPDATER_H

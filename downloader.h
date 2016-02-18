#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

/*!
 * \brief The Downloader class
 * Класс, реализующий процесс скачивания обновления
*/
class Downloader : public QObject
{
    Q_OBJECT
    QByteArray _downloadedData;
    QUrl _url;
    QNetworkReply *_reply = nullptr;
    QNetworkAccessManager _manager;
    bool _cancel = false;
public:
    /*!
     * \brief Downloader
     * Конструктор класса
     * \param url
     * Ссылка на скачивание
     * \param parent
     * Родитель (необязательно)
     */
    explicit Downloader(const QUrl &url, QObject *parent = 0);
    ~Downloader();
    QByteArray downloadedData() const { return _downloadedData; }
    /*!
     * \brief download
     * Запуск скачивания обновления
     */
    void download();

signals:
    /*!
     * \brief success
     * Сигнал об успешном завершении скачивания
     */
    void success();
    /*!
     * \brief progress
     * Сигнал о прогрессе скачивания
     * \param current
     * Текущая сумма скачанных байтов
     * \param total
     * Сумма байтов в файле
     */
    void progress(qint64 current, qint64 total);    
    /*!
     * \brief cancel
     * Сигнал об отмене скачивания
     */
    void cancel();
    /*!
     * \brief canceled
     * Сигнал о завершенной отмене скачивания
     */
    void canceled();

private slots:
    /*!
     * \brief fileDownloaded
     * Метод, переводящий ответ в массив и сигналящий о завершении скачивания
     */
    void fileDownloaded();
    /*!
     * \brief cancelReply
     * Метод, реализующий отмену скачивания по каким-то причинам
     */
    void cancelReply();

};

#endif // DOWNLOADER_H

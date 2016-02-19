#include "downloader.h"

Downloader::Downloader(const QUrl &url, QObject *parent) : QObject(parent)
{
    _url = url;
}

Downloader::~Downloader()
{
}

void Downloader::download()
{
    QNetworkRequest request(_url);
    _reply = _manager.get(request);
    connect(this, &Downloader::cancel, this, &Downloader::cancelReply);
    connect(_reply, &QNetworkReply::finished, this, &Downloader::fileDownloaded);
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(cancelReply()));
    connect(_reply, &QNetworkReply::downloadProgress, this, &Downloader::progress);
}

void Downloader::fileDownloaded()
{
    if(_reply->canReadLine() && !_cancel) {
        _downloadedData = _reply->readAll();
        emit success();
    }
    _reply->deleteLater();
}

void Downloader::cancelReply()
{
    if(_reply->isOpen()) {
        _cancel = true;
        _reply->abort();
        _reply->close();
        _reply->deleteLater();
        emit canceled();
    }
}

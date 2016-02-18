#include "updater.h"

Updater::Updater(quint16 version[], const QUrl &url, QObject *parent)
    : QObject(parent)
{
    _url = url;
    for(int i = 0; i < 4; i++) {
        if(i <= 0)
            _version[i] = version[i];
        else
            _version[i] = (version[i] > 9 ? 9 : version[i]);
        _curVersion += QString::number(version[i]) + ".";
    }
    _curVersion.chop(1);
}

Updater::~Updater()
{
}

void Updater::checkUpdate()
{
    _reply = _manager.get(QNetworkRequest(_url));
    connect(_reply, &QNetworkReply::finished, this, &Updater::checkVersion);
}

void Updater::startInstall()
{
    QByteArray arr = _dwn->downloadedData();
    QFile setup(_fileName);
    if (!setup.open(QIODevice::WriteOnly)) {
        emit cancelDownload();
        emit unableToOpenFile();
        return;
    }
    setup.write(arr);
    setup.close();
    QProcess prc;
    prc.startDetached(_fileName, QStringList());
        emit setupStarted();
}

void Updater::checkVersion()
{
    if(_reply->canReadLine()) {
        QJsonDocument doc = QJsonDocument::fromJson(_reply->readAll());
        _reply->deleteLater();
        QJsonObject obj = doc.object();
        QString version = obj.take("version").toString();
        QMap<QString, QVariant> map;
        if(fullVersion() < strToIntVrs(version)) {
            map.insert("programName", obj.take("programName"));
            map.insert("version", version);
            map.insert("desc", obj.take("desc"));

            _downloadLink = QUrl(obj.take("updateDownload").toString());
            _fileName = obj.take("updateFile").toString();

            emit newVersionIsAvailable(map);
            return;
        }
    }
    emit newVersionIsUnavailable();
}

void Updater::download()
{
    _dwn = new Downloader(_downloadLink, this);
    connect(_dwn, &Downloader::success, this, &Updater::downloaded);
    connect(_dwn, &Downloader::success, this, &Updater::startInstall);
    connect(_dwn, &Downloader::progress, this, &Updater::progress);
    connect(this, &Updater::cancelDownload, _dwn, &Downloader::cancel);
    connect(_dwn, &Downloader::canceled, this, &Updater::canceled);
    _dwn->download();
}

int Updater::fullVersion()
{
    QString versionString;
    for(int i = 0; i < 4; i++)
        versionString += QString::number(_version[i]);

    return versionString.toInt();
}

#include "updaterwindow.h"

UpdaterWindow::UpdaterWindow(const QString &programName, const QString &version, const QUrl &updateText,
                             const QString &curVersion, QWidget *parent)
    : QWidget(parent, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    setWindowTitle(tr("Обновление ПО %1").arg(programName));
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);
    setMaximumSize(800, 600);

    /*
     * QWebView страдает утечками памяти типа ChachedResource
     * на некоторых страницах, но только при закрытии главного приложения
    */
    _webInfo = new QWebView(this);
    _webInfo->load(updateText);
    _webInfo->setContextMenuPolicy(Qt::NoContextMenu);
    _webInfo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGroupBox *infoGb = new QGroupBox(tr("Информация об обновлении"), this);
    QVBoxLayout *infoLay = new QVBoxLayout();
    infoGb->setLayout(infoLay);
    QString versionString = tr("Ваша версия <b>%1</b>, доступная версия <b>%2</b>");
    QLabel *infoLabel = new QLabel(versionString.arg(curVersion, version), this);
    infoLay->addWidget(infoLabel);
    infoLay->addWidget(_webInfo);
    infoLay->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Expanding));

    QHBoxLayout *actionsLay = new QHBoxLayout();
    QPushButton *downloadButton = new QPushButton(tr("Скачать и установить"), this);
    QPushButton *closeButton = new QPushButton(tr("Закрыть"), this);
    actionsLay->addWidget(downloadButton);
    actionsLay->addWidget(closeButton);

    layout->addWidget(infoGb);
    layout->addLayout(actionsLay);

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    connect(downloadButton, &QPushButton::clicked, this, &UpdaterWindow::downloadUpdate);
}

UpdaterWindow::~UpdaterWindow()
{
}


#include "mail.h"

Mail::Mail(QWidget *parent)
        : QWidget(parent) {
    lay = new QHBoxLayout(this);

    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);

    setProperty("class", "mail");
    setAttribute(Qt::WA_StyledBackground);

    connect(mail, &ReceiveMail::dataReady, this, &Mail::retrieveData);

    mail->fetchLastMail(4);
    mail->readMail(918);

    //mImap->sendRequest(R"(list "" "*")");
    //mImap->sendRequest("select INBOX");
    //mImap->sendRequest("search all");
    //mImap->sendRequest("fetch 800 all");
    //mImap->sendRequest("select drfts");
}

void Mail::retrieveData(QByteArray data) {
    mData = data;
    qDebug() << data;
}
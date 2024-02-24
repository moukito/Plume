#include "mail.h"

Mail::Mail(QWidget *parent)
        : QWidget(parent) {
    lay = new QHBoxLayout(this);

    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);

    setProperty("class", "mail");
    setAttribute(Qt::WA_StyledBackground);

    QByteArray login{""};
    QByteArray password{""};

    mImap = new ImapConnection(login, password, this);

    connect(mImap, &ImapConnection::accessRead, this, &Mail::test);

    mImap->sendRequest("select INBOX");
}

void Mail::test() {
    qDebug() << mImap->getData();
}
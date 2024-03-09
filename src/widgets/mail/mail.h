#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "ReceiveMail.h"

class Mail : public QWidget {
Q_OBJECT

public:
    explicit Mail(QWidget *parent);

private:
    QHBoxLayout *lay = nullptr;
    QByteArray mLogin{""};
    QByteArray mPassword{""};
    ReceiveMail *mail{new ReceiveMail(mLogin, mPassword, this)};
    QByteArray mData;

    Q_SLOT void retrieveData(QByteArray data);
};
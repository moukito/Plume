//
// Created by theo on 2/24/24.
//

#include "ImapConnection.h"

int ImapConnection::mCode{0};

ImapConnection::ImapConnection(string &login, string &password, QObject *parent) : QObject{parent}, mLogin{login},
                                                                                   mPassword{password} {
    connect(mSocket, SIGNAL(encrypted()), SLOT(loginin()));
    connect(mSocket, SIGNAL(readyRead()), SLOT(readData()));
    connect(mTimer, SIGNAL(timeout()), SLOT(timeIsOut()));

    mSocket->connectToHostEncrypted(mAddress, mPort);

    mTimer->start(5000);
}

void ImapConnection::readData() {
    mData.append(mSocket->readAll());
    if (!(mTimer->isActive())) {
        mTimer->start(10000);
    }
}

QByteArray ImapConnection::code() {
    return QByteArray::number(mCode++);
}

void ImapConnection::timeIsOut() {
    if (mData.isEmpty()) {
        //todo : error
        qDebug() << "time";
    }
}

ImapConnection::string ImapConnection::getData() {
    return mData;
}

void ImapConnection::sendRequest(const QByteArray& request) {
    mData = "";
    mSocket->write(code() + " " + request + "\r\n");
}

bool ImapConnection::isReadyRead() {
    return !mData.isEmpty();
}

void ImapConnection::loginin() {
    mSocket->write(code() + " " + "login " + mLogin + " " + mPassword + "\r\n");
}

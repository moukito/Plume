//
// Created by theo on 2/24/24.
//

#include "ImapConnection.h"

int ImapConnection::mCode{0};

ImapConnection::ImapConnection(string &login, string &password, QObject *parent) : QObject{parent}, mLogin{login},
                                                                                   mPassword{password} {
    connect(mSocket, &QSslSocket::encrypted, this, [=]() {mSocket->write(code() + " " + "login " + mLogin + " " + mPassword + "\r\n");});
    connect(mSocket, &QSslSocket::readyRead, this, &ImapConnection::readData);
    connect(mTimer, &QTimer::timeout, this, &ImapConnection::timeIsOut);

    mSocket->connectToHostEncrypted(mAddress, mPort);

    mTimer->setSingleShot(true);
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
    } else {
        emit accessRead();
        if (!mQueue.empty()) {
            uploadRequest(mQueue.front());
            mQueue.pop();
        }
    }
}

ImapConnection::string ImapConnection::getData() {
    return mData;
}

void ImapConnection::sendRequest(const QByteArray &request) {
    mQueue.push(request);
    if (!mTimer->isActive()) {
        uploadRequest(mQueue.front());
        mQueue.pop();
    }
}

void ImapConnection::uploadRequest(const QByteArray& request) {
    mData = "";
    mSocket->write(code() + " " + request + "\r\n");
}


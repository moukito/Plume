//
// Created by theo on 2/27/24.
//

#include "ReceiveMail.h"

ReceiveMail::ReceiveMail(string &login, string &password, QObject *parent) : QObject(parent),
                                                                             mServer(new ImapConnection(login, password,
                                                                                                        this)) {
    requests.push(request::setup);
    connect(mServer, &ImapConnection::accessRead, this, &ReceiveMail::storeData);
}

ReceiveMail::~ReceiveMail() {
    delete mServer;
}

void ReceiveMail::storeData() {
    mData = mServer->getData();
    qDebug() << mData;
    QByteArray fetch;
    qsizetype start;
    qsizetype end;
    QByteArray first;
    QByteArray last;
    switch (requests.front()) {
        case request::select:
            //mData.contains(mServer->getCode() + " OK");
            mSearchNumber = mData.sliced(2, mData.indexOf("EXISTS") - 3);
            //qDebug() << mSearchNumber;
            break;
        case request::search:
            mData = mData.first(mData.size() - 2);
            start = mData.lastIndexOf("\r\n", -1) - (mSearchNumber.size() * mNumber) - (mNumber - 1);
            end = (mSearchNumber.size() * mNumber) + (mNumber - 1);
            fetch = mData.sliced(start, end);
            //qDebug() << fetch;
            if (mNumber == 1) {
                mServer->sendRequest("fetch " + fetch + " all");
            } else {
                first = fetch.sliced(0, 3);
                last = fetch.sliced(fetch.size() - 3, 3);
                mServer->sendRequest("fetch " + first + ":" + last + " all");
            }
            break;
        case request::fetch:
            emit dataReady(mData);
            break;
        case request::setup:
            //qDebug() << "setup done";
            break;
    }
    requests.pop();
}

void ReceiveMail::fetchLastMail(int number) {
    mNumber = number;
    requests.push(request::select);
    mServer->sendRequest("select INBOX");
    requests.push(request::search);
    mServer->sendRequest("search all");
    requests.push(request::fetch);
}

void ReceiveMail::readMail(int uid) {
    requests.push(request::fetch);
    mServer->sendRequest("fetch " + QByteArray::number(uid) + " BODY");
}
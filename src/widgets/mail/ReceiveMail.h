//
// Created by theo on 2/27/24.
//

#ifndef PLUME_RECEIVEMAIL_H
#define PLUME_RECEIVEMAIL_H


#include "protocol/ImapConnection.h"

class ReceiveMail : public QObject {
Q_OBJECT

    using string = QByteArray;
public:
    ReceiveMail(string &login, string &password, QObject *parent);

    ~ReceiveMail() override;

    void fetchLastMail(int number);

    void readMail(int uid);

    Q_SIGNAL void dataReady(QByteArray data);

private:
    enum class request {
        setup,
        select,
        search,
        fetch,
    };
    string mData{""};
    ImapConnection *mServer;
    std::queue<request> requests;
    QByteArrayView mSearchNumber;
    int mNumber{};
    QByteArray answer{};

    Q_SLOT void storeData();
};


#endif //PLUME_RECEIVEMAIL_H

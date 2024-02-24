//
// Created by theo on 2/24/24.
//

#ifndef PLUME_IMAPCONNECTION_H
#define PLUME_IMAPCONNECTION_H


#include <QSslSocket>
#include <vector>
#include <QTimer>
#include <queue>

class ImapConnection : public QObject {

Q_OBJECT

    using string = QByteArray;

public:
    explicit ImapConnection(string &login, string &password, QObject *parent);

    string getData();

    void sendRequest(const QByteArray &request);

    Q_SIGNAL void accessRead();

private:
    static constexpr char mAddress[]{"zmail.insa-lyon.fr"};
    static constexpr int mPort{993};
    QSslSocket *mSocket{new QSslSocket(this)};
    string mLogin;
    string mPassword;
    string mData{""};
    static int mCode;
    QTimer *mTimer{new QTimer(this)};
    std::queue<QByteArray> mQueue;

    static QByteArray code();

    Q_SLOT void readData();

    Q_SLOT void timeIsOut();

    void uploadRequest(const QByteArray& request);
};


#endif //PLUME_IMAPCONNECTION_H

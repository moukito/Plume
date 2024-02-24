//
// Created by theo on 2/24/24.
//

#ifndef PLUME_IMAPCONNECTION_H
#define PLUME_IMAPCONNECTION_H


#include <QSslSocket>
#include <vector>
#include <QTimer>

class ImapConnection : public QObject {
Q_OBJECT

public Q_SLOTS:

    void readData();

    void loginin();

    void timeIsOut();

private:
    using string = QByteArray;
public:
    explicit ImapConnection(string &login, string &password, QObject *parent);


    string getData();

    void sendRequest(const QByteArray &request);

    bool isReadyRead();

private:
    static constexpr char mAddress[]{"zmail.insa-lyon.fr"};
    static constexpr int mPort{993};
    QSslSocket *mSocket{new QSslSocket(this)};
    string mLogin;
    string mPassword;
    string mData{""};
    static int mCode;
    QTimer *mTimer{new QTimer(this)};

    static QByteArray code();

};


#endif //PLUME_IMAPCONNECTION_H

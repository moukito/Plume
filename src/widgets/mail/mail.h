#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "protocol/ImapConnection.h"

class Mail : public QWidget {
Q_OBJECT

public:
    explicit Mail(QWidget *parent);

private:
    QHBoxLayout *lay = nullptr;
    ImapConnection *mImap;

    Q_SLOT void test();
};
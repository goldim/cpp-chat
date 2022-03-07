#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <thread>
#include "interface.cpp"
#include "core.hpp"

#ifndef GRAPHIC_INTERFACE_H
#define	GRAPHIC_INTERFACE_H

class FormConnection: public QDialog
{
        Q_OBJECT
    public:
        QPushButton *ok;
        QLineEdit *editLogin;
        QLineEdit *editIp;
        QLineEdit *editPort;
        FormConnection();
        ~FormConnection();
    private:
        QVBoxLayout *mainl;
        QLabel *lLogin;
        QLabel *lIp;
        QLabel *lPort;
        QVBoxLayout *lcol;
        QVBoxLayout *rcol;
        QHBoxLayout *trow;
        QHBoxLayout *brow;
    signals:
        void Login();
};

class Periphery: public QDialog
{
        Q_OBJECT
    public:
        Periphery();
        ~Periphery();
        void turn_on();
        static void get_msg(Client *_client, Periphery *_shell);
    private:
        QTextEdit *chatSpace;
        QPushButton *sendButton;
        QLabel *hintLabel;
        QVBoxLayout *mainl;
        QHBoxLayout *l1;
        QHBoxLayout *l2;
        QLineEdit *msg;
        Client *cl;
        std::thread *receiver;
        FormConnection *entrance;
    private slots:
        void connect2server();
        void sendMessage();
        void printMsg(QString str);
        void reconnect();
    signals:
        void Simple(QString str);
        void ServerOff();
};


#endif	


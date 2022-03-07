#include "graphic_interface.h"
#include <sstream>

FormConnection::FormConnection()
{
    lLogin =    new QLabel("login");
    lIp =       new QLabel("ip");
    lPort =     new QLabel("port");
    editLogin = new QLineEdit;
    editIp =    new QLineEdit; 
    editPort =  new QLineEdit;
    mainl =     new QVBoxLayout;
    lcol =      new QVBoxLayout;
    rcol =      new QVBoxLayout;
    trow =      new QHBoxLayout;
    brow =      new QHBoxLayout;
    ok =        new QPushButton("Ok");
    ok->setDefault(true);
    lcol->addWidget(lLogin);
    lcol->addWidget(lIp);
    lcol->addWidget(lPort);
    rcol->addWidget(editLogin);
    rcol->addWidget(editIp);
    rcol->addWidget(editPort);
    trow->addLayout(lcol);
    trow->addLayout(rcol);
    brow->addWidget(ok);
    mainl->addLayout(trow);
    mainl->addLayout(brow);
    setLayout(mainl);    
}

FormConnection::~FormConnection(){}

Periphery::Periphery()
{
    sendButton = new QPushButton("Send");
    hintLabel =  new QLabel("Send");
    msg =        new QLineEdit;
    chatSpace =  new QTextEdit;
    mainl =      new QVBoxLayout;
    l1 =         new QHBoxLayout;
    l2 =         new QHBoxLayout;
    entrance =   new FormConnection();
}

Periphery::~Periphery(){}

void Periphery::turn_on()
{
    connect(entrance->ok, SIGNAL(clicked()), this, SLOT(connect2server()));
    entrance->setWindowTitle("Configuration");
    entrance->show();
    hide();
    chatSpace->setReadOnly(true);
    l1->addWidget(hintLabel);
    l1->addWidget(msg);
    l1->addWidget(sendButton);
    l2->addWidget(chatSpace);
    mainl->addLayout(l2);
    mainl->addLayout(l1);
    setLayout(mainl);
    setWindowTitle("Chat");
    //setWindowFlags(Qt::Window);
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(this, SIGNAL(Simple(QString)), this, SLOT(printMsg(QString)));
    connect(this, SIGNAL(ServerOff()), this, SLOT(reconnect()));
}

void Periphery::connect2server() 
{
    unsigned int port = entrance->editPort->text().toInt();
    std::string ip = entrance->editIp->text().toStdString();
    std::string login = entrance->editLogin->text().toStdString(); 
    try
    {
        cl = new Client(ip, port, login);
        setWindowTitle((std::string("Chat User: ")+login).c_str());
        cl->start();
        receiver = new std::thread(&Periphery::get_msg, cl, this);
        entrance->hide();
        show();
    }
    catch(SocketException &e)
    {
        if (strcmp(e.what().c_str(), "connection error") == 0)
        {
            QMessageBox *err = new QMessageBox;
            err->setWindowTitle("Error");
            err->setText("Server with its ip and port doesn't work or exist");
            err->exec();
            delete err;
        };
    }
}

void Periphery::reconnect() 
{
    delete cl;
    hide();
    QMessageBox *err = new QMessageBox;
    err->setWindowTitle("Disconnection");
    err->setText("Server shutdowns");
    err->move(40, 200);
    err->exec();
    entrance->editIp->clear();
    entrance->editLogin->clear();
    entrance->editPort->clear();
    entrance->show();
}


void Periphery::printMsg(QString str)
{
    chatSpace->moveCursor(QTextCursor::End);
    chatSpace->insertPlainText(str);
}

void Periphery::sendMessage()
{
    std::string inputText(msg->text().toUtf8().constData());
    if (!inputText.empty()) cl->send_msg(inputText);
    msg->clear();
}

void Periphery::get_msg(Client *_client, Periphery *_shell)
{
    std::string str;
    try
    {
        while (1)
        {
            str = _client->receive_msg();
            emit _shell->Simple(QString::fromStdString(str));
        }
    }
    catch (SocketException& e)
    {
        emit _shell->ServerOff();
    }
}




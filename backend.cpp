#include "backend.h"

Backend::Backend(QObject *parent):QObject(parent)
{
    this->myServer = nullptr;
}
QString Backend::onCloseClicked()
{
    QString str = "";
    if(this->myServer != nullptr)
    {
        str = this->myServer->closeTcp();
        this->myServer = nullptr;
    }
    return str;
}
QString Backend::onStartClicked()
{
    QString str = "";
    if(this->myServer == nullptr)
    {
        this->myServer = new MyServer(this);
        connect(this->myServer,&MyServer::haveNewConnection,this,&Backend::NewConnection);
        connect(this->myServer,&MyServer::haveMessage,this,&Backend::NewMessage);
        connect(this->myServer,&MyServer::closeConnection,this,&Backend::CloseDetected);
        connect(this->myServer,&MyServer::sendSuccess,this,&Backend::onSendSuccess);
        str = this->myServer->listenTcp();
    }
    return str;
}
void Backend::onSendClicked(QByteArray msg)
{
    if(this->myServer != nullptr)
    {
        this->myServer->sendTcp(msg);
    }
}

void Backend::NewConnection(QString msg)
{
    emit haveNewConnection(msg);
}
void Backend::NewMessage(QByteArray msg )
{
    emit haveMessage( msg );
}
void Backend::CloseDetected(QString msg)
{
    emit closeConnection(msg);
}
void Backend::onSendSuccess()
{
    emit sendSuccess();
}


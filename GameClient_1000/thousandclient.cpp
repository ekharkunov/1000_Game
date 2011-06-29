#include "thousandclient.h"

ThousandClient::ThousandClient(quint16 port, QString ip, QObject *parent): AbstractClient(parent)
{
  connectComplite=false;
  serverPort = port;
  serverIp = ip;
  connection = new QTcpSocket();
  dataParser = new ThousandClientDataParser(this);
  hostAddress.setAddress(ip);
}

void ThousandClient::setHostAddress(const QString ip)
{
   hostAddress.setAddress(ip);
   serverIp=ip;
}

void ThousandClient::connectToServer()
{
   connection->connectToHost(hostAddress,serverPort);
   if(connection->waitForConnected(1000)) emit(erorText("Connected!"));
   connect(connection,SIGNAL(error(QAbstractSocket::SocketError)),
        this,SLOT(connectEror(QAbstractSocket::SocketError)));
   connect(connection,SIGNAL(readyRead()),this,SLOT(serverReady()));
   connect(connection,SIGNAL(connected()),this,SLOT(serverConnected()));
}

void ThousandClient::serverConnected()
{
    connectComplite=true;
    emit(erorText("Client connect to server"));
}

void ThousandClient::connectEror(QAbstractSocket::SocketError err)
{
  if(err==QAbstractSocket::HostNotFoundError)emit(erorText("Host not found!"));
  if(err==QAbstractSocket::RemoteHostClosedError)emit(erorText("The remote host is closed!"));
  if(err==QAbstractSocket::ConnectionRefusedError)emit(erorText("The connection was refused!"));
}

void ThousandClient::serverReady()
{
    dataParser->incomingData();
}

void ThousandClient::sendToServer(QByteArray &data, const QueryType &type)
{
    QByteArray outReqest;
    QueryStruct query;
      query.type=type;
      query.socketDescriptor=connection->socketDescriptor();
      query.size=data.size();
    QDataStream out(&outReqest,QIODevice::ReadWrite);
      out.setVersion(QDataStream::Qt_4_7);
      out<<query;
    connection->write(outReqest);
    connection->write(data);
}

ThousandClientDataParser* ThousandClient::getDataParser()
{
    return dataParser;
}


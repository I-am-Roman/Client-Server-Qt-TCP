#include "server.h"

Server::Server()
{
  // port have a 2^16 - 1 combination
  if(!(this->listen(QHostAddress::Any,65000)))
  {
    qDebug()<<"Error";
  }
  nextBlockSize = 0;
}

//processing a new connection
void Server :: incomingConnection(qintptr soketDescriptor)
{
  socket = new QTcpSocket;
  // the soketDescriptor is simple number he's authenticating the output/input streams
  socket->setSocketDescriptor(soketDescriptor);

  connect(socket, &QTcpSocket :: readyRead,   this,   &Server::slotReadyRead);
  connect(socket, &QTcpSocket :: disconnected,socket, &QTcpSocket::deleteLater);

  Sockets.push_back(socket);
  qDebug() << "Client connected: " << soketDescriptor;
}

void Server::slotReadyRead()
{
  socket = (QTcpSocket*)sender();;
  QDataStream input(socket);
  input.setVersion(QDataStream::Qt_6_0);

  if(input.status() == QDataStream::Ok)
  {
    qDebug()<<"Read...";
    while(true)
    {
      if(nextBlockSize == 0)
      {
        if(socket->bytesAvailable()<2)
        {
          qDebug() << "Data < 2 bytes!";
          break;
        }//if 4
        input >> nextBlockSize;
        qDebug() <<"nextBlockSize = 0 "<< "nextBlockSize = "<< nextBlockSize;
      }// if 2
      if(socket->bytesAvailable() < nextBlockSize)
      {
        qDebug() << "Data not full!";
        break;
      }// if 3

      QString str;
      QTime time;
      input>> time >> str;
      nextBlockSize = 0;
      qDebug() << str;
      SendToClient(str);
      break;

    }// while
  }// if 1
  else
  {
    qDebug()<<"DataStream error";
  }//else 1
}

void Server::SendToClient(const QString& str)
{
  data.clear();
  QDataStream output(&data, QIODevice::WriteOnly);
  output.setVersion(QDataStream ::Qt_6_0);

  output <<quint16(0) << QTime::currentTime()<< str;
  output.device()->seek(0);
  output << quint16(data.size() - sizeof (quint16));

  // we should send evereone users message
  for(const auto& v : Sockets)
  { v->write(data); }
}


#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

class Server : public QTcpServer
{
  Q_OBJECT
public:
  Server();
  // The connection provides with the help sockets
  // socket include in yourself IP and port
  QTcpSocket* socket;

private:
  QVector <QTcpSocket*> Sockets;
  QByteArray data;
  void SendToClient(const QString& str);

  // The main problem is that we get infomation in parts.
  // By chance, we can process the data before we get
  // full message. So we should get information
  // about size our Block first
  quint16 nextBlockSize;

private slots:
  void incomingConnection(qintptr soketDescriptor);
  void slotReadyRead();

};


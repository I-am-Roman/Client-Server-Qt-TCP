#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Server ser;
  return a.exec();
}

/*
  1 - server
  2 - client
  1.1) launching the server (ip,port)
  2.1) creating client socket
  2.2) connect to Host (ip, port)
  1.2) connection processing
  1.3) send to client message about connection
  (successful/unsuccessful)
  2.3) message processing
  2.4) send to server something message
  1.4) message processing
  1.5/2.5) Delete sockets
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  connect(socket, &QTcpSocket::readyRead,   this,   &MainWindow::slotReadyRead);
  connect(socket, &QTcpSocket::disconnected,socket, &QTcpSocket::deleteLater);
  nextBlockSize = 0;
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_Connect_clicked()
{
  // IP can change
  //socket->connectToHost("192.168.220.145",65000);
  socket->connectToHost("192.168.196.17",65000);
}


void MainWindow::SendToServer(QString str)
{
  Data.clear();
  QDataStream out(&Data, QIODevice::WriteOnly);
  out.setVersion(QDataStream ::Qt_6_0);
  // while our message aren't written
  // we allocated 16 bits
  out <<quint16(0) <<QTime::currentTime() << str;
  out.device()->seek(0);
  // our size
  out << quint16(Data.size() - sizeof (quint16));

  socket ->write(Data);
  ui->lineEdit->clear();
}

void MainWindow::slotReadyRead()
{
  QDataStream in(socket);
  in.setVersion(QDataStream::Qt_6_0);

  if(in.status()==QDataStream::Ok)
  {
    // we don't know we get whole data or in parts
    while(true)
    {
      if(nextBlockSize == 0)
      {
          if(socket->bytesAvailable()<2)
          {
            break;
          }//if 4
          in >> nextBlockSize;
      }//if 2

      if(socket->bytesAvailable() < nextBlockSize)
      {
        break;
      }//if 3

      QString str;
      QTime time;
      in>>time >> str;
      nextBlockSize = 0;
      ui->textBrowser->append(time.toString()+ " " + str);
    }//while
  }//if 1
  else
  {
    ui->textBrowser->append("Read error");
  }//else 1
}

void MainWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}

void MainWindow::on_Send_clicked()
{
    SendToServer(ui->lineEdit->text());
}


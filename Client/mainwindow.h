#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

    class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
   void on_lineEdit_returnPressed();
   void on_Connect_clicked();
   void on_Send_clicked();

 private:
  Ui::MainWindow *ui;
  QTcpSocket* socket;
  QByteArray Data;
  void SendToServer(QString str);

  // The main problem is that we get infomation in parts.
  // By chance, we can process the data before we get
  // full message. So we should get information
  // about size our Block first
  quint16 nextBlockSize;

public slots:
  void slotReadyRead();
};
#endif // MAINWINDOW_H

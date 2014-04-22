#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <qfiledialog.h>

#include <QList>
#include <QtNetwork/QNetworkInterface>

using namespace  std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  proc(NULL)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
  if (proc != NULL) delete proc;
}

void MainWindow::on_pushButton_start_clicked()
{
  if (ui->pushButton_start->text().compare("Start")==0) {
    proc = new QProcess;
    QString program = "python3";
    QStringList arguments;
    arguments << "-m" << "http.server" << ui->lineEdit_port->text().toStdString().c_str();
    proc->start(program,arguments);

    ui->pushButton_start->setText("Stop");
    ui->pushButton_folder->setEnabled(false);
    ui->tab_settings->setEnabled(false);

    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for(int nIter=0; nIter<list.count(); nIter++) {
      if(!list[nIter].isLoopback()) {
        if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol ) {
          QString ip = list[nIter].toString();
          history += "<font color=green>Started</font> Find me as:<br> <font color=blue>http://"+ip+":"+ui->lineEdit_port->text()+"</font><br>";
          ui->textBrowser_history->setHtml(history);
        }
      }
    }

  }
  else {
    proc->close();
    delete proc;
    proc = NULL;
    ui->pushButton_start->setText("Start");
    ui->pushButton_folder->setEnabled(true);
    ui->tab_settings->setEnabled(true);
    history += "<font color=red>Stoped</font><br>";
    ui->textBrowser_history->setHtml(history);
  }
}

void MainWindow::on_pushButton_folder_clicked()
{
  QFileDialog dialog;
  dialog.setFileMode(QFileDialog::Directory);
  dialog.setOption(QFileDialog::ShowDirsOnly);
  if (dialog.exec()==1) {
    ui->pushButton_folder->setText( dialog.directory().absolutePath() );
    QDir::setCurrent(dialog.directory().absolutePath());
  }
}

void MainWindow::on_pushButton_clear_clicked()
{
    history = "";
    ui->textBrowser_history->setHtml(history);
}

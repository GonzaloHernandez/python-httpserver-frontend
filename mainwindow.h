#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdio>
#include <qprocess.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_pushButton_start_clicked();
  void on_pushButton_folder_clicked();

  void on_pushButton_clear_clicked();

private:
  Ui::MainWindow *ui;
  QProcess* proc ;
  QString history;

friend class PythonServer;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QWidget>
//#include "gamemain.h"
#include "qt5serialport/serial.h"
#include "text.h"

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

    void on_startButton_clicked();


    void on_textButton_clicked();

private:
    Ui::MainWindow *ui;
    serial *s;

};

#endif // MAINWINDOW_H

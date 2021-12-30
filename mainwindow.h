#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include<QtDebug>
#include<QFileInfo>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void myfunction();
    void myfunction1();

   // void serialReceived();

private slots:
    void on_pushButton_load_tbl_clicked();
    void serialReceived();

    void makePlot();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *timer1;

};
#endif // MAINWINDOW_H

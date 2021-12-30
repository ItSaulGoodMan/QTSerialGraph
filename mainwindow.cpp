#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QtSql>
#include <QDateTime>
#include<QTime>
#include<QSerialPort>
#include<QSerialPortInfo>
using namespace std;
QSerialPort *serial;

void addValues(int tezina);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    serial = new QSerialPort(this);
        serial ->setPortName("COM8");
        serial ->setBaudRate(QSerialPort::Baud9600);
        serial ->setDataBits(QSerialPort::Data8);
        serial ->setParity(QSerialPort::NoParity);
        serial ->setStopBits(QSerialPort::OneStop);
        serial ->setFlowControl(QSerialPort::NoFlowControl);
        serial ->open(QIODevice::ReadOnly);

        QTime dieTime= QTime::currentTime().addSecs(5);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ui -> label_3 -> setText(serial ->readLine());


        connect(serial, SIGNAL(readyRead), this, SLOT(serialReceived()));


        QTimer *timer1 = new QTimer(this);
        connect(timer1, SIGNAL(timeout()), this, SLOT(serialReceived()));
        timer1->start(3000);


    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("baza2");

    if(!mydb.open())

        ui -> label -> setText("Database is not connected");

else
        ui -> label -> setText("Database is  connected");

    QString query = "CREATE TABLE testtable("
            "timestamp datetime,"
            "tezina integer);";

    QSqlQuery qry;
    if(!qry.exec(query)){
        qDebug()<<"error creating table";
    }

  timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myfunction()));


    timer -> start(1000);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialReceived()
{


ui -> label_3 -> setText(serial ->readLine());
qDebug()<<"IDENESTO";
}

void MainWindow::myfunction()
{

QString s = ui->label_3 -> text();

int nesto = s.toInt();
qDebug()<<nesto;

qDebug()<<"Update";
int i;
i = rand() % 100;
ui -> label_2 -> setText(QString::number(i));
addValues(i);
QSqlQueryModel *model = new QSqlQueryModel();
QSqlQueryModel *model2 = new QSqlQueryModel();

QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
mydb.setDatabaseName("baza2");

if(!mydb.open())

    ui -> label -> setText("Database is not connected");

else
    ui -> label -> setText("Database is  connected");

QSqlQuery *qry = new QSqlQuery(mydb);
qry -> prepare("SELECT * FROM testtable");
qry -> exec();
model -> setQuery(*qry);
ui -> tableView -> setModel(model);
QSqlQuery *qry2 = new QSqlQuery(mydb);
qry2 -> prepare("SELECT"
           " tezina "
       " FROM "
          "  testtable "
       " LIMIT 10;" );
qry2 -> exec();
model2 -> setQuery(*qry2);
ui -> tableView_2 -> setModel(model2);
QStringList list;
QAbstractItemModel *modell = ui->tableView->model();
while (model->canFetchMore())
   model->fetchMore();
int n = modell->rowCount();


QVector<double> x(n), y(n);
//QVector<QCPGraphData> y(n);
  // generate random walk data:
QString str[5000];

int j = 0;
double now;
QVector<QCPGraphData> timeData(n);

for(int i = 0; i < n; i++)
{
QModelIndex index = modell->index(i, 2); // The first column data.
list.append(index.data().toString());
QString s = index.data().toString();
x[i] =  ui->tableView->model()->data(ui->tableView->model()->index(i,1)).toInt();
str[i] =  ui->tableView->model()->data(ui->tableView->model()->index(i,0)).toString();
QDateTime time = QDateTime::fromString(str[i], Qt::ISODateWithMs);
now = time.toTime_t();
y[i] = now;


//y[i] = now;

j++;

}



//qDebug()<<n;
QString pocetak = "2021-12-25T13:07:27.458";
QString kraj = "2021-12-25T13:08:03.230";
QDateTime time1 = QDateTime::fromString(pocetak, Qt::ISODateWithMs);
QDateTime time2 = QDateTime::fromString(kraj, Qt::ISODateWithMs);

double now1 = time1.toTime_t();
double now2 = time2.toTime_t();

ui -> customPlot->addGraph();
ui -> customPlot->graph(0)->setData(y, x);
// give the axes some labels:
ui -> customPlot->yAxis->setLabel("y");
// set axes ranges, so we see all data:
ui -> customPlot->yAxis->setRange(0, 100);
ui -> customPlot->xAxis->setRange(now - 50, now);
QLinearGradient plotGradient;
plotGradient.setStart(0, 0);
plotGradient.setFinalStop(0, 500);
plotGradient.setColorAt(0, QColor(250, 250, 250));
plotGradient.setColorAt(1, QColor(222, 222, 222));
ui -> customPlot->setBackground(plotGradient);//Set the background color
ui -> customPlot->replot();


}

void MainWindow::myfunction1()
{
    serial = new QSerialPort(this);
        serial ->setPortName("COM8");
        serial ->setBaudRate(QSerialPort::Baud9600);
        serial ->setDataBits(QSerialPort::Data8);
        serial ->setParity(QSerialPort::NoParity);
        serial ->setStopBits(QSerialPort::OneStop);
        serial ->setFlowControl(QSerialPort::NoFlowControl);
        serial ->open(QIODevice::ReadOnly);
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        ui -> label_3 -> setText(serial ->readLine());


        connect(serial, SIGNAL(readyRead), this, SLOT(serialReceived()));

}



void addValues(int tezina){
    QSqlQuery qry;
    QDateTime timestamp =  QDateTime::currentDateTime();
    QString n = timestamp.toString();
    QDateTime time = QDateTime::fromString(n, Qt::ISODateWithMs);
    double now = QDateTime::currentDateTime().toTime_t();


    int gf = n.toInt();
    //qDebug()<<gf;

    qry.prepare("INSERT INTO testtable("
               " timestamp,"
                "tezina)"
                "VALUES(?,?);");
    qry.addBindValue(timestamp);
    qry.addBindValue(tezina);



    if(!qry.exec()){

    qDebug()<<"Error adding values";
    }
    }


void MainWindow::on_pushButton_load_tbl_clicked()
{




    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQueryModel *model2 = new QSqlQueryModel();

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("baza2");

    if(!mydb.open())

        ui -> label -> setText("Database is not connected");

    else
        ui -> label -> setText("Database is  connected");

    QSqlQuery *qry = new QSqlQuery(mydb);
    qry -> prepare("SELECT * FROM testtable");
    qry -> exec();
    model -> setQuery(*qry);
    ui -> tableView -> setModel(model);
    QSqlQuery *qry2 = new QSqlQuery(mydb);
    qry2 -> prepare("SELECT"
               " tezina "
           " FROM "
              "  testtable "
           " LIMIT 10;" );
    qry2 -> exec();
    model2 -> setQuery(*qry2);
    ui -> tableView_2 -> setModel(model2);
    QStringList list;
    QAbstractItemModel *modell = ui->tableView->model();
    while (model->canFetchMore())
       model->fetchMore();
    int n = modell->rowCount();


    QVector<double> x(n), y(n);
    //QVector<QCPGraphData> y(n);
      // generate random walk data:
    QString str[5000];

    int j = 0;
    double now;
    QVector<QCPGraphData> timeData(n);

    for(int i = 0; i < n; i++)
    {
    QModelIndex index = modell->index(i, 2); // The first column data.
    list.append(index.data().toString());
    QString s = index.data().toString();
    x[i] =  ui->tableView->model()->data(ui->tableView->model()->index(i,1)).toInt();
    str[i] =  ui->tableView->model()->data(ui->tableView->model()->index(i,0)).toString();
    QDateTime time = QDateTime::fromString(str[i], Qt::ISODateWithMs);
    now = time.toTime_t();
    y[i] = now;


    //y[i] = now;

    j++;

    }



    //qDebug()<<n;
    QString pocetak = ui->lineEdit->text();

    QString kraj = ui->lineEdit_2->text();

    QDateTime time1 = QDateTime::fromString(pocetak, Qt::ISODateWithMs);
    QDateTime time2 = QDateTime::fromString(kraj, Qt::ISODateWithMs);
 QDateTime time3 = ui -> dateTimeEdit -> dateTime();
 QDateTime time4 = ui -> dateTimeEdit_2 -> dateTime();

    double now1 = time1.toTime_t();
    double now2 = time2.toTime_t();
    double now3 = time3.toTime_t();
    double now4 = time4.toTime_t();


    ui -> customPlot_2->addGraph();
    ui -> customPlot_2->graph(0)->setData(y, x);
    // give the axes some labels:
    ui -> customPlot_2->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui -> customPlot_2->yAxis->setRange(0, 100);
    ui -> customPlot_2->xAxis->setRange(now3, now4);
    ui -> customPlot_2->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 500);
    plotGradient.setColorAt(0, QColor(250, 250, 250));
    plotGradient.setColorAt(1, QColor(222, 222, 222));
    ui -> customPlot_2->setBackground(plotGradient);//Set the background color
    ui -> customPlot_2->replot();


}

void MainWindow::makePlot(){


}


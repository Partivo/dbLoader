#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>

#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>
#include <QClipboard>
#include <QtSql>
#include <QtSql/QSqlDatabase>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

QString hwid = "WWpOS2RtTXpRakZaTWpscVpGZGtNV0ZFVWpSa1ZFNXpaVmMwUFE9PQ==";
// This is not a "hwid". Just think of it as a password that will provide the connection with the server.
// You will match the hwid on your server with the string that comes out of your function that creates your own hwid.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // After the UI setup is finished, we start to write our codes.

    // We are establishing a connection with the database.
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // We are adding our database by defining it..
    db.setHostName("localhost"); // We are writing the address where our database is hosted.
    db.setUserName("root"); // We write the username in the database entry.
    db.setPassword(""); // We write our password in the database entry. I'm on localhost, I didn't set a password.
    db.setDatabaseName("dbloader"); // We write the name of the structure under the database. (It's the structure name, not the table.)

    // This is how you can check for version check, update check, on/off status. This is not our topic, I'm going over it.
    // Now we need to login to our loader. Let's get this done.

    // Introduction to Loader :)

    ui->hwidText->setText(hwid); // Here we pass the hwid we have drawn to our textbox in the form.

    if(db.open()) // If we have a connection to the database,
    {
        QString lHwid = ui->hwidText->text(); // We have defined the hwid to be checked.
        QString lUyelikDurumu; // We will define our membership status from the database here.
        QString lTest; // As an example, we will define the test article from the database here.

        QString ExecuteSQL = "SELECT lUyelikDurumu, lTest FROM data WHERE hwid = '" + lHwid + "'"; // We perform the SQL operation.
        // In this line, it briefly says "lMembershipStatus" and "lTest", select the part that matches the "hwid" in the xorui table and the hwid on this computer and pass it to the SQL realization definition.

        QSqlQuery qry; // We are creating our SQL query.

        qry.prepare(ExecuteSQL);
        if( !qry.exec() )
            qDebug() << qry.lastError();
          else
          {
        QSqlRecord rec = qry.record();
          int cols = rec.count();

          QString temp;
          for( int c=0; c<cols; c++ )
            temp += rec.fieldName(c) + ((c<cols-1)?"\t":"");

          while( qry.next() )
              {
                temp = "";
                  lUyelikDurumu = qry.value(0).toString(); // After successfully pulling the MemberStatus from the database, we pass it to the "MembershipStatus" string that we just defined here.
                  lTest = qry.value(1).toString(); // The same goes for "lTest" here.
              }
          }

        // As a result, we get the data. I'm passing here we pull the data using loops. There isn't much to tell.

        ui->pushButton_4->setText(lUyelikDurumu); // And here we pass our Membership status to our form.
        ui->pushButton_6->setText(lTest); // In the same way we pass our Test script.
    }
}

// This is the task of the Hwid copy button.
void MainWindow::on_pushButton_5_clicked() // Right click on pushButton5 and say Go to slot and create it with the clicked event. Do not try to open such a void manually.
{
    QClipboard *clip = QApplication::clipboard(); // We define our Copy Clipboard.
    QString input = ui->hwidText->text(); // Define as Input = Hwid.
    clip->setText(input); // We pass Input as input to our clipboard.
}

MainWindow::~MainWindow()
{
    delete ui;
}

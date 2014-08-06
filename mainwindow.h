#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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
    void getMusic(QNetworkReply*);
private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString url;
    QString urlEncode;
    QString urlDecode;
};

#endif // MAINWINDOW_H

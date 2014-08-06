#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getMusic(QNetworkReply*)));
 //http://box.zhangmen.baidu.com/x?op=12&count=1&title=TITLE$$AUTHOR$$$$
    QUrl url("http://box.zhangmen.baidu.com/x");
    QString author;
    QString title = "泡沫";

    QUrlQuery query;
    query.addQueryItem("op","12");
    query.addQueryItem("count","1");
    query.addQueryItem("title",QString("%1$$%2$$$").arg(title).arg(author));
    url.setQuery(query);
     qDebug() << url;

    manager->get(QNetworkRequest(url));





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getMusic(QNetworkReply* reply)
{
        QTextCodec *codec = QTextCodec::codecForName("utf8");

//        使用utf8编码，这样才可以显示中文

        QString all = codec->toUnicode(reply->readAll());

        qDebug() << reply;
        ui->textEdit->setText(all);

        //解析xml
        QXmlStreamReader xmlRead(all);


        while(!xmlRead.atEnd()){
            xmlRead.readNext();
            if(xmlRead.name()=="encode"){
                //读节点内容
                urlEncode = xmlRead.readElementText();
            }
            if(xmlRead.name()=="decode"){
                urlDecode = xmlRead.readElementText();
                break;
            }
         }
        url =urlEncode.mid(0,urlEncode.lastIndexOf("/"))+"/"+urlDecode.mid(0,urlDecode.lastIndexOf("&"));
        qDebug() << urlEncode;
        qDebug() << url;
        ui->textEdit_2->setText(url);

}
